# Streaming MP3

Import `Audio.Mp3Stream` to register incremental MP3 decoding with `Audio.Streams`.
It supports mono/stereo inputs through seekable `TStream` objects with known byte
lengths. The source should begin at an ID3 header or an MPEG Layer III frame; this
provider does not search arbitrary leading junk for a possible MP3.

```blitzmax
Import SDL3.SDL3AudioAudio
Import Audio.Mp3Stream

If Not SetAudioDriver("SDL3") Then Throw SDL_GetError()
Local music:TSound = LoadSound("music.mp3", SOUND_STREAM | SOUND_LOOP)
If Not music Then Throw SDL_GetError()
Local channel:TChannel = PlaySound(music)
If Not channel Then Throw SDL_GetError()
```

## Duration, seeking and loops

Decoding produces float PCM directly, with fixed working buffers. Loading reads
initial metadata/audio frames and may inspect end tags; it does not scan the
whole recording to calculate its length. If Xing/Info metadata supplies a frame
count, `frames` reports the audible count after recognised encoder delay/padding.
Otherwise `frames = -1` and playback continues until EOF.

Recognised LAME-style delay and padding are trimmed by the decoder. Tests cover
both CBR and VBR files with such metadata. Files without usable gapless metadata
may include leading/trailing encoder samples; seamless loops cannot be promised
for those files. Trimming metadata also does not remove silence present in the
original recording.

`SeekFrame` addresses audible output frames. Rewinding is cheap. Nonzero seeks
currently rewind and decode/discard up to the requested frame to keep positions
correct with encoder delay. This uses bounded memory but costs time proportional
to the destination; no seek table is built during loading. Use short samples
loaded into memory when frequent random seeking matters. Concatenations that
change channel count or sample rate are not a supported input format.

## Stream ownership and errors

The input's current position is the start of the MP3 file. The decoder borrows
it and never closes it. Close the decoder explicitly or use `Using`; use each
input/decoder from one thread at a time. Stream callbacks catch exceptions so
they cannot unwind through native code, then rethrow after the native call.
Detected premature EOF against a known duration is an error. The native decoder
can skip damaged frames; an untagged damaged file may be indistinguishable from
an early end. This provider is not a bitstream integrity checker.

For direct decoding, use `OpenAudioStreamDecoder(stream)` and reuse a `Float[]`
with `ReadFrames`. Importing this module does not add a whole-file sample loader
or alter existing sound-effect loading.

## Bundled decoder and tests

Uses **dr_mp3 0.7.3**, release commit
`5690d4671d7ad07ae6021756d7222eb159745f06` from
[dr_libs](https://github.com/mackron/dr_libs/tree/5690d4671d7ad07ae6021756d7222eb159745f06).
The unchanged header is in `vendor/dr_mp3.h`. The MIT-0 licence option is used;
the header also preserves the underlying minimp3 public-domain notice. The
BlitzMax/C wrapper is zlib/libpng. Decoder symbols are private so other modules
can use their own versions. SoLoud and Raylib are not dependencies.

`SDL3`'s `tests/audio_flac_mp3.bmx` checks CBR/VBR delay and padding, an untagged
unknown-duration input, mono/stereo PCM, sample-accurate seeks, partial reads,
nonzero origins, callback failures, ownership and playback/looping. Fixtures are
generated triangle waves. Regenerate with
`../flacstream.mod/tests/generate_fixtures.py` (FFmpeg and LAME required only for
regenerating test assets).
