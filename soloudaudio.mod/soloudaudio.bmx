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
bbdoc: Soloud Audio Driver
about: Provides Soloud driver for use with the BRL.Audio module.
End Rem
Module Audio.soloudaudio

ModuleInfo "Version: 1.03"
ModuleInfo "License: zlib/libpng"
ModuleInfo "Copyright: 2016-2023 Bruce A Henderson"

ModuleInfo "History: 1.03"
ModuleInfo "History: Added support for Sfxr loading (.sfxr) and generation (preset, seed)."
ModuleInfo "History: 1.02"
ModuleInfo "History: Fixed loader priority ordering."
ModuleInfo "History: 1.01"
ModuleInfo "History: Added support for Ay (in .zap format) loading."
ModuleInfo "History: 1.00"
ModuleInfo "History: Initial Release."

Import Audio.soloud
Import BRL.Audio
Import brl.filesystem

Private

Global _driver:TSoloudAudioDriver

Public


Const SOLOUD_SOUND_WAV:Int =       $00001000
Const SOLOUD_SOUND_WAVSTREAM:Int = $00002000
Const SOLOUD_SOUND_SFXR:Int =      $00004000
Const SOLOUD_SOUND_OPENMPT:Int =   $00008000
Const SOLOUD_SOUND_MONOTONE:Int =  $00010000
Const SOLOUD_SOUND_TEDSID:Int =    $00020000
Const SOLOUD_SOUND_SPEECH:Int =    $00040000
Const SOLOUD_SOUND_AY:Int =        $00080000
Const SOLOUD_SOUND_QUEUED:Int =    $00800000

Const SOLOUD_SOUND_PAUSE_INAUDIBLE:Int = $10000000
Const SOLOUD_SOUND_PROTECT:Int = $20000000

Type TSoloudAudioDriver Extends TAudioDriver

	Field _soloud:TSoloud

	Method Name:String()
		Return "SoLoud"
	End Method
	
	Method Startup:Int()
		_soloud = New TSoloud

		_soloud.init(, Backend())

		_driver = Self
		
		Return True
	End Method
	
	Method Shutdown()
		Local soloud:TSoloud = _soloud
		_soloud = Null
		
		soloud.deinit()
		_driver = Null
	End Method

	Method CreateSound:TSound( sample:TAudioSample, loopFlag:Int )
		'Return New TSound
	End Method

	Method LoadSound:TSound( url:Object, flags:Int = 0)
		Return TSoloudSound.Load(url, flags)
	End Method

	Method AllocChannel:TChannel()
		Return New TSoloudChannel
	End Method

	Method Backend:Int() Abstract
	
End Type

