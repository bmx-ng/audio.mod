SuperStrict

Framework SDL.SDLRenderMax2d

'
' Choose SDL or MiniAudio backend
'Import Audio.AudioSDL
Import Audio.AudioMiniAudio
Import Audio.ModLoader

Graphics 800,600,0

Global sounds:String[] = ["mods/STK.hobbyslakt",
		"mods/Crystal Score - Dance Of The Goblins.it",
		"mods/odyssey6.mod",
		"mods/2ND_PM.S3M"]

Global id:Int
Global sound:TSound = LoadSound(sounds[id])

Local driver:TSoloudAudioDriver = TSoloudAudioDriver(GetAudioDriver())
Local so:TSoLoud = driver._soloud

so.setVisualizationEnable(True)

Global channel:TChannel = PlaySound(sound)
Local volume:Float = 1

While not keydown(KEY_ESCAPE)
	Cls

	If KeyHit(KEY_SPACE) Then
		NextTrack()
		channel.SetVolume(volume)
	End If

	If KeyDown(Key_UP) Then
		volume :+ 0.02
		volume = Min(volume, 1)

		channel.SetVolume(volume)
	End If

	If KeyDown(Key_Down) Then
		volume :- 0.02
		volume = Max(volume, 0)

		channel.SetVolume(volume)
	End If

	Local StaticArray wavData:Float[256]
	Local StaticArray fftData:Float[256]
	Local buf:Float Ptr = so.getWave()
	MemCopy(wavData, buf, 246 * 4)
	buf = so.calcFFT()
	MemCopy(fftData, buf, 256 * 4)
	
	SetColor(255, 255, 255)

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

	Local length:Int = TSoloudChannel(channel).Length()

	Local pos:Int = TSoloudChannel(channel).Position()
	Local pps:Float = 758.0 / length

	If length - pos < 200 Then
		NextTrack()
	End If

	SetColor(27, 179, 27)

	DrawRect(21, y + 1, pps * pos, 18)

	SetColor(255, 255, 255)
	DrawText(TimeToTime(pos), 20, y + 25)
	DrawText(TimeToTime(length - pos), 747, y + 25)

	DrawRect(20, 400, 20, 80)
	SetColor(0,0,0)
	DrawRect(21, 401, 18, 78)
	length = 78 * volume

	SetColor(4, 136, 4)
	DrawRect(21, 401 + 78 - length, 18, length)

	Flip

Wend

Function NextTrack()
	channel.Stop()

	id :+ 1
	If id = sounds.Length Then
		id = 0
	End If

	sound = LoadSound(sounds[id])
	channel = PlaySound(sound)
End Function

Function TimeToTime:String(time:Int)
	Local t:Int = time / 1000
	Local mins:String = t / 60
	Local secs:String = t Mod 60
	Local pad:String
	If secs.Length < 2 Then
		pad = "0"
	End If
	Return mins + ":" + pad + secs
End Function
