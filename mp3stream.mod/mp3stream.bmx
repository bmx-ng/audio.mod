SuperStrict

Rem
bbdoc: Registers incremental MP3 decoding with Audio.Streams.
about: Supports mono/stereo seekable TStreams. Decoders borrow input streams and return interleaved float PCM. Import this provider to enable SOUND_STREAM playback in compatible backends.
End Rem
Module Audio.Mp3Stream
ModuleInfo "License: zlib/libpng (wrapper); MIT-0 (decoder)"
ModuleInfo "CC_OPTS: -std=c99"
Import Audio.Streams
Import "glue.c"

Private
Type TMp3StreamProvider Extends TAudioStreamProvider
	Method Open:TAudioStreamDecoder(stream:TStream) Override
		Local origin:Long = stream.Pos()
		Local signature:Byte[4]
		Local read:Int
		While read < 4
			Local got:Long = stream.Read(Varptr signature[read], 4 - read)
			If got < 0 Or got > 4 - read Then Throw "Invalid MP3 probe read result"
			If Not got Then Return Null
			read :+ Int(got)
		Wend
		Local recognised:Int = (signature[0] = 73 And signature[1] = 68 And signature[2] = 51) Or (signature[0] = 255 And (signature[1] & 224) = 224 And (signature[1] & 6) = 2 And (signature[1] & 24) <> 8 And (signature[2] & 240) <> 240 And (signature[2] & 12) <> 12)
		If Not recognised Then Return Null
		If stream.Seek(origin) <> origin Then Throw "Unable to rewind MP3 input"
		Local decoder:TMp3StreamDecoder = New TMp3StreamDecoder
		decoder.input = TAudioDecoderInput.Create(stream)
		Try
			decoder.handle = bmx_mp3stream_open(decoder.input, TAudioDecoderInput.Read, TAudioDecoderInput.Seek, TAudioDecoderInput.Tell, decoder.channels, decoder.hertz, decoder.frames)
			decoder.input.Check()
			If Not decoder.handle Then Throw "Invalid or unsupported MP3 input"
		Catch error:Object
			decoder.Close()
			Throw error
		End Try
		Return decoder
	End Method
End Type

Type TMp3StreamDecoder Extends TAudioStreamDecoder
	Field input:TAudioDecoderInput
	Field handle:Byte Ptr
	Field position:Long

	Method ReadFrames:Int(output:Float[], count:Int) Override
		If Not handle Then Throw "MP3 decoder is closed"
		input.Check()
		If count < 0 Or count > output.length / channels Then Throw "Audio output buffer is too small"
		If Not count Then Return 0
		Local got:Int = bmx_mp3stream_read(handle, output, count)
		input.Check()
		If got < 0 Then Throw "MP3 decoding failed"
		If Not got And frames >= 0 And position < frames Then Throw "Truncated or corrupt MP3 audio"
		position :+ got
		Return got
	End Method

	Method SeekFrame:Int(frame:Long) Override
		If Not handle Or frame < 0 Or (frames >= 0 And frame > frames) Then Return False
		input.Check()
		Local ok:Int = bmx_mp3stream_seek(handle, frame)
		input.Check()
		If ok Then position = frame
		Return ok
	End Method

	Method Close() Override
		If handle Then bmx_mp3stream_close(handle)
		handle = Null
		input = Null
	End Method
End Type

New TMp3StreamProvider

Extern
	Function bmx_mp3stream_open:Byte Ptr(source:Object, read:Long(value:Object, output:Byte Ptr, count:Long), seek:Int(value:Object, offset:Long, whence:Int), tell:Long(value:Object), channels:Int Var, hertz:Int Var, frames:Long Var)
	Function bmx_mp3stream_read:Int(handle:Byte Ptr, output:Float Ptr, count:Int)
	Function bmx_mp3stream_seek:Int(handle:Byte Ptr, frame:Long)
	Function bmx_mp3stream_close(handle:Byte Ptr)
End Extern
