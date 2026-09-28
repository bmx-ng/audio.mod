SuperStrict

Import BRL.Stream

Rem
bbdoc: Stream callback adapter for incremental decoder providers.
about: Borrows a seekable stream with a known size. Offsets are relative to its starting position. Read/Seek/Tell callbacks capture failures; call Check after native decoder operations. Use from one decoding thread at a time.
End Rem
Type TAudioDecoderInput
	Field stream:TStream
	Field origin:Long
	Field length:Long
	Field failure:String

	Function Create:TAudioDecoderInput(stream:TStream)
		Local input:TAudioDecoderInput = New TAudioDecoderInput
		input.stream = stream
		input.origin = stream.Pos()
		input.length = stream.Size() - input.origin
		If input.origin < 0 Or input.length < 0 Then Throw "Audio decoder requires a seekable input with a known size"
		Return input
	End Function

	Method Check()
		If failure Then Throw failure
	End Method

	Function Read:Long(value:Object, output:Byte Ptr, count:Long)
		Local input:TAudioDecoderInput = TAudioDecoderInput(value)
		If input.failure Then Return -1
		Try
			Local position:Long = input.stream.Pos() - input.origin
			If position < 0 Or position > input.length Then Throw "Invalid audio decoder input position"
			count = Min(count, input.length - position)
			Local total:Long
			While total < count
				Local amount:Long = input.stream.Read(output + total, count - total)
				If amount < 0 Or amount > count - total Then Throw "Invalid audio decoder input read result"
				If Not amount Then Throw "Truncated audio decoder input"
				total :+ amount
			Wend
			Return total
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function

	Function Seek:Int(value:Object, offset:Long, whence:Int)
		Local input:TAudioDecoderInput = TAudioDecoderInput(value)
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
			If base < 0 Or base > input.length Then Throw "Invalid audio decoder seek origin"
			If offset < -base Or offset > input.length - base Then Return -1
			Local target:Long = input.origin + base + offset
			If input.stream.Seek(target) <> target Then Throw "Unable to seek audio decoder input"
			Return 0
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function

	Function Tell:Long(value:Object)
		Local input:TAudioDecoderInput = TAudioDecoderInput(value)
		If input.failure Then Return -1
		Try
			Return input.stream.Pos() - input.origin
		Catch error:Object
			input.failure = error.ToString()
			Return -1
		End Try
	End Function
End Type
