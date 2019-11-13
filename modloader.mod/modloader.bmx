SuperStrict

Module Audio.modloader

Import Audio.SoloudAudio

Import "common.bmx"


Rem
bbdoc: 
End Rem
Type TSLOpenmpt Extends TSLLoadableAudioSource

	Method New()
		asPtr = Openmpt_create()
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Load:Int(filename:String)
		Local s:Byte Ptr = filename.ToUTF8String()
		Local res:Int = Openmpt_load(asPtr, s)
		MemFree(s)
		Return res
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method loadMem:Int(data:Byte Ptr, dataLen:Int, copy:Int = False, takeOwnership:Int = True)
		Return Openmpt_loadMemEx(asPtr, data, dataLen, copy, takeOwnership)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method loadStream:Int(stream:TStream)
		Local sf:TStreamFile = New TStreamFile.Create(stream)
		Return Openmpt_LoadFile(asPtr, sf.filePtr)
	End Method

	Rem
	bbdoc: Sets default volume for instances.
	End Rem
	Method setVolume(volume:Float)
		Openmpt_setVolume(asPtr, volume)
	End Method
	
	Rem
	bbdoc: Sets the looping of the instances created from this audio source.
	End Rem
	Method setLooping(loop:Int)
		Openmpt_setLooping(asPtr, loop)
	End Method

	Rem
	bbdoc: Sets the minimum and maximum distances for 3d audio source (closer to min distance = max vol)
	End Rem
	Method set3dMinMaxDistance(minDistance:Float, maxDistance:Float)
		Openmpt_set3dMinMaxDistance(asPtr, minDistance, maxDistance)
	End Method
	
	Rem
	bbdoc: Sets attenuation model and rolloff factor for 3d audio source.
	End Rem
	Method set3dAttenuation(attenuationModel:Int, attenuationRolloffFactor:Float)
		Openmpt_set3dAttenuation(asPtr, attenuationModel, attenuationRolloffFactor)
	End Method

	Rem
	bbdoc: Sets doppler factor to reduce or enhance doppler effect, default = 1.0
	End Rem
	Method set3dDopplerFactor(dopplerFactor:Float)
		Openmpt_set3dDopplerFactor(asPtr, dopplerFactor)
	End Method

	Rem
	bbdoc: Enables 3d processing.
	about: Implicitly set by play3d calls.
	End Rem
	Method set3dListenerRelative(listenerRelative:Int)
		Openmpt_set3dListenerRelative(asPtr, listenerRelative)
	End Method

	Rem
	bbdoc: Sets the coordinates for this audio source to be relative to listener's coordinates.
	End Rem
	Method set3dDistanceDelay(distanceDelay:Int)
		Openmpt_set3dListenerRelative(asPtr, distanceDelay)
	End Method

	Rem
	bbdoc: Enables delaying the start of the sound based on the distance.
	End Rem
	Method set3dCollider(collider:TSLAudioCollider)
		' TODO
	End Method

	Rem
	bbdoc: Sets a custom 3d audio collider.
	about: Set to Null to disable.
	End Rem
	Method set3dColliderEx(collider:TSLAudioCollider, userData:Int)
		' TODO
	End Method

	Rem
	bbdoc: Sets a custom attenuator.
	about: Set to Null to disable.
	End Rem
	Method set3dAttenuator(attenuator:TSLAudioAttenuator)
		' TODO
	End Method

	Rem
	bbdoc: Sets behavior for inaudible sounds.
	End Rem
	Method setInaudibleBehavior(mustTick:Int, kill:Int)
		Openmpt_setInaudibleBehavior(asPtr, mustTick, kill)
	End Method

	Rem
	bbdoc: Sets filter.
	about: Set to NULL to clear the filter.
	End Rem
	Method setFilter(filterId:Int, filter:TSLFilter)
		' TODO
	End Method

	Rem
	bbdoc: Stops all instances of this audio source.
	End Rem
	Method stop()
		Openmpt_stop(asPtr)
	End Method

	Method destroy()
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

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream )
		Local sound:TSLLoadableAudioSource = New TSLOpenmpt
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type
