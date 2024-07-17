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
#ifndef max_dataqueue_h_
#define max_dataqueue_h_

#include <stdlib.h>
#include <string.h>

#if __STDC_VERSION__ >= 199901L
    #include <stdint.h>
#else
    typedef unsigned char uint8_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* this is not (currently) a public API. But maybe it should be! */

struct data_queue;
typedef struct data_queue data_queue;

data_queue *bmx_queue_new(const size_t packetlen, const size_t initialslack);
void bmx_queue_free(data_queue *queue);
void bmx_queue_clear(data_queue *queue, const size_t slack);
int bmx_queue_write(data_queue *queue, const void *data, const size_t len);
size_t bmx_queue_read(data_queue *queue, void *buf, const size_t len);
size_t bmx_queue_peek(data_queue *queue, void *buf, const size_t len);
size_t bmx_queue_count(data_queue *queue);

#ifdef __cplusplus
}
#endif

#endif /* max_dataqueue_h_ */


