#include "MenuOptions.h"

struct TetrisAudio
{
	#pragma region SOUND
	HEFFECT boomEffect;
	void TetrisAudio::setup_boom(HGE*);
	void TetrisAudio::play_place(HGE*);
	void TetrisAudio::play_pop(HGE*);
	#pragma endregion
	#pragma region STREAMS
	HSTREAM backmusic;
	void setup_backmusic(std::string, HGE*);
	void play_backmusic(HGE*);
	void stop_backmusic(HGE*);
	std::string guarantee_get_playlist_path();
	std::vector<std::string> read_playlist();
	std::string playlist_get_random_path(HGE*);
	void play_random_music(HGE*);
	#pragma endregion

};