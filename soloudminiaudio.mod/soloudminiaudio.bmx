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

Module Audio.SoloudMiniAudio

ModuleInfo "Version: 1.00"
ModuleInfo "License: zlib/libpng"
ModuleInfo "Copyright: SoLoud - 2013-2020 Jari Komppa"
ModuleInfo "Copyright: Wrapper - 2016-2020 Bruce A Henderson"

ModuleInfo "History: 1.00"
ModuleInfo "History: Initial Release."

?win32x86
ModuleInfo "CC_OPTS: -msse2"
?win32x64
ModuleInfo "CC_OPTS: -msse3"
?linuxx86
ModuleInfo "CC_OPTS: -msse2"
?linuxx64
ModuleInfo "CC_OPTS: -msse3"
?
ModuleInfo "CC_OPTS: -DWITH_SDL2_STATIC"
ModuleInfo "CC_OPTS: -DWITH_MINIAUDIO"
ModuleInfo "CC_OPTS: -DMA_NO_WAV"

Import "common.bmx"

Function MiniAudioInit(backend:Int)
	bmx_soloud_miniaudio_context_init(backend)
End Function

Private
Extern
	Function bmx_soloud_miniaudio_context_init(backend:Int)
End Extern
