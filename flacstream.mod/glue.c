#include "../streams.mod/callbacks.h"
#include <stdlib.h>
#define DR_FLAC_IMPLEMENTATION
#define DRFLAC_API static
#define DR_FLAC_NO_STDIO
#define DR_FLAC_NO_OGG
#include "vendor/dr_flac.h"

typedef struct Decoder {
	BmxAudioInput input;
	drflac *decoder;
} Decoder;

static drflac_bool32 seek_input(void *context, int offset, drflac_seek_origin origin) {
	BmxAudioInput *input = context;
	return input->seek(input->object, offset, (int)origin) == 0;
}
static drflac_bool32 tell_input(void *context, drflac_int64 *position) {
	BmxAudioInput *input = context;
	BBLONG value = input->tell(input->object);
	if (value < 0) return 0;
	*position = value;
	return 1;
}

Decoder *bmx_flacstream_open(BBObject *object,
	BBLONG (*read)(BBObject *, void *, BBLONG),
	int (*seek)(BBObject *, BBLONG, int), BBLONG (*tell)(BBObject *),
	int *channels, int *hertz, BBLONG *frames) {
	Decoder *value = calloc(1, sizeof(*value));
	if (!value) return NULL;
	value->input.object = object;
	value->input.read = read;
	value->input.seek = seek;
	value->input.tell = tell;
	value->decoder = drflac_open(bmx_audio_read, seek_input, tell_input, &value->input, NULL);
	if (!value->decoder) { free(value); return NULL; }
	*channels = value->decoder->channels;
	*hertz = value->decoder->sampleRate;
	*frames = value->decoder->totalPCMFrameCount ? (BBLONG)value->decoder->totalPCMFrameCount : -1;
	if (*channels < 1 || *channels > 2 || *hertz <= 0 || value->input.failed) {
		drflac_close(value->decoder);
		free(value);
		return NULL;
	}
	return value;
}
int bmx_flacstream_read(Decoder *value, float *output, int count) {
	drflac_uint64 got = drflac_read_pcm_frames_f32(value->decoder, count, output);
	return value->input.failed ? -1 : (int)got;
}
int bmx_flacstream_seek(Decoder *value, BBLONG frame) {
	int ok;
	if (!value->decoder->totalPCMFrameCount && frame > 0) {
		/* Upstream clamps unknown-length seeks to zero; use bounded decoding. */
		ok = drflac_seek_to_pcm_frame(value->decoder, 0);
		if (ok) ok = drflac_read_pcm_frames_f32(value->decoder, frame, NULL) == (drflac_uint64)frame;
	} else {
		ok = drflac_seek_to_pcm_frame(value->decoder, frame);
	}
	return ok && !value->input.failed;
}
void bmx_flacstream_close(Decoder *value) {
	if (!value) return;
	drflac_close(value->decoder);
	free(value);
}
