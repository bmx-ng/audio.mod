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
Import Audio.libopenmpt

Import "../soloud.mod/soloud/include/*.h"

' audiosource - openmpt
Import "../soloud.mod/soloud/src/audiosource/openmpt/soloud_openmpt.cpp"

Import "openmptloader.cpp"

Extern
	' Openmpt
	Function Openmpt_destroy(aOpenmpt:Byte Ptr)
	Function Openmpt_create:Byte Ptr()
	Function Openmpt_load:Int(aOpenmpt:Byte Ptr, aFilename:Byte Ptr)
	Function Openmpt_loadMem:Int(aOpenmpt:Byte Ptr, aMem:Byte Ptr, aLength:Int)
	Function Openmpt_loadMemEx:Int(aOpenmpt:Byte Ptr, aMem:Byte Ptr, aLength:Int, aCopy:Int, aTakeOwnership:Int)
	Function Openmpt_loadFile:Int(aOpenmpt:Byte Ptr, aFile:Byte Ptr)
	Function Openmpt_setVolume(aOpenmpt:Byte Ptr, aVolume:Float)
	Function Openmpt_setLooping(aOpenmpt:Byte Ptr, aLoop:Int)
	Function Openmpt_setAutoStop(aOpenmpt:Byte Ptr, aAutoStop:Int)
	Function Openmpt_set3dMinMaxDistance(aOpenmpt:Byte Ptr, aMinDistance:Float, aMaxDistance:Float)
	Function Openmpt_set3dAttenuation(aOpenmpt:Byte Ptr, aAttenuationModel:Int, aAttenuationRolloffFactor:Float)
	Function Openmpt_set3dDopplerFactor(aOpenmpt:Byte Ptr, aDopplerFactor:Float)
	Function Openmpt_set3dListenerRelative(aOpenmpt:Byte Ptr, aListenerRelative:Int)
	Function Openmpt_set3dDistanceDelay(aOpenmpt:Byte Ptr, aDistanceDelay:Int)
	Function Openmpt_set3dCollider(aOpenmpt:Byte Ptr, aCollider:Byte Ptr)
	Function Openmpt_set3dColliderEx(aOpenmpt:Byte Ptr, aCollider:Byte Ptr, aUserData:Int)
	Function Openmpt_set3dAttenuator(aOpenmpt:Byte Ptr, aAttenuator:Byte Ptr)
	Function Openmpt_setInaudibleBehavior(aOpenmpt:Byte Ptr, aMustTick:Int, aKill:Int)
	Function Openmpt_setFilter(aOpenmpt:Byte Ptr, aFilterId:Int, aFilter:Byte Ptr)
	Function Openmpt_stop(aOpenmpt:Byte Ptr)
End Extern
