#include <brl.mod/blitz.mod/blitz.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#define OV_EXCLUDE_STATIC_CALLBACKS
#include <vorbis/vorbisfile.h>

typedef struct VorbisStream {
	OggVorbis_File file;
	BBObject *source;
	BBLONG (*read)(BBObject *, void *, BBLONG);
	int (*seek)(BBObject *, BBLONG, int);
	BBLONG (*tell)(BBObject *);
	int channels;
	int failed;
} VorbisStream;

static size_t read_source(void *ptr, size_t size, size_t count, void *value) {
	VorbisStream *stream = value;
	if (!size || !count) return 0;
	if (count > SIZE_MAX / size || size * count > LLONG_MAX) {
		stream->failed = 1;
		return 0;
	}
	BBLONG bytes = stream->read(stream->source, ptr, (BBLONG)(size * count));
	if (bytes < 0 || (uint64_t)bytes > size * count) {
		stream->failed = 1;
		return 0;
	}
	return (size_t)bytes / size;
}

static int seek_source(void *value, ogg_int64_t offset, int whence) {
	VorbisStream *stream = value;
	return stream->seek(stream->source, offset, whence);
}

static long tell_source(void *value) {
	VorbisStream *stream = value;
	BBLONG position = stream->tell(stream->source);
	/* C long is 32 bits on Windows, even in a 64-bit build. */
	if (position < 0 || position > LONG_MAX) {
		stream->failed = 1;
		return -1;
	}
	return (long)position;
}

BBLONG bmx_vorbisstream_limit(void) { return LONG_MAX; }

VorbisStream *bmx_vorbisstream_open(BBObject *source,
	BBLONG (*read)(BBObject *, void *, BBLONG),
	int (*seek)(BBObject *, BBLONG, int), BBLONG (*tell)(BBObject *),
	int *error, int *channels, int *hertz, BBLONG *frames) {
	VorbisStream *stream = calloc(1, sizeof(*stream));
	*error = OV_EFAULT;
	if (!stream) return NULL;
	stream->source = source;
	stream->read = read;
	stream->seek = seek;
	stream->tell = tell;
	ov_callbacks callbacks = {read_source, seek_source, NULL, tell_source};
	*error = ov_open_callbacks(stream, &stream->file, NULL, 0, callbacks);
	if (*error < 0) {
		/* Failed opens clear vorbisfile's internal allocations. */
		free(stream);
		return NULL;
	}
	vorbis_info *info = ov_info(&stream->file, 0);
	if (!info || info->channels < 1 || info->channels > 2 || info->rate < 1 || info->rate > INT_MAX || stream->failed) goto invalid;
	*channels = stream->channels = info->channels;
	*hertz = (int)info->rate;
	/* One decoder has one PCM format. Reject format-changing chains up front. */
	for (long i = 1; i < ov_streams(&stream->file); ++i) {
		info = ov_info(&stream->file, (int)i);
		if (!info || info->channels != *channels || info->rate != *hertz) goto invalid;
	}
	*frames = ov_pcm_total(&stream->file, -1);
	if (*frames < 0) goto invalid;
	/* Opening indexes links and can leave the decoder beyond the first PCM frame. */
	if (ov_pcm_seek(&stream->file, 0) < 0 || stream->failed) goto invalid;
	return stream;
invalid:
	*error = OV_EINVAL;
	ov_clear(&stream->file);
	free(stream);
	return NULL;
}

int bmx_vorbisstream_read(VorbisStream *stream, float *output, int count) {
	float **pcm = NULL;
	int section = 0;
	long got = ov_read_float(&stream->file, &pcm, count, &section);
	if (stream->failed) return OV_EREAD;
	if (got <= 0) return (int)got;
	for (int i = 0; i < got; ++i) {
		for (int channel = 0; channel < stream->channels; ++channel) {
			output[i * stream->channels + channel] = pcm[channel][i];
		}
	}
	return (int)got;
}

int bmx_vorbisstream_seek(VorbisStream *stream, BBLONG frame) {
	int result = ov_pcm_seek(&stream->file, frame);
	return stream->failed ? OV_EREAD : result;
}

void bmx_vorbisstream_close(VorbisStream *stream) {
	if (!stream) return;
	ov_clear(&stream->file);
	free(stream);
}
