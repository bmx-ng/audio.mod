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

Import Audio.Soloud

?linux
Import "-ldl"
?
Import "source.bmx"

Private
Extern
	Function miniaudio_stub()
	
End Extern

Function _miniaudio_stub()
	miniaudio_stub()
End Function

Public

Const MA_BACKEND_WASAPI:Int = 0
Const MA_BACKEND_DSOUND:Int = 1
Const MA_BACKEND_WINMM:Int = 2
Const MA_BACKEND_COREAUDIO:Int = 4
Const MA_BACKEND_SNDIO:Int = 5
Const MA_BACKEND_AUDIO4:Int = 6
Const MA_BACKEND_OSS:Int = 7
Const MA_BACKEND_PULSEAUDIO:Int = 8
Const MA_BACKEND_ALSA:Int = 9
Const MA_BACKEND_JACK:Int = 10
Const MA_BACKEND_AAUDIO:Int = 11
Const MA_BACKEND_OPENSL:Int = 12
Const MA_BACKEND_WEBAUDIO:Int = 13
Const MA_BACKEND_NULL:Int = 14
