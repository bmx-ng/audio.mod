# Incremental audio decoders

`Audio.Streams` provides a small decoder interface for reading audio in chunks.
It does not open an audio device or load an entire recording. Import a provider
such as `Audio.WavStream` or `Audio.VorbisStream` to register the formats your application needs.

```blitzmax
SuperStrict

Framework Audio.WavStream
Import BRL.StandardIO

Local input:TStream = ReadStream("music.wav")
If Not input Then Throw "Unable to open music.wav"
Using
	Local ownedInput:TStream = input
	Local decoder:TAudioStreamDecoder = OpenAudioStreamDecoder(input)
Do
	If Not decoder Then Throw "No decoder recognises this file"
	Local pcm:Float[] = New Float[2048 * decoder.channels]
	Local count:Int = decoder.ReadFrames(pcm, 2048)
	Print "Read " + count + " sample frames"
	' Consume count * decoder.channels floats, then reuse pcm for the next read.
End Using
```

A frame contains one sample per channel. Decoded samples use interleaved floating
point PCM, normally from -1 to +1. `hertz` and `channels` describe that output;
`frames` reports the total frame count, or -1 if unknown. `ReadFrames` returns the
number of frames written, zero at EOF, and throws on a read or decoding error.
`SeekFrame(0)` rewinds; seeking returns False if unsupported.

The decoder borrows the input. Closing it releases decoder resources without
closing the stream. Keep the input alive and use it exclusively until the decoder
is closed. The example explicitly owns and closes both resources with `Using`.
Decoders may be used on a worker thread, but each decoder/input pair must be used
by only one thread at a time. Custom streams must support that use.

## Add a provider

Extend `TAudioStreamProvider`, implement `Open(stream)`, and create one instance
at module initialization. Importing your module then registers the decoder.

- Return Null when the input is not your format. Throw for malformed recognised
  input. Never close the caller's stream.
- Honour the input's initial position; it need not be zero. The registry seeks
  back to that position before each probe and restores it on failure.
- Return a `TAudioStreamDecoder` with valid output metadata. Reuse scratch storage
  when reading. Do not hide a whole-file load behind this interface.
- Register before workers start. The provider registry is initialized once and
  is not intended for concurrent registration or unloading.

The registry currently requires seekable inputs so format probing can rewind.
There is no automatic fallback to BRL.AudioSample loaders.

`TAudioDecoderInput` is a reusable callback adapter for provider implementations.
Create it with a seekable stream of known size, then pass its `Read`, `Seek` and
`Tell` functions to native glue. Offsets are relative to the original stream
position. Call `Check` after each native operation to rethrow captured stream
errors safely; native code must not retain the object beyond the decoder's
lifetime. The adapter does not own or close the stream.
