SuperStrict

Rem
bbdoc: Registers incremental Ogg Vorbis decoding for Audio.Streams.
about: Import alongside a streaming audio backend. Supports seekable mono/stereo inputs and chained streams with identical channel counts and sample rates. Decoders borrow their input and output interleaved float PCM. Uses the bundled Pub.OggVorbis library; ordinary BRL.OGGLoader loading remains separate.
End Rem
Module Audio.VorbisStream
ModuleInfo "License: zlib/libpng (wrapper); Xiph BSD-style licences (Pub.OggVorbis)"
ModuleInfo "CC_OPTS: -std=c99 -I%PWD%/../../pub.mod/oggvorbis.mod/libogg-1.3.1/include -I%PWD%/../../pub.mod/oggvorbis.mod/libvorbis-1.3.4/include"

Import Audio.Streams
Import Pub.OggVorbis
Import "glue.c"

Private

' Callbacks run synchronously on the decoding thread, never on an audio thread.
' Catch here so a BlitzMax exception never unwinds through libvorbis allocations.
Type TVorbisInput
	Field stream:TStream
	Field origin:Long
	Field length:Long
	Field failure:String

	Method Check()
		If failure Then Throw failure
	End Method

	Function Read:Long(value:Object, output:Byte Ptr, count:Long)
		Local input:TVorbisInput = TVorbisInput(value)
		If input.failure Then Return -1
		Try
			Local position:Long = input.stream.Pos() - input.origin
			If position < 0 Or position > input.length Then Throw "Invalid Vorbis input position"
			count = Min(count, input.length - position)
			Local total:Long
			While total < count
				Local amount:Long = input.stream.Read(output + total, count - total)
				If amount < 0 Or amount > count - total Then Throw "Invalid Vorbis input read result"
				If Not amount Then Throw "Truncated Vorbis input"
				total :+ amount
			Wend
			Return total
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function

	Function Seek:Int(value:Object, offset:Long, whence:Int)
		Local input:TVorbisInput = TVorbisInput(value)
		If input.failure Then Return -1
		Try
			Local base:Long
			Select whence
				Case 0
					base = 0
				Case 1
					base = input.stream.Pos() - input.origin
				Case 2
					base = input.length
				Default
					Return -1
			End Select
			If base < 0 Or base > input.length Then Throw "Invalid Vorbis seek origin"
			If offset < -base Or offset > input.length - base Then Return -1
			Local target:Long = input.origin + base + offset
			If input.stream.Seek(target) <> target Then Throw "Unable to seek Vorbis input"
			Return 0
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function

	Function Tell:Long(value:Object)
		Local input:TVorbisInput = TVorbisInput(value)
		If input.failure Then Return -1
		Try
			Return input.stream.Pos() - input.origin
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function
End Type

Type TVorbisStreamProvider Extends TAudioStreamProvider
	Method Open:TAudioStreamDecoder(stream:TStream) Override
		Local origin:Long = stream.Pos()
		Local signature:Byte[4]
		Local read:Int
		While read < signature.length
			Local amount:Long = stream.Read(Varptr signature[read], signature.length - read)
			If amount < 0 Or amount > signature.length - read Then Throw "Invalid Vorbis probe read result"
			If Not amount Then Return Null
			read :+ Int(amount)
		Wend
		If signature[0] <> 79 Or signature[1] <> 103 Or signature[2] <> 103 Or signature[3] <> 83 Then Return Null
		If stream.Seek(origin) <> origin Then Throw "Unable to rewind Vorbis input"
		Local decoder:TVorbisStreamDecoder = New TVorbisStreamDecoder
		decoder.input = New TVorbisInput
		decoder.input.stream = stream
		decoder.input.origin = stream.Pos()
		decoder.input.length = stream.Size() - decoder.input.origin
		If decoder.input.length < 0 Then Throw "Vorbis input requires a known size"
		If decoder.input.length > bmx_vorbisstream_limit() Then Throw "Vorbis input exceeds this platform's C long offset limit"
		Try
			Local error:Int
			decoder.handle = bmx_vorbisstream_open(decoder.input, TVorbisInput.Read, TVorbisInput.Seek, TVorbisInput.Tell, error, decoder.channels, decoder.hertz, decoder.frames)
			decoder.input.Check()
			If Not decoder.handle Then
				If error = -132 Then Return Null ' OV_ENOTVORBIS; another provider may recognise it.
				Throw "Unable to open Vorbis input (code " + error + "); expected valid mono/stereo Vorbis with a fixed PCM format"
			End If
		Catch error:Object
			decoder.Close()
			Throw error
		End Try
		Return decoder
	End Method
End Type

Type TVorbisStreamDecoder Extends TAudioStreamDecoder
	Field handle:Byte Ptr
	Field input:TVorbisInput

	Method ReadFrames:Int(output:Float[], count:Int) Override
		If Not handle Then Throw "Vorbis decoder is closed"
		input.Check()
		If count < 0 Or count > output.length / channels Then Throw "Audio output buffer is too small"
		If Not count Then Return 0
		Local got:Int = bmx_vorbisstream_read(handle, output, count)
		input.Check()
		If got < 0 Then Throw "Vorbis decode failed (code " + got + ")"
		Return got
	End Method

	Method SeekFrame:Int(frame:Long) Override
		If Not handle Or frame < 0 Or frame > frames Then Return False
		input.Check()
		Local result:Int = bmx_vorbisstream_seek(handle, frame)
		input.Check()
		Return result = 0
	End Method

	Method Close() Override
		If handle Then bmx_vorbisstream_close(handle)
		handle = Null
		input = Null
	End Method
End Type

New TVorbisStreamProvider

Extern
	Function bmx_vorbisstream_limit:Long()
	Function bmx_vorbisstream_open:Byte Ptr(source:Object, read:Long(value:Object, output:Byte Ptr, count:Long), seek:Int(value:Object, offset:Long, whence:Int), tell:Long(value:Object), error:Int Var, channels:Int Var, hertz:Int Var, frames:Long Var)
	Function bmx_vorbisstream_read:Int(handle:Byte Ptr, output:Float Ptr, count:Int)
	Function bmx_vorbisstream_seek:Int(handle:Byte Ptr, frame:Long)
	Function bmx_vorbisstream_close(handle:Byte Ptr)
End Extern
