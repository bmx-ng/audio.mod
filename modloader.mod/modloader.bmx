' Copyright (c) 2016-2022 Bruce A Henderson
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
bbdoc: Mod music loader.
End Rem
Module Audio.ModLoader

Import Audio.SoloudAudio

Import "common.bmx"


Rem
bbdoc: Audio source for Openmpt supported music.
about: Formats include 669, amf, ams, dbm, digi, dmf, dsm, far, gdm, ice, imf, it, itp, j2b, m15,
mdl, med, mid, mo3, mod, mptm, mt2, mtm, okt, plm, psm, ptm, s3m, stm, ult, umx, wow and xm.
End Rem
Type TSLOpenmpt Extends TSLLoadableAudioSource

	Method New()
		asPtr = Openmpt_create()
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Load:Int(filename:String) Override
		Local s:Byte Ptr = filename.ToUTF8String()
		Local res:Int = Openmpt_load(asPtr, s)
		MemFree(s)
		Return res
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method loadMem:Int(data:Byte Ptr, dataLen:Int, copy:Int = False, takeOwnership:Int = True) Override
		Return Openmpt_loadMemEx(asPtr, data, dataLen, copy, takeOwnership)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method loadStream:Int(stream:TStream) Override
		Local sf:TStreamFile = New TStreamFile.Create(stream)
		Return Openmpt_LoadFile(asPtr, sf.filePtr)
	End Method

	Rem
	bbdoc: Sets default volume for instances.
	End Rem
	Method setVolume(volume:Float) Override
		Openmpt_setVolume(asPtr, volume)
	End Method
	
	Rem
	bbdoc: Sets the looping of the instances created from this audio source.
	End Rem
	Method setLooping(loop:Int) Override
		Openmpt_setLooping(asPtr, loop)
	End Method

	Rem
	bbdoc: Set whether audio should auto-stop when it ends or not.
	End Rem
	Method setAutoStop(autoStop:Int) Override
		Openmpt_setAutoStop(asPtr, autoStop)
	End Method

	Rem
	bbdoc: Sets the minimum and maximum distances for 3d audio source (closer to min distance = max vol)
	End Rem
	Method set3dMinMaxDistance(minDistance:Float, maxDistance:Float) Override
		Openmpt_set3dMinMaxDistance(asPtr, minDistance, maxDistance)
	End Method
	
	Rem
	bbdoc: Sets attenuation model and rolloff factor for 3d audio source.
	End Rem
	Method set3dAttenuation(attenuationModel:Int, attenuationRolloffFactor:Float) Override
		Openmpt_set3dAttenuation(asPtr, attenuationModel, attenuationRolloffFactor)
	End Method

	Rem
	bbdoc: Sets doppler factor to reduce or enhance doppler effect, default = 1.0
	End Rem
	Method set3dDopplerFactor(dopplerFactor:Float) Override
		Openmpt_set3dDopplerFactor(asPtr, dopplerFactor)
	End Method

	Rem
	bbdoc: Enables 3d processing.
	about: Implicitly set by play3d calls.
	End Rem
	Method set3dListenerRelative(listenerRelative:Int) Override
		Openmpt_set3dListenerRelative(asPtr, listenerRelative)
	End Method

	Rem
	bbdoc: Sets the coordinates for this audio source to be relative to listener's coordinates.
	End Rem
	Method set3dDistanceDelay(distanceDelay:Int) Override
		Openmpt_set3dListenerRelative(asPtr, distanceDelay)
	End Method

	Rem
	bbdoc: Enables delaying the start of the sound based on the distance.
	End Rem
	Method set3dCollider(collider:TSLAudioCollider) Override
		' TODO
	End Method

	Rem
	bbdoc: Sets a custom 3d audio collider.
	about: Set to Null to disable.
	End Rem
	Method set3dColliderEx(collider:TSLAudioCollider, userData:Int) Override
		' TODO
	End Method

	Rem
	bbdoc: Sets a custom attenuator.
	about: Set to Null to disable.
	End Rem
	Method set3dAttenuator(attenuator:TSLAudioAttenuator) Override
		' TODO
	End Method

	Rem
	bbdoc: Sets behavior for inaudible sounds.
	End Rem
	Method setInaudibleBehavior(mustTick:Int, kill:Int) Override
		Openmpt_setInaudibleBehavior(asPtr, mustTick, kill)
	End Method

	Rem
	bbdoc: Sets filter.
	about: Set to NULL to clear the filter.
	End Rem
	Method setFilter(filterId:Int, filter:TSLFilter) Override
		' TODO
	End Method

	Rem
	bbdoc: Stops all instances of this audio source.
	End Rem
	Method stop() Override
		Openmpt_stop(asPtr)
	End Method

	Rem
	bbdoc: Returns the length of the audio source, in seconds.
	End Rem
	Method getLength:Double() Override
		Return Openmpt_getLength(asPtr)
	End Method

	Method destroy() Override
		If asPtr Then
			Openmpt_destroy(asPtr)
			asPtr = Null
		End If
	End Method

	Method Delete()
		destroy()
	End Method

End Type

New TSoloudModLoader(1)

Type TSoloudModLoader Extends TAudioSourceLoader

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int ) Override
		Local sound:TSLLoadableAudioSource = New TSLOpenmpt
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type
