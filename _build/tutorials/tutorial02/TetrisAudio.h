#include "MenuOptions.h"

struct TetrisAudio
{
	#pragma region SOUND
	HEFFECT boomEffect;
	void TetrisAudio::setup_boom(HGE*hge);
	void TetrisAudio::play_place(HGE*hge);
	void TetrisAudio::play_pop(HGE*hge);
	#pragma endregion
	#pragma region STREAMS
	HSTREAM backmusic;
	void setup_backmusic(std::string path, HGE*hge);
	void play_backmusic(HGE*hge);
	void stop_backmusic(HGE*hge);
	std::string guarantee_get_playlist_path();
	std::vector<std::string> read_playlist();
	std::string playlist_get_random_path(HGE*hge);
	void play_random_music(HGE*hge);
	#pragma endregion

};