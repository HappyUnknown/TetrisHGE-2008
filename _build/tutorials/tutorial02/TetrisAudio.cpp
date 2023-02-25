#include "TetrisAudio.h"

void TetrisAudio::setup_boom(HGE*hge)
{
	boomEffect = hge->Effect_Load("menu.wav");
}
void TetrisAudio::play_place(HGE*hge)
{	
  const float volume = 100;
  const float pan = int((-1) / 2.56f);
  const float pitch = 0.15;
  hge->Effect_PlayEx(boomEffect, volume, pan, pitch);
}
void TetrisAudio::play_pop(HGE*hge)
{
  const float volume = 100;
  const float pan = int((-1) / 2.56f);
  const float pitch = 0.5;
  hge->Effect_PlayEx(boomEffect, volume, pan, pitch);
}

void TetrisAudio::setup_backmusic(std::string path, HGE*hge)
{
	backmusic = hge->Stream_Load(path.c_str());
}
void TetrisAudio::play_backmusic(HGE*hge)
{
	hge->Stream_Play(backmusic, true);
}
void TetrisAudio::stop_backmusic(HGE*hge)
{
	hge->Stream_Free(backmusic);
}
std::string TetrisAudio::guarantee_get_playlist_path()
{
	if(!DealFiles::file_exists(GameConstants::get_playlist_path())) DealFiles::recreate_file(GameConstants::get_playlist_path());
	return GameConstants::get_playlist_path();
}
std::vector<std::string> TetrisAudio::read_playlist()
{
	return DealFiles::read_lines(guarantee_get_playlist_path());
}
std::string TetrisAudio::playlist_get_random_path(HGE*hge)
{
	srand(time(NULL));
	std::vector<std::string> playlist = read_playlist();
	if(playlist.size() > 0)
	{
		int randomIndex = rand() % playlist.size();
		if(playlist[randomIndex] != "")
		{
			std::string path = playlist[randomIndex];
			if(DealFiles::file_exists(path))
			return path;
			else MessageBox(NULL, (path+"\nPath does not exist").c_str(), "Achtung", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		}
		else MessageBox(NULL, "Playlist's element is an empty line", "Achtung", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	}
	else MessageBox(NULL, "Playlist is empty", "Achtung", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	return "menu.wav";
}
void TetrisAudio::play_random_music(HGE*hge)
{
	std::string path = playlist_get_random_path(hge);
	setup_backmusic(path, hge);
	play_backmusic(hge);
}