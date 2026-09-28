#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vorbis/vorbisenc.h>
static void page(FILE *f, ogg_page *p) {
	fwrite(p->header, 1, p->header_len, f);
	fwrite(p->body, 1, p->body_len, f);
}
int main(int argc, char **argv) {
	if (argc != 4) return 1;
	int channels = atoi(argv[2]), rate = atoi(argv[3]);
	FILE *f = fopen(argv[1], "wb");
	if (!f) return 1;
	vorbis_info info;
	vorbis_info_init(&info);
	if (vorbis_encode_init_vbr(&info, channels, rate, 0.3f)) return 2;
	vorbis_comment comment;
	vorbis_comment_init(&comment);
	vorbis_comment_add_tag(&comment, "TITLE", "Generated streaming test tone");
	vorbis_dsp_state dsp;
	vorbis_analysis_init(&dsp, &info);
	vorbis_block block;
	vorbis_block_init(&dsp, &block);
	ogg_stream_state stream;
	ogg_stream_init(&stream, channels * rate);
	ogg_packet head, comm, code, packet;
	vorbis_analysis_headerout(&dsp, &comment, &head, &comm, &code);
	ogg_stream_packetin(&stream, &head);
	ogg_stream_packetin(&stream, &comm);
	ogg_stream_packetin(&stream, &code);
	ogg_page out;
	while (ogg_stream_flush(&stream, &out)) page(f, &out);
	int frames = rate / 4;
	float **pcm = vorbis_analysis_buffer(&dsp, frames);
	for (int i = 0; i < frames; ++i)
		for (int c = 0; c < channels; ++c)
			pcm[c][i] = 0.125 * sin(6.283185307179586 * (440 + c * 220) * i / rate);
	vorbis_analysis_wrote(&dsp, frames);
	vorbis_analysis_wrote(&dsp, 0);
	while (vorbis_analysis_blockout(&dsp, &block) == 1) {
		vorbis_analysis(&block, NULL);
		vorbis_bitrate_addblock(&block);
		while (vorbis_bitrate_flushpacket(&dsp, &packet)) {
			ogg_stream_packetin(&stream, &packet);
			while (ogg_stream_pageout(&stream, &out)) page(f, &out);
		}
	}
	while (ogg_stream_flush(&stream, &out)) page(f, &out);
	ogg_stream_clear(&stream);
	vorbis_block_clear(&block);
	vorbis_dsp_clear(&dsp);
	vorbis_comment_clear(&comment);
	vorbis_info_clear(&info);
	fclose(f);
	return 0;
}
