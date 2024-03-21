SuperStrict

Framework SDL.SDLRenderMax2d

'
' Choose SDL or MiniAudio backend
Import Audio.AudioSDL
'Import Audio.AudioMiniAudio

Graphics 800,600,0

Global sound:TSound = LoadSound(Null, SOLOUD_SOUND_QUEUED)

Local driver:TSoloudAudioDriver = TSoloudAudioDriver(GetAudioDriver())
Local so:TSoLoud = driver._soloud

Local queue:TSLQueued = TSLQueued(TSoloudSound(sound)._sound)

'Local buf:Byte[]
' create a  buffer with 1 second of sine wave at 44100hz C5, where Sin() takes degrees
Local sampleRate:Int = 44100
Local frequency:Float = sampleRate / 168.0
Local samplesForOneSecond:Int = sampleRate * 2

' create byte buffer large enough to hold the float samples
Local data:Byte[samplesForOneSecond * 4] 

' create a float pointer to the byte buffer
Local floatPtr:Float Ptr = Float Ptr(data)

For Local i:Int = 0 Until samplesForOneSecond
	Local sample:Float = Sin(i * (360.0 * frequency / sampleRate))
	floatPtr[i] = sample ' store the float sample directly
Next

queue.writeData(data, size_t(samplesForOneSecond * 4))
queue.writeData(data, size_t(samplesForOneSecond * 4))

so.setVisualizationEnable(True)

Global channel:TChannel = PlaySound(sound)
Local volume:Float = 1

Local ms:Int = MilliSecs()

While not keydown(KEY_ESCAPE)
	Cls

	Local ts:Int = MilliSecs()
	local size:Size_T = queue.size()

	If size < 20000 Then
		queue.writeData(data, size_t(samplesForOneSecond * 4))
		ms = ts
	EndIf

	Local StaticArray wavData:Float[256]
	Local StaticArray fftData:Float[256]
	Local buf:Float Ptr = so.getWave()
	MemCopy(wavData, buf, 246 * 4)
	buf = so.calcFFT()
	MemCopy(fftData, buf, 256 * 4)
	
	SetColor(255, 255, 255)

	DrawText samplesForOneSecond * 4, 10, 10
	DrawText size, 10, 20

	For Local i:int = 0 Until 256
		Local d:Float = wavData[i]
		Local height:Float = d * 128
		If d > 0 Then
			DrawRect( 30 + i * 3, 200 - height, 3, height )
		Else
			DrawRect( 30 + i * 3, 200, 3, Abs(height) )
		End If
	Next

	SetColor(248, 58, 10)
	For Local i:int = 0 Until 246
		Local d:Float = fftData[i]
		Local height:Float = Min(200, d * 2)

		DrawRect( 30 + i * 3, 200 - height, 2, height )
	Next

	SetColor(255, 255, 255)

	Local y:Int = 350
	DrawRect(20, y, 760, 20)

	SetColor(0, 0, 0)
	DrawRect(21, y + 1, 758, 18)


	Flip

Wend
