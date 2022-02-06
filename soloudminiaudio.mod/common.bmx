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

Enum EMaBackend
	ma_backend_wasapi
    ma_backend_dsound
    ma_backend_winmm
    ma_backend_coreaudio
    ma_backend_sndio
    ma_backend_audio4
    ma_backend_oss
    ma_backend_pulseaudio
    ma_backend_alsa
    ma_backend_jack
    ma_backend_aaudio
    ma_backend_opensl
    ma_backend_webaudio
    ma_backend_custom '  <-- Custom backend, with callbacks defined by the context config.
    ma_backend_null    ' <-- Must always be the last item. Lowest priority, and used as the terminator for backend enumeration. 
End Enum
