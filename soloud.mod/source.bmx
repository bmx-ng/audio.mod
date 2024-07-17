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

Import "soloud/include/*.h"

' core
Import "soloud/src/core/soloud_audiosource.cpp"
Import "soloud/src/core/soloud_bus.cpp"
Import "soloud/src/core/soloud_core_3d.cpp"
Import "soloud/src/core/soloud_core_basicops.cpp"
Import "soloud/src/core/soloud_core_faderops.cpp"
Import "soloud/src/core/soloud_core_filterops.cpp"
Import "soloud/src/core/soloud_core_getters.cpp"
Import "soloud/src/core/soloud_core_setters.cpp"
Import "soloud/src/core/soloud_core_voicegroup.cpp"
Import "soloud/src/core/soloud_core_voiceops.cpp"
Import "soloud/src/core/soloud_fader.cpp"
Import "soloud/src/core/soloud_fft_lut.cpp"
Import "soloud/src/core/soloud_fft.cpp"
Import "soloud/src/core/soloud_file.cpp"
Import "soloud/src/core/soloud_filter.cpp"
Import "soloud/src/core/soloud_misc.cpp"
Import "soloud/src/core/soloud_queue.cpp"
Import "soloud/src/core/soloud_thread.cpp"
Import "soloud/src/core/soloud.cpp"


' filter
Import "soloud/src/filter/soloud_bassboostfilter.cpp"
Import "soloud/src/filter/soloud_biquadresonantfilter.cpp"
Import "soloud/src/filter/soloud_dcremovalfilter.cpp"
Import "soloud/src/filter/soloud_echofilter.cpp"
Import "soloud/src/filter/soloud_eqfilter.cpp"
Import "soloud/src/filter/soloud_fftfilter.cpp"
Import "soloud/src/filter/soloud_flangerfilter.cpp"
Import "soloud/src/filter/soloud_freeverbfilter.cpp"
Import "soloud/src/filter/soloud_lofifilter.cpp"
Import "soloud/src/filter/soloud_robotizefilter.cpp"
Import "soloud/src/filter/soloud_waveshaperfilter.cpp"

' c api
Import "soloud/src/c_api/soloud_c_ay.cpp"
Import "soloud/src/c_api/soloud_c_bus.cpp"
Import "soloud/src/c_api/soloud_c_monotone.cpp"
Import "soloud/src/c_api/soloud_c_noise.cpp"
Import "soloud/src/c_api/soloud_c_queue.cpp"
Import "soloud/src/c_api/soloud_c_vizsn.cpp"
Import "soloud/src/c_api/soloud_c_wav.cpp"
Import "soloud/src/c_api/soloud_c.cpp"

' backend - alsa
Import "soloud/src/backend/alsa/soloud_alsa.cpp"

' backend - coreaudio
Import "soloud/src/backend/coreaudio/soloud_coreaudio.cpp"

' backend - jack
Import "soloud/src/backend/jack/soloud_jack.cpp"

' backend - nosound
Import "soloud/src/backend/nosound/soloud_nosound.cpp"

' backend - null
Import "soloud/src/backend/null/soloud_null.cpp"

' backend - openal
Import "soloud/src/backend/openal/soloud_openal_dll.c"
Import "soloud/src/backend/openal/soloud_openal.cpp"

' backend - portaudio
Import "soloud/src/backend/portaudio/soloud_portaudio_dll.c"
Import "soloud/src/backend/portaudio/soloud_portaudio.cpp"

' backend - wasapi
Import "soloud/src/backend/wasapi/soloud_wasapi.cpp"

' backend - winmm
Import "soloud/src/backend/winmm/soloud_winmm.cpp"

' audiosource - ay
Import "soloud/src/audiosource/ay/*.h"
Import "soloud/src/audiosource/ay/chipplayer.cpp"
Import "soloud/src/audiosource/ay/sndbuffer.cpp"
Import "soloud/src/audiosource/ay/sndchip.cpp"
Import "soloud/src/audiosource/ay/sndrender.cpp"
Import "soloud/src/audiosource/ay/soloud_ay.cpp"

' audiosource - monotone
Import "soloud/src/audiosource/monotone/soloud_monotone.cpp"

' audiosource - monotone
Import "soloud/src/audiosource/noise/soloud_noise.cpp"

' audiosource - sfxr
Import "soloud/src/audiosource/sfxr/soloud_sfxr.cpp"

' audiosource - speech
Import "soloud/src/audiosource/speech/*.h"
Import "soloud/src/audiosource/speech/darray.cpp"
Import "soloud/src/audiosource/speech/klatt.cpp"
Import "soloud/src/audiosource/speech/resonator.cpp"
Import "soloud/src/audiosource/speech/soloud_speech.cpp"
Import "soloud/src/audiosource/speech/tts.cpp"

' audiosource - tedsid
Import "soloud/src/audiosource/tedsid/sid.cpp"
Import "soloud/src/audiosource/tedsid/soloud_tedsid.cpp"
Import "soloud/src/audiosource/tedsid/ted.cpp"

' audiosource - vic
Import "soloud/src/audiosource/vic/soloud_vic.cpp"

' audiosource - vizsn
Import "soloud/src/audiosource/vizsn/soloud_vizsn.cpp"

' audiosource - wav
Import "soloud/src/audiosource/wav/*.h"
Import "soloud/src/audiosource/wav/dr_impl.cpp"
Import "soloud/src/audiosource/wav/soloud_wav.cpp"
Import "soloud/src/audiosource/wav/soloud_wavstream.cpp"
Import "soloud/src/audiosource/wav/stb_vorbis.c"


Import "glue.cpp"

Import "dataqueue/*.h"
Import "dataqueue/dataqueue.c"
