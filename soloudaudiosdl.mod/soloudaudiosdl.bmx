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

Type TSDLSoloudAudioDriver Extends TSoloudAudioDriver
	Method Backend:Int() Override
		Return SOLOUD_SDL2
	End Method
End Type

?win32
New TDirectSoundSoloudAudioDriver
New TWinmMMSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TDirectSoundSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::DirectSound"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("directsound")
		Return Super.Startup()
	End Method
	
End Type

Type TWinmMMSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::WinMM"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("winmm")
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TDirectSoundSoloudAudioDriver

	Method Name$() Override
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

	Method Name$() Override
		Return "SoLoud::ALSA"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("alsa")
		Return Super.Startup()
	End Method
	
End Type

Type TPulseAudioSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::PulseAudio"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("pulseaudio")
		Return Super.Startup()
	End Method
	
End Type

Type TOSSSoloudAudioDriver Extends TSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::OSS"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("dsp")
		Return Super.Startup()
	End Method
	
End Type

Type TNASSoloudAudioDriver Extends TSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::NAS"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("nas")
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TPulseAudioSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud"
	End Method

End Type
?macos
New TCoreAudioSoloudAudioDriver
New TDefaultSoloudAudioDriver

Type TCoreAudioSoloudAudioDriver Extends TSDLSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud::CoreAudio"
	End Method

	Method Startup:Int() Override
		SDLAudioInit("coreaudio")
		Return Super.Startup()
	End Method
	
End Type

Type TDefaultSoloudAudioDriver Extends TCoreAudioSoloudAudioDriver

	Method Name$() Override
		Return "SoLoud"
	End Method

End Type
?
