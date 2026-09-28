SuperStrict

Rem
bbdoc: Registers incremental decoding of mono/stereo integer PCM RIFF WAV audio.
about: Supports unsigned 8-bit and signed 16/24/32-bit little-endian PCM. No whole-file buffering. Compressed WAV, RF64, extensible WAV and floating-point WAV are not supported by this initial provider. Input must be seekable; caller streams remain open.
End Rem
Module Audio.WavStream
ModuleInfo "License: zlib/libpng"
Import Audio.Streams

Private
Type TWavStreamProvider Extends TAudioStreamProvider
	Method Open:TAudioStreamDecoder(stream:TStream) Override
		Local origin:Long = stream.Pos()
		Local header:Byte[12]
		If ReadSome(stream, header, 12) <> 12 Then Return Null
		If Tag(header, 0) <> "RIFF" Or Tag(header, 8) <> "WAVE" Then Return Null
		Local endPos:Long = origin + 8 + LE32(header, 4)
		If endPos < origin + 12 Then Throw "Invalid WAV RIFF size"
		Local size:Long = stream.Size()
		If size >= 0 And endPos > size Then Throw "Truncated WAV container"
		Local chunk:Byte[8]
		Local format:Byte[16]
		Local bits:Int, channels:Int, hertz:Int, align:Int
		Local dataPos:Long = -1, dataBytes:Long
		Local haveFormat:Int
		While stream.Pos() + 8 <= endPos
			ReadExact(stream, chunk, 8)
			Local length:Long = LE32(chunk, 4)
			Local payload:Long = stream.Pos()
			Local nextPos:Long = payload + length + (length & 1)
			If nextPos > endPos Then Throw "WAV chunk exceeds RIFF boundary"
			Select Tag(chunk, 0)
				Case "fmt "
					If haveFormat Or length < 16 Then Throw "Invalid WAV format chunk"
					ReadExact(stream, format, 16)
					If LE16(format, 0) <> 1 Then Throw "Streaming WAV requires integer PCM"
					channels = LE16(format, 2)
					Local frequency:Long = LE32(format, 4)
					If frequency <= 0 Or frequency > 384000 Then Throw "Unsupported WAV sample rate"
					hertz = Int(frequency)
					bits = LE16(format, 14)
					If channels < 1 Or channels > 2 Then Throw "Streaming WAV supports mono or stereo"
					If bits <> 8 And bits <> 16 And bits <> 24 And bits <> 32 Then Throw "Unsupported WAV PCM bit depth"
					align = channels * (bits / 8)
					If LE16(format, 12) <> align Or LE32(format, 8) <> Long(hertz) * align Then Throw "Inconsistent WAV frame size"
					haveFormat = True
				Case "data"
					If dataPos < 0 Then
						dataPos = payload
						dataBytes = length
					End If
			End Select
			If haveFormat And dataPos >= 0 Then Exit
			If stream.Seek(nextPos) <> nextPos Then Throw "Unable to seek WAV chunk"
		Wend
		If Not haveFormat Or dataPos < 0 Or dataBytes Mod align Then Throw "Invalid WAV audio data"
		Local decoder:TWavStreamDecoder = New TWavStreamDecoder
		decoder.stream = stream
		decoder.hertz = hertz
		decoder.channels = channels
		decoder.frames = dataBytes / align
		decoder.dataPos = dataPos
		decoder.align = align
		decoder.bits = bits
		If Not decoder.SeekFrame(0) Then Throw "Unable to seek WAV audio data"
		Return decoder
	End Method
End Type

Type TWavStreamDecoder Extends TAudioStreamDecoder
	Field stream:TStream
	Field dataPos:Long
	Field position:Long
	Field align:Int
	Field bits:Int
	Field bytes:Byte[]

	Method ReadFrames:Int(output:Float[], count:Int) Override
		If Not stream Then Throw "WAV decoder is closed"
		If count < 0 Or count > output.length / channels Then Throw "Audio output buffer is too small"
		count = Int(Min(Long(count), frames - position))
		If Not count Then Return 0
		If count > 2147483647 / align Then Throw "Audio read is too large"
		Local length:Int = count * align
		If bytes.length < length Then bytes = New Byte[length]
		ReadExact(stream, bytes, length)
		Local offset:Int
		For Local i:Int = 0 Until count * channels
			Select bits
				Case 8
					output[i] = (Int(bytes[offset]) - 128) / 128.0
				Case 16
					Local value:Int = LE16(bytes, offset)
					If value >= 32768 Then value :- 65536
					output[i] = value / 32768.0
				Case 24
					Local value:Int = Int(bytes[offset]) | (Int(bytes[offset + 1]) Shl 8) | (Int(bytes[offset + 2]) Shl 16)
					If value >= 8388608 Then value :- 16777216
					output[i] = value / 8388608.0
				Case 32
					Local value:Long = LE32(bytes, offset)
					If value >= 2147483648:Long Then value :- 4294967296:Long
					output[i] = Float(value / 2147483648.0:Double)
			End Select
			offset :+ bits / 8
		Next
		position :+ count
		Return count
	End Method

	Method SeekFrame:Int(frame:Long) Override
		If Not stream Or frame < 0 Or frame > frames Then Return False
		Local offset:Long = dataPos + frame * align
		If stream.Seek(offset) <> offset Then Return False
		position = frame
		Return True
	End Method

	Method Close() Override
		stream = Null
		bytes = Null
	End Method
End Type

Function ReadSome:Int(stream:TStream, data:Byte[], count:Int)
	Local offset:Int
	While offset < count
		Local amount:Long = stream.Read(Varptr data[offset], count - offset)
		If amount < 0 Or amount > count - offset Then Throw "Invalid audio stream read result"
		If Not amount Then Exit
		offset :+ Int(amount)
	Wend
	Return offset
End Function

Function ReadExact(stream:TStream, data:Byte[], count:Int)
	If ReadSome(stream, data, count) <> count Then Throw "Truncated WAV audio"
End Function

Function LE16:Int(data:Byte[], offset:Int)
	Return Int(data[offset]) | (Int(data[offset + 1]) Shl 8)
End Function

Function LE32:Long(data:Byte[], offset:Int)
	Return Long(data[offset]) | (Long(data[offset + 1]) Shl 8) | (Long(data[offset + 2]) Shl 16) | (Long(data[offset + 3]) Shl 24)
End Function

Function Tag:String(data:Byte[], offset:Int)
	Return Chr(data[offset]) + Chr(data[offset + 1]) + Chr(data[offset + 2]) + Chr(data[offset + 3])
End Function

New TWavStreamProvider
