# Streaming WAV decoder

Import `Audio.WavStream` to register RIFF WAV decoding with `Audio.Streams`.
Supported inputs are mono/stereo integer PCM with unsigned 8-bit or signed
16-, 24- or 32-bit little-endian samples. Unknown RIFF chunks and chunk padding
are skipped. Compressed WAV, floating-point WAV, extensible WAV and RF64 are not
yet supported.

The decoder reads only requested frames, keeps reusable scratch storage, supports
frame seeking and leaves the caller's stream open. It requires seekable input.

For SDL3 playback, import `SDL3.SDL3AudioAudio` too, select the `SDL3` audio driver,
and load with `LoadSound(url, SOUND_STREAM)`. Add `SOUND_LOOP` for looping music.
The ordinary `BRL.WAVLoader` remains appropriate for fully loaded sound effects;
it is separate from this incremental decoder.
