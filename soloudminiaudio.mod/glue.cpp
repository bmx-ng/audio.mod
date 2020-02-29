#include "soloud.h"
#include "miniaudio.h"

namespace SoLoud {

	result sdl2static_init(SoLoud::Soloud *aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2)
    {
        return NOT_IMPLEMENTED;
    }

    result miniaudio_init(SoLoud::Soloud* aSoloud, unsigned int aFlags = Soloud::CLIP_ROUNDOFF, unsigned int aSamplerate = 44100, unsigned int aBuffer = 2048, unsigned int aChannels = 2);

}

ma_context * _bmx_ma_context = 0;

extern "C" {

void bmx_soloud_miniaudio_context_deinit() {
	ma_context_uninit(_bmx_ma_context);
}

void bmx_soloud_miniaudio_context_init(ma_backend backend) {
	if (_bmx_ma_context) {
		bmx_soloud_miniaudio_context_deinit();
	} else {
		_bmx_ma_context = (ma_context*)malloc(sizeof(ma_context));
	}
	
	ma_backend backends[] = { backend };
	
	ma_context_init(backends, 1, NULL, _bmx_ma_context);
}


// linkage requires us to have a call to miniaudio_init
void miniaudio_stub() {
	SoLoud::miniaudio_init(0, 0, 0, 0);
}

}