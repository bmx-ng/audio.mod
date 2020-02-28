#include "soloud.h"

namespace SoLoud {

	result sdl2static_init(SoLoud::Soloud *aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2)
    {
        return NOT_IMPLEMENTED;
    }

    result miniaudio_init(SoLoud::Soloud* aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2);

}

extern "C" {

// linkage requires us to have a call to miniaudio_init
void miniaudio_stub() {
	SoLoud::miniaudio_init(0, 0, 0, 0);
}

}