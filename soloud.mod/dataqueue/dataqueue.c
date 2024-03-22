/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "dataqueue.h"

typedef struct data_queue_packet
{
    size_t datalen;  /* bytes currently in use in this packet. */
    size_t startpos;  /* bytes currently consumed in this packet. */
    struct data_queue_packet *next;  /* next item in linked list. */
    uint8_t data[1];  /* packet data */
} data_queue_packet;

struct data_queue
{
    data_queue_packet *head; /* device fed from here. */
    data_queue_packet *tail; /* queue fills to here. */
    data_queue_packet *pool; /* these are unused packets. */
    size_t packet_size;   /* size of new packets */
    size_t queued_bytes;  /* number of bytes of data in the queue. */
};


static size_t min(const size_t a, const size_t b) {
    return a <= b ? a : b;
}

static void bmx_queue_list_free(data_queue_packet *packet) {
    while (packet) {
        data_queue_packet *next = packet->next;
        free(packet);
        packet = next;
    }
}

/* this all expects that you managed thread safety elsewhere. */

data_queue * bmx_queue_new(const size_t _packetlen, const size_t initialslack) {
    data_queue *queue = (data_queue *) malloc(sizeof (data_queue));

    if (!queue) {
        return 0;
    } else {
        const size_t packetlen = _packetlen ? _packetlen : 1024;
        const size_t wantpackets = (initialslack + (packetlen - 1)) / packetlen;
        size_t i;

        memset(queue, 0, sizeof(data_queue));
        queue->packet_size = packetlen;

        for (i = 0; i < wantpackets; i++) {
            data_queue_packet *packet = (data_queue_packet *) malloc(sizeof (data_queue_packet) + packetlen);
            if (packet) { /* don't care if this fails, we'll deal later. */
                packet->datalen = 0;
                packet->startpos = 0;
                packet->next = queue->pool;
                queue->pool = packet;
            }
        }
    }

    return queue;
}

void bmx_queue_free(data_queue *queue) {
    if (queue) {
        bmx_queue_list_free(queue->head);
        bmx_queue_list_free(queue->pool);
        bmx_queue_free(queue);
    }
}

void bmx_queue_clear(data_queue *queue, const size_t slack) {
    const size_t packet_size = queue ? queue->packet_size : 1;
    const size_t slackpackets = (slack + (packet_size-1)) / packet_size;
    data_queue_packet *packet;
    data_queue_packet *prev = 0;
    size_t i;

    if (!queue) {
        return;
    }

    packet = queue->head;

    /* merge the available pool and the current queue into one list. */
    if (packet) {
        queue->tail->next = queue->pool;
    } else {
        packet = queue->pool;
    }

    /* Remove the queued packets from the device. */
    queue->tail = 0;
    queue->head = 0;
    queue->queued_bytes = 0;
    queue->pool = packet;

    /* Optionally keep some slack in the pool to reduce memory allocation pressure. */
    for (i = 0; packet && (i < slackpackets); i++) {
        prev = packet;
        packet = packet->next;
    }

    if (prev) {
        prev->next = 0;
    } else {
        queue->pool = 0;
    }

    bmx_queue_free(packet);  /* free extra packets */
}

static data_queue_packet * bmx_queue_packet_allocate(data_queue *queue) {
    data_queue_packet *packet;

    packet = queue->pool;
    if (packet != 0) {
        /* we have one available in the pool. */
        queue->pool = packet->next;
    } else {
        /* Have to allocate a new one! */
        packet = (data_queue_packet *) malloc(sizeof (data_queue_packet) + queue->packet_size);
        if (packet == 0) {
            return 0;
        }
    }

    packet->datalen = 0;
    packet->startpos = 0;
    packet->next = 0;
                
    if (queue->tail == 0) {
        queue->head = packet;
    } else {
        queue->tail->next = packet;
    }
    queue->tail = packet;
    return packet;
}


int bmx_queue_write(data_queue *queue, const void *_data, const size_t _len) {
    size_t len = _len;
    const uint8_t *data = (const uint8_t *) _data;
    const size_t packet_size = queue ? queue->packet_size : 0;
    data_queue_packet *orighead;
    data_queue_packet *origtail;
    size_t origlen;
    size_t datalen;

    if (!queue) {
        return 0;
    }

    orighead = queue->head;
    origtail = queue->tail;
    origlen = origtail ? origtail->datalen : 0;

    while (len > 0) {
        data_queue_packet *packet = queue->tail;

        if (!packet || (packet->datalen >= packet_size)) {
            /* tail packet missing or completely full; we need a new packet. */
            packet = bmx_queue_packet_allocate(queue);
            if (!packet) {
                /* uhoh, reset so we've queued nothing new, free what we can. */
                if (!origtail) {
                    packet = queue->head;  /* whole queue. */
                } else {
                    packet = origtail->next;  /* what we added to existing queue. */
                    origtail->next = 0;
                    origtail->datalen = origlen;
                }
                queue->head = orighead;
                queue->tail = origtail;
                queue->pool = 0;

                bmx_queue_list_free(packet);  /* give back what we can. */
                return -1;
            }
        }

        datalen = min(len, packet_size - packet->datalen);
        memcpy(packet->data + packet->datalen, data, datalen);
        data += datalen;
        len -= datalen;
        packet->datalen += datalen;
        queue->queued_bytes += datalen;
    }

    return 0;
}

size_t bmx_queue_peek(data_queue *queue, void *_buf, const size_t _len) {
    size_t len = _len;
    uint8_t *buf = (uint8_t *) _buf;
    uint8_t *ptr = buf;
    data_queue_packet *packet;

    if (!queue) {
        return 0;
    }

    for (packet = queue->head; len && packet; packet = packet->next) {
        const size_t avail = packet->datalen - packet->startpos;
        const size_t cpy = min(len, avail);

        memcpy(ptr, packet->data + packet->startpos, cpy);
        ptr += cpy;
        len -= cpy;
    }

    return (size_t) (ptr - buf);
}

size_t bmx_queue_read(data_queue *queue, void *_buf, const size_t _len) {
    size_t len = _len;
    uint8_t *buf = (uint8_t *) _buf;
    uint8_t *ptr = buf;
    data_queue_packet *packet;

    if (!queue) {
        return 0;
    }

    while ((len > 0) && ((packet = queue->head) != 0)) {
        const size_t avail = packet->datalen - packet->startpos;
        const size_t cpy = min(len, avail);

        memcpy(ptr, packet->data + packet->startpos, cpy);
        packet->startpos += cpy;
        ptr += cpy;
        queue->queued_bytes -= cpy;
        len -= cpy;

        if (packet->startpos == packet->datalen) {  /* packet is done, put it in the pool. */
            queue->head = packet->next;

            packet->next = queue->pool;
            queue->pool = packet;
        }
    }

    if (queue->head == 0) {
        queue->tail = 0;  /* in case we drained the queue entirely. */
    }

    return (size_t) (ptr - buf);
}

size_t bmx_queue_count(data_queue *queue) {
    return queue ? queue->queued_bytes : 0;
}
