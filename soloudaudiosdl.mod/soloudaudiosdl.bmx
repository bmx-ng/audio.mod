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

Module Audio.SoloudAudioSDL

Import Audio.SoloudSDL
Import Audio.SoloudAudio


?win32
New TDirectSoundSoloudAudioDriver
New TWinmMMSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TSDLSoloudAudioDriver Extends TSoloudAudioDriver
	Method Backend:Int()
		Return SOLOUD_SDL2
	End Method
End Type

Type TDirectSoundSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$()
		Return "SoLoud::DirectSound"
	End Method

	Method Startup:Int()
		SDLAudioInit("directsound")
		Return Super.Startup()
	End Method
	
End Type

Type TWinmMMSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$()
		Return "SoLoud::WinMM"
	End Method

	Method Startup:Int()
		SDLAudioInit("winmm")
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
New TOSSSoloudAudioDriver
New TNASSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TALSASoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$()
		Return "SoLoud::ALSA"
	End Method

	Method Startup:Int()
		SDLAudioInit("alsa")
		Return Super.Startup()
	End Method
	
End Type

Type TPulseAudioSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$()
		Return "SoLoud::PulseAudio"
	End Method

	Method Startup:Int()
		SDLAudioInit("pulseaudio")
		Return Super.Startup()
	End Method
	
End Type

Type TOSSSoloudAudioDriver Extends TSoloudAudioDriver

	Method Name$()
		Return "SoLoud::OSS"
	End Method

	Method Startup:Int()
		SDLAudioInit("dsp")
		Return Super.Startup()
	End Method
	
End Type

Type TNASSoloudAudioDriver Extends TSoloudAudioDriver

	Method Name$()
		Return "SoLoud::NAS"
	End Method

	Method Startup:Int()
		SDLAudioInit("nas")
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

Type TCoreAudioSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$()
		Return "SoLoud::CoreAudio"
	End Method

	Method Startup:Int()
		SDLAudioInit("coreaudio")
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TCoreAudioSoloudAudioDriver

	Method Name$()
		Return "SoLoud"
	End Method

End Type
?
