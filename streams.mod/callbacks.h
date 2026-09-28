#ifndef BMX_AUDIO_STREAM_CALLBACKS_H
#define BMX_AUDIO_STREAM_CALLBACKS_H
#include <brl.mod/blitz.mod/blitz.h>
#include <stdint.h>
#include <limits.h>

typedef struct BmxAudioInput {
	BBObject *object;
	BBLONG (*read)(BBObject *, void *, BBLONG);
	int (*seek)(BBObject *, BBLONG, int);
	BBLONG (*tell)(BBObject *);
	int failed;
} BmxAudioInput;

static size_t bmx_audio_read(void *context, void *output, size_t bytes) {
	BmxAudioInput *input = context;
	if (bytes > LLONG_MAX) {
		input->failed = 1;
		return 0;
	}
	BBLONG got = input->read(input->object, output, (BBLONG)bytes);
	if (got < 0 || (uint64_t)got > bytes) {
		input->failed = 1;
		return 0;
	}
	return (size_t)got;
}
#endif
