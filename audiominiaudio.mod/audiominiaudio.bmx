' Copyright (c) 2016-2020 Bruce A Henderson
'
' This software is provided 'as-is', without any express or implied
' warranty. In no event will the authors be held liable for any damages
' arising from the use of this software.
'
' Permission is granted to anyone to use this software for any purpose,
' including commercial applications, and to alter it and redistribute it
' freely, subject to the following restrictions:
'
'    1. The origin of this software must not be misrepresented; you must not
'    claim that you wrote the original software. If you use this software
'    in a product, an acknowledgment in the product documentation would be
'    appreciated but is not required.
'
'    2. Altered source versions must be plainly marked as such, and must not be
'    misrepresented as being the original software.
'
'    3. This notice may not be removed or altered from any source
'    distribution.
'
SuperStrict

Rem
bbdoc: MiniAudio Audio driver.
End Rem
Module Audio.AudioMiniAudio

Import Audio.SoloudMiniAudio
Import Audio.SoloudAudio

Type TMiniAudioSoloudAudioDriver Extends TSoloudAudioDriver
	Method Backend:Int()
		Return SOLOUD_MINIAUDIO
	End Method
End Type

?win32
New TWASAPISoloudAudioDriver
New TDirectSoundSoloudAudioDriver
New TWinmMMSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TWASAPISoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::WASAPI"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_WASAPI)
		Return Super.Startup()
	End Method
	
End Type

Type TDirectSoundSoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::DirectSound"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_DSOUND)
		Return Super.Startup()
	End Method
	
End Type

Type TWinmMMSoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::WinMM"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_WINMM)
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TDirectSoundSoloudAudioDriver

	Method Name$()
		Return "SoLoud"
	End Method

End Type
?linux
New TALSASoloudAudioDriver
New TPulseAudioSoloudAudioDriver
New TJACKSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TALSASoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::ALSA"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_ALSA)
		Return Super.Startup()
	End Method
	
End Type

Type TPulseAudioSoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::PulseAudio"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_PULSEAUDIO)
		Return Super.Startup()
	End Method
	
End Type

Type TJACKSoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::JACK"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_JACK)
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TPulseAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud"
	End Method

End Type
?macos
New TCoreAudioSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TCoreAudioSoloudAudioDriver Extends TMiniAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud::CoreAudio"
	End Method

	Method Startup:Int()
		MiniAudioInit(MA_BACKEND_COREAUDIO)
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TCoreAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud"
	End Method

End Type
?

SetAudioDriver "SoLoud"
