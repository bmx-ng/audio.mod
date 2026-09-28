SuperStrict

Rem
bbdoc: Incremental audio decoder providers, independent of any playback backend.
about: Import a provider such as Audio.WavStream to register a format. Decoders borrow seekable TStreams and output interleaved float PCM. Keep the stream open, and use each decoder and stream from one thread at a time. Register providers during module initialization, before starting decoder workers.
End Rem
Module Audio.Streams
ModuleInfo "License: zlib/libpng"
Import BRL.Stream
Import "input.bmx"

Rem
bbdoc: An incremental decoder that borrows its input stream.
about: hertz and channels describe output PCM. frames is the total frame count, or -1 if unknown. A frame contains one sample per channel. Close releases decoder resources but does not close the borrowed stream. Read failures throw; zero frames read means end of input.
End Rem
Type TAudioStreamDecoder Implements ICloseable
	Field hertz:Int
	Field channels:Int
	Field frames:Long = -1

	Rem
	bbdoc: Reads up to count sample frames into the beginning of output. The array must hold count times channels floats.
	End Rem
	Method ReadFrames:Int(output:Float[], count:Int) Abstract

	Rem
	bbdoc: Seeks to an absolute sample frame. Returns False if seeking is unsupported or the position is invalid.
	End Rem
	Method SeekFrame:Int(frame:Long) Abstract

	Method Close() Abstract
End Type

Rem
bbdoc: A decoder factory registered by constructing a subclass during module initialization.
about: Open returns Null for unrecognised formats and throws for malformed recognised input. It must not close the supplied stream. The stream may start at a nonzero position. The registry rewinds it before probing each provider.
End Rem
Type TAudioStreamProvider
	Private
	Field _next:TAudioStreamProvider
	Public
	Method New()
		_next = providers
		providers = Self
	End Method
	Method Open:TAudioStreamDecoder(stream:TStream) Abstract

	Function OpenDecoder:TAudioStreamDecoder(stream:TStream)
		If Not stream Then Return Null
		Local origin:Long = stream.Pos()
		If origin < 0 Or stream.Seek(origin) <> origin Then Throw "Audio decoding requires a seekable stream"
		Local provider:TAudioStreamProvider = providers
		Try
			While provider
				If stream.Seek(origin) <> origin Then Throw "Unable to rewind audio stream"
				Local decoder:TAudioStreamDecoder = provider.Open(stream)
				If decoder Then Return decoder
				provider = provider._next
			Wend
		Catch error:Object
			stream.Seek(origin)
			Throw error
		End Try
		stream.Seek(origin)
		Return Null
	End Function
End Type

Rem
bbdoc: Opens an incremental decoder at the stream's current position, or returns Null if no imported provider recognises it.
about: The caller owns the stream. Failures restore its starting position where possible. No fallback to whole-file decoding is performed.
End Rem
Function OpenAudioStreamDecoder:TAudioStreamDecoder(stream:TStream)
	Return TAudioStreamProvider.OpenDecoder(stream)
End Function

Private
Global providers:TAudioStreamProvider
