# Streaming FLAC

Import `Audio.FlacStream` to register incremental native FLAC decoding with
`Audio.Streams`. It supports mono/stereo audio through seekable `TStream` inputs
with a known byte length. Ogg-encapsulated FLAC is not enabled.

```blitzmax
Import SDL3.SDL3AudioAudio
Import Audio.FlacStream

If Not SetAudioDriver("SDL3") Then Throw SDL_GetError()
Local music:TSound = LoadSound("music.flac", SOUND_STREAM | SOUND_LOOP)
If Not music Then Throw SDL_GetError()
Local channel:TChannel = PlaySound(music)
If Not channel Then Throw SDL_GetError()
```

The provider reads headers at open, then decodes requested chunks to interleaved
float PCM. It obtains the total PCM frame count from STREAMINFO; a zero/unknown
count is exposed as `frames = -1`. Playback does not allocate a full decoded
recording. Frame seeking and looping are supported. If the frame count is
unknown, nonzero seeks rewind and decode/discard up to the requested frame;
this uses bounded memory but takes time proportional to the destination.

The input's current position is the beginning of the FLAC file. The decoder
borrows it and never closes it. Close the decoder explicitly or use `Using`;
input access is exclusive to its decoding thread. Stream exceptions are caught
inside callbacks and rethrown after native decoder calls return. Detected early
EOF against a known frame count is reported as truncated/corrupt audio. The
underlying decoder can recover from some damaged frames; this is not a file
integrity checker or a FLAC MD5 verification API.

For direct use, call `OpenAudioStreamDecoder(stream)` and reuse a `Float[]` with
`ReadFrames`. Importing this provider does not register a whole-file sample
loader or change existing sound-effect loading.

## Bundled decoder and tests

Uses **dr_flac 0.13.3**, release commit
`69d777c482775858e8ea8a7b047c9bcd451febc8` from
[dr_libs](https://github.com/mackron/dr_libs/tree/69d777c482775858e8ea8a7b047c9bcd451febc8).
The unchanged header is in `vendor/dr_flac.h`. The MIT-0 licence option is used;
the licence text remains in that header. The BlitzMax/C wrapper is zlib/libpng.
Decoder symbols are private, so other modules may use their own dr_flac versions.
There is no dependency on SoLoud or Raylib.

`SDL3`'s `tests/audio_flac_mp3.bmx` checks exact lossless PCM output, frame counts,
nonzero stream origins, partial reads, seeking, malformed input, callback failures,
ownership and playback/looping. `tests/data` contains generated one-second
triangle-wave fixtures. `tests/generate_fixtures.py` regenerates these and the MP3
fixtures using FFmpeg and LAME; those tools are not runtime dependencies.
