#include "../streams.mod/callbacks.h"
#include <stdlib.h>
#define DR_MP3_IMPLEMENTATION
#define DR_MP3_FLOAT_OUTPUT
#define DRMP3_API static
#define DR_MP3_NO_STDIO
#include "vendor/dr_mp3.h"

typedef struct Decoder {
	BmxAudioInput input;
	drmp3 decoder;
} Decoder;

static drmp3_bool32 seek_input(void *context, int offset, drmp3_seek_origin origin) {
	BmxAudioInput *input = context;
	return input->seek(input->object, offset, (int)origin) == 0;
}
static drmp3_bool32 tell_input(void *context, drmp3_int64 *position) {
	BmxAudioInput *input = context;
	BBLONG value = input->tell(input->object);
	if (value < 0) return 0;
	*position = value;
	return 1;
}

Decoder *bmx_mp3stream_open(BBObject *object,
	BBLONG (*read)(BBObject *, void *, BBLONG),
	int (*seek)(BBObject *, BBLONG, int), BBLONG (*tell)(BBObject *),
	int *channels, int *hertz, BBLONG *frames) {
	Decoder *value = calloc(1, sizeof(*value));
	if (!value) return NULL;
	value->input.object = object;
	value->input.read = read;
	value->input.seek = seek;
	value->input.tell = tell;
	if (!drmp3_init(&value->decoder, bmx_audio_read, seek_input, tell_input, NULL, &value->input, NULL)) {
		free(value);
		return NULL;
	}
	*channels = value->decoder.channels;
	*hertz = value->decoder.sampleRate;
	/* Only query the count if present in metadata; never scan the file at open. */
	*frames = value->decoder.totalPCMFrameCount == DRMP3_UINT64_MAX ? -1 : (BBLONG)drmp3_get_pcm_frame_count(&value->decoder);
	if (*channels < 1 || *channels > 2 || *hertz <= 0 || value->input.failed) {
		drmp3_uninit(&value->decoder);
		free(value);
		return NULL;
	}
	return value;
}
int bmx_mp3stream_read(Decoder *value, float *output, int count) {
	drmp3_uint64 got = drmp3_read_pcm_frames_f32(&value->decoder, count, output);
	return value->input.failed ? -1 : (int)got;
}
int bmx_mp3stream_seek(Decoder *value, BBLONG frame) {
	/* Seek in audible frames: resetting first avoids raw encoder-delay offsets. */
	int ok = drmp3_seek_to_pcm_frame(&value->decoder, 0);
	if (ok && frame) ok = drmp3_read_pcm_frames_f32(&value->decoder, frame, NULL) == (drmp3_uint64)frame;
	return ok && !value->input.failed;
}
void bmx_mp3stream_close(Decoder *value) {
	if (!value) return;
	drmp3_uninit(&value->decoder);
	free(value);
}