Type TSoloudSound Extends TSound

	Field _sound:TSLAudioSource
	Field isLooped:Int
	Field pauseInaudible:Int
	Field isProtected:Int

	Method Play:TChannel( allocedChannel:TChannel=Null )
		Return StartSound(allocedChannel, False)
	End Method
	
	Method Cue:TChannel( allocedChannel:TChannel=Null )
		Return StartSound(allocedChannel, True)
	End Method
	
	Method StartSound:TChannel(allocedChannel:TChannel=Null, pause:Int = False)
		If isLooped Then
			_sound.SetLooping(True)
		End If

		If Not pauseInaudible
			_sound.setInaudibleBehavior(True, False)
		End If

		Local voiceHandle:Int = _driver._soloud.play(_sound, -1, 0, True)

		Local channel:TChannel
		If Not allocedChannel Then
			channel = New TSoloudChannel.Create(_driver._soloud, voiceHandle, _sound)
		Else
			TSoloudChannel(allocedChannel).Set(_driver._soloud, voiceHandle, _sound)
			channel = allocedChannel
		End If

		If isProtected Then
			TSoloudChannel(channel).SetProtected(isProtected)
		End If
		
		If Not pause Then
			channel.SetPaused(False)
		End If
		
		Return channel
	End Method
	
	Function Load:TSound( url:Object, loopFlag:Int )

		If loopFlag & SOLOUD_SOUND_SPEECH Then
			Local this:TSoloudSound = New TSoloudSound
			this._sound = New TSLSpeech
			TSLSpeech(this._sound).SetText(String(url))

			If loopFlag & SOUND_LOOP Then
				this.isLooped = True
			End If

			Return this
		End If

		If loopFlag & SOLOUD_SOUND_QUEUED Then
			Local this:TSoloudSound = New TSoloudSound
			this._sound = New TSLQueued

			If loopFlag & SOUND_LOOP Then
				this.isLooped = True
			End If

			Return this
		End If
	
		Local sound:TSLLoadableAudioSource
		
		If loopFlag & SOLOUD_SOUND_WAV Then
			sound = New TSLWav
		Else If loopFlag & SOLOUD_SOUND_WAVSTREAM Then
			sound = New TSLWavStream
		Else If loopFlag & SOLOUD_SOUND_SFXR Then
			sound = New TSLSfxr
		Else If loopFlag & SOLOUD_SOUND_MONOTONE Then
			sound = New TSLMonotone
		Else If loopFlag & SOLOUD_SOUND_TEDSID Then
			sound = New TSLTedSid
		Else If loopFlag & SOLOUD_SOUND_AY Then
			sound = New TSLAy
		End If
		
		Local this:TSoloudSound = New TSoloudSound
		If sound Then
			this._sound = sound
		End If

		If loopFlag & SOUND_LOOP Then
			this.isLooped = True
		End If
		
		If loopFlag & SOLOUD_SOUND_PAUSE_INAUDIBLE Then
			this.pauseInaudible = True
		End If

		Local stream:TStream
		If String(url) Then
			'sfxr also allows a "long key" to store the preset/seed setup
			If loopFlag & SOLOUD_SOUND_SFXR And String(Long(String(url))) = String(url) Then
				'unpack preset/effect from url
				Local key:Long = Long(String(url))
				Local preset:Int = (key Shr 32) & $FFFFFFFF
				Local seed:Int = key & $FFFFFFFF
				sfxr_loadPreset( this._sound.asPtr, preset, seed )
				
				Return this
			EndIf

			stream = ReadStream(url)
			If Not stream Then
				Return Null
			End If
		Else If TStream(url) Then
			stream = TStream(url)
		End If
			
		If stream Then
			If Not sound Then
				this._sound = TryLoadSound(stream, loopFlag)
				
				If Not this._sound Then
					Return Null
				End If
				
				Return this
			End If
			
			If sound Then
				Local res:Int = sound.loadStream(stream)
				If res Then
					Return Null
				End If
				
				Return this
			End If
		End If
		
		Return this

	End Function
	
	Function TryLoadSound:TSLLoadableAudioSource(stream:TStream, flags:Int)
		If Not stream Then Return Null

		Local sound:TSLLoadableAudioSource
		Local loader:TAudioSourceLoader = audio_loaders

		Local pos:Int = stream.Pos()
		
		While loader
			'reset to initial position for each loader attempt
			stream.Seek(pos)
			
			sound = loader.LoadAudioSource(stream, flags)
			If sound Then Exit
			
			loader = loader._succ
		Wend
		
		Return sound
	End Function
	
End Type

