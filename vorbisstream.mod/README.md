# Streaming Ogg Vorbis

Import `Audio.VorbisStream` to register incremental Ogg Vorbis decoding with
`Audio.Streams`. For SDL3 music playback:

```blitzmax
Import SDL3.SDL3AudioAudio
Import Audio.VorbisStream

If Not SetAudioDriver("SDL3") Then Throw SDL_GetError()
Local music:TSound = LoadSound("music.ogg", SOUND_STREAM | SOUND_LOOP)
If Not music Then Throw SDL_GetError()
Local channel:TChannel = PlaySound(music)
If Not channel Then Throw SDL_GetError()
```

Keep the application running while music plays; stop with `StopChannel(channel)`.
Use `SDLAudioStreamingError(channel)` to check for a later read/decoding failure.

For short effects loaded fully into memory, import `BRL.OGGLoader` and omit
`SOUND_STREAM`. Both imports can coexist. This provider reuses `Pub.OggVorbis`;
it does not replace its existing API or BRL's sample loader.

## Supported inputs

- Mono and stereo Ogg **Vorbis**. An `.ogg` extension alone does not identify the
  codec; Ogg Opus and other Ogg codecs are not decoded by this provider.
- Seekable `TStream` inputs with a known size. Decoding begins at the stream's
  current position, which may be nonzero. The remainder of the stream is the Ogg
  input; supply a bounded stream if there is unrelated data after it.
- Chained Vorbis streams when all links have the same sample rate and channel
  count. Chains that change the output format are rejected when opened.
- Sample-frame seeking for replay and loops. Total frame counts use BlitzMax
  `Long`, including all links in a chain.

Opening uses libvorbisfile to inspect headers and index logical streams. It can
seek and read near the end of the input; it does not decode the whole recording
into memory. Decoding then produces interleaved float PCM in requested chunks.
Working memory depends on Vorbis setup data and the number of links, not the
recording's decoded duration. Input and decoding failures throw; damaged packets
are reported rather than silently skipped.

The bundled libvorbisfile API uses **C `long`** for its tell callback. On Windows
that limits an individual input to 2 GiB minus one byte; larger inputs are
explicitly rejected instead of truncating offsets. macOS/Linux 64-bit builds have
64-bit C `long`. This limit concerns compressed input bytes, not PCM frame counts.

## Use the decoder directly

Call `OpenAudioStreamDecoder(stream)` from `Audio.Streams`, reuse a `Float[]`
buffer for `ReadFrames`, and close the decoder explicitly or with `Using`.
`Close` does not close the borrowed stream. Use each decoder/input exclusively
from one thread at a time. Stream callbacks run synchronously on the decoding
thread and catch exceptions before returning to native Vorbis code; the wrapper
rethrows after the native call has returned. They never run on SDL's audio thread.

The wrapper is zlib/libpng licensed. The existing Ogg/Vorbis sources retain their
Xiph BSD-style licences in `Pub.OggVorbis`.

## Tests

`SDL3`'s `tests/audio_vorbis.bmx` exercises mono/stereo PCM, short reads, nonzero
origins, sample-accurate seeking, compatible/incompatible chains, malformed
inputs, callback errors, borrowed-stream ownership, and SDL3 playback/looping.
The tiny fixtures in `tests/data` are generated sine tones, not third-party music.
`tests/generate_fixtures.c` can regenerate them using the bundled Vorbis encoder:
compile it together with `libvorbis-1.3.4/lib/vorbisenc.c`, the platform's built
`Pub.OggVorbis` archive, and the Ogg include, Vorbis include and Vorbis lib include
paths. Run with `output.ogg channels rate`; fixtures use `1 48000` and `2 44100`.
