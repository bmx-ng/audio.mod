# BlitzMax Audio 

The `Audio` modules provide a more comprehensive audio experience in BlitzMax than the original and default audio drivers, adding support for more backends, more audio file types, and streaming.



The `Audio` framework is built on top of the open source [SoLoud](https://sol.gfxile.net/soloud/) audio engine, which itself integrates with various different audio formats and libraries.

## Supported Audio Formats

### Wave Sounds

Wave sounds are sound files loaded directly into memory. These are converted to float samples, which means that every second of a 44100Hz stereo sound takes about 350kB of memory. Although  they require a lot of memory, processing them requires very few resources.

Because of the memory requirements, these are more suited to sound effects and short clips, rather than long audio tracks. For large samples, consider using Streaming.

The following file formats are supported : `wav`, `flac`, `mp3`, and `ogg`.

### Streaming

Streaming allows audio to be played directly from the device by loading a section of it at a time. Although this requires more resources to process the audio, it uses much less memory.

The following file formats can be streamed : `wav`, `flac`, `mp3`, and `ogg`.

### MODs

By importing `Audio.ModLoader`, you gain access to a multitude of MOD/tracker music, with support for the following MOD file formats:  `669`, `amf`, `ams`, `dbm`, `digi`, `dmf`, `dsm`, `far`, `gdm`, `ice`, `imf`, `it`, `itp`, `j2b`, `m15`, `mdl`, `med`, `mid`, `mo3`, `mod`, `mptm`, `mt2`, `mtm`, `okt`, `plm`, `psm`, `ptm`, `s3m`, `stm`, `ult`, `umx`, `wow` and `xm`.



## Selecting an Audio Driver

Depending on what platform you are targeting and what system backend you are using there are up to two audio drivers available to choose from.

Different audio backends are available on different platforms, and for Linux specifically, only if the relevant packages have been installed on the system.

Each has a "default" backend which will be automatically enabled when audio is initialised.

### Audio.AudioSDL
This driver is only available if the SDL backend for rendering and events is in use, although it's not specifically required if you are using the SDL backend.

#### Available Backends

Win32

* `SoLoud::DirectSound` / `SoLoud` (default)
* `SoLoud::WinMM`

Linux

* `SoLoud::ALSA`
* `SoLoud::PulseAudio` / `SoLoud` (default)
* `SoLoud::OSS`
* `SoLoud::NAS`

macOS

* `SoLoud::CoreAudio` / `SoLoud` (default)


### Audio.AudioMiniAudio

This driver is backed by the [MiniAudio](https://github.com/dr-soft/miniaudio)  library.

#### Available Backends

Win32

* `SoLoud::DirectSound` / `SoLoud` (default)
* `SoLoud::WinMM`
* `SoLoud::WASAPI`

Linux

* `SoLoud::ALSA`
* `SoLoud::PulseAudio` / `SoLoud` (default)
* `SoLoud::JACK`

macOS

* `SoLoud::CoreAudio` / `SoLoud` (default)


## Examples

The following highlight some basic examples of using the Audio modules.

See [BRL.Audio](https://blitzmax.org/docs/en/api/brl/brl.audio/) for more detailed examples of TSound and TChannel usage.

### Listing Drivers

Output the names of available audio drivers on the current platform.
```blitzmax
SuperStrict

Framework audio.AudioMiniAudio
Import BRL.StandardIO

Local drivers:String[] = AudioDrivers()

Print "Available Audio Drivers : "
For Local i:Int = 0 Until drivers.length
	Print "~t" + drivers[i]
Next
```

### Playing a Sound

```blitzmax
SuperStrict

Framework audio.AudioMiniAudio

Local sound:TSound = LoadSound("crash.ogg")
Local channel:TChannel = PlaySound(sound)

Repeat
    Delay 100
Until Not channel.Playing()
```

### Streaming a Sound

```blitzmax
SuperStrict

Framework audio.AudioMiniAudio

Local sound:TSound = LoadSound("music.ogg", SOUND_STREAM)
Local channel:TChannel = PlaySound(sound)

Repeat
    Delay 100
Until Not channel.Playing()
```