Type TSoloudChannel Extends TChannel

	Field _soloud:TSoloud
	Field _voiceHandle:Int
	
	Field _sound:TSLAudioSource

	' since we can "alloc" a channel, it won't yet have a _channel object.. which will be added later.
	' so, any settings changed need to be cached and applied when initialized
	Field prePaused:Int
	Field preVolume:Float
	Field prePan:Float
	Field preRate:Float
	Field preflags:Int
	
	Field APPLY_PAUSED:Int = 1
	Field APPLY_VOLUME:Int = 2
	Field APPLY_PAN:Int = 4
	Field APPLY_RATE:Int = 8
	
	Method Create:TSoloudChannel(soloud:TSoloud, voiceHandle:Int, sound:TSLAudioSource)
		_soloud = soloud
		_voiceHandle = voiceHandle
		_sound = sound
		Return Self
	End Method

	' - usually applied if this object was created with AllocChannel()
	Method Set(soloud:TSoloud, voiceHandle:Int, sound:TSLAudioSource)
		_soloud = soloud
		_voiceHandle = voiceHandle
		_sound = sound
		
		If preflags & APPLY_PAUSED Then
			SetPaused(prePaused)
		End If

		If preflags & APPLY_VOLUME Then
			SetVolume(preVolume)
		End If

		If preflags & APPLY_PAN Then
			SetPan(prePan)
		End If

		If preflags & APPLY_RATE Then
			SetRate(preRate)
		End If
	End Method

	Method Stop() Override
		If _voiceHandle Then
			_soloud.stop(_voiceHandle)
		End If
	End Method

	Method SetPaused( paused:Int ) Override
		If _voiceHandle Then
			_soloud.setPause(_voiceHandle, paused)
		Else
			preflags:| APPLY_PAUSED
			prePaused = paused
		End If
	End Method

	Method SetVolume( volume:Float ) Override
		If _voiceHandle Then
			_soloud.setVolume(_voiceHandle, volume)
		End If
		preflags:| APPLY_VOLUME
		preVolume = volume
	End Method

	Method SetPan( pan:Float ) Override
		If _voiceHandle Then
			_soloud.setPan(_voiceHandle, pan)
		End If
		preflags:| APPLY_PAN
		prePan = pan
	End Method

	Method SetDepth( depth:Float ) Override
		' TODO ?
	End Method

	Method SetRate( rate:Float ) Override
		If _voiceHandle Then
			_soloud.setSamplerate(_voiceHandle, rate)
		End If
		preflags:| APPLY_RATE
		preRate = rate
	End Method

	Method Playing:Int() Override
		If _voiceHandle Then
			Return _soloud.isValidVoiceHandle(_voiceHandle) And Not _soloud.getPause(_voiceHandle)
		Else
			Return False
		End If
	End Method

	Method Position:Int()
		If _voiceHandle Then
			Return Int(_soloud.getStreamPosition(_voiceHandle) * 1000)
		Else
			Return 0
		End If
	End Method

	Method StreamTime:Int()
		If _voiceHandle Then
			Return Int(_soloud.getStreamTime(_voiceHandle) * 1000)
		Else
			Return 0
		End If
	End Method
	
	Method LoopCount:Int()
		If _voiceHandle Then
			Return _soloud.getLoopCount(_voiceHandle)
		Else
			Return 0
		End If
	End Method
	
	Method Length:Int()
		If _sound Then
			Return Int(_sound.getLength() * 1000)
		Else
			Return -1
		End If
	End Method
	
	Method SetProtected(protect:Int)
		If _voiceHandle Then
			_soloud.setProtectVoice(_voiceHandle, protect)
		End If
	End Method
End Type

Private
Global audio_loaders:TAudioSourceLoader
Public

New TSoloudWavLoader(5)
New TSoloudMonotoneLoader(10)
New TSoloudAyLoader(15)
New TSoloudSfxrLoader(20)

Rem
bbdoc: 
End Rem
Type TAudioSourceLoader
	Field _succ:TAudioSourceLoader
	Field _priority:Int
	
	Method New(priority:Int)
		Self._priority = priority
		Local loader:TAudioSourceLoader = audio_loaders
		Local last:TAudioSourceLoader
		While loader
			If priority <= loader._priority Then
				_succ=audio_loaders
				audio_loaders=Self
				Return
			End If
			
			last = loader
			loader = loader._succ
		Wend
		
		If last Then
			If last._succ Then Throw "Unexpected audio loader entry"
			last._succ = Self
		Else
			audio_loaders = Self
		End If
	End Method
	
	Rem
	bbdoc: Load an audio sample
	returns: A new audio sample object, or Null if sample could not be loaded
	about: Extending types must implement this method.
	End Rem
	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int ) Abstract
End Type

Type TSoloudWavLoader Extends TAudioSourceLoader

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int )
		Local sound:TSLLoadableAudioSource

		If flags & SOUND_STREAM Then
			sound = New TSLWavStream
			If sound.loadStream(stream) = SO_NO_ERROR Then
				Return sound
			End If
			sound.destroy()
		End If
		
		sound = New TSLWav
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type

Type TSoloudMonotoneLoader Extends TAudioSourceLoader

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int )
		Local sound:TSLLoadableAudioSource = New TSLMonotone
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type

Type TSoloudAyLoader Extends TAudioSourceLoader

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int )
		Local sound:TSLLoadableAudioSource = New TSLAy
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type

Type TSoloudSfxrLoader Extends TAudioSourceLoader

	Method LoadAudioSource:TSLLoadableAudioSource( stream:TStream, flags:Int )
		Local sound:TSLLoadableAudioSource = New TSLSfxr
		If sound.loadStream(stream) = SO_NO_ERROR Then
			Return sound
		End If
		sound.destroy()
	End Method
	
End Type


Function GenerateSfxrUrl:String(preset:Int, seed:Int)
	Local key:Long = Long(preset) shl 32 | Long(seed)
	Return string(key)
End Function


Function LoadSfxrSound:TSound(preset:Int, seed:Int, flags:Int = 0)
	Return TSoloudSound.Load( GenerateSfxrUrl(preset, seed), flags | SOLOUD_SOUND_SFXR )
End Function