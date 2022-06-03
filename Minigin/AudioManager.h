#pragma once
#include "Singleton.h"
#include "../3rdParty/SDL2_mixer-2.0.4/include/SDL_mixer.h"

namespace dae
{
	class AudioManager final : public Singleton<AudioManager>
	{
	};
}
