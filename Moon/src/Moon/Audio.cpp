#include "Audio.hpp"

#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

namespace Moon
{
	void Audio::Play(const String& file)
	{
		String command = "play \"./src/sound/" + file + ".mp3\"";
		mciSendString(WString(command.begin(), command.end()).c_str(), NULL, 0, NULL);
	}
}