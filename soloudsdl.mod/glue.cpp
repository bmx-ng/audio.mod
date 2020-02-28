#include "soloud.h"

namespace SoLoud {

	result sdl2static_init(SoLoud::Soloud *aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2);

    result miniaudio_init(SoLoud::Soloud* aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2)
    {
        return NOT_IMPLEMENTED;
    }

}

extern "C" {

// linkage requires us to have a call to sdl2static_init
void sdl_stub() {
	SoLoud::sdl2static_init(0, 0, 0, 0);
}

}