#include "GameConstants.h"
float GameConstants::get_texture_start_x()
{
	return 0.0f;
}
float GameConstants::get_texture_start_y()
{
	return 0.0f;
}
float GameConstants::get_texture_fraction()
{
	return 0.5f; //Otherwise, we receive quad clearence
}
double GameConstants::get_max_fall_period()
	{
		return 2;
	}
std::string GameConstants::get_texture_path()
	{
		return "white_cube.png";
	}
std::string GameConstants::get_background_path()
	{
		return "bg.png";
	}
std::string GameConstants::get_playlist_path()
	{
		return "playlist.txt";
	}
int GameConstants::squares_on_width()
	{
		return FRAMEX / VISUAL_SIZE;
	}
int GameConstants::squares_on_height()
	{
		return FRAMEY / VISUAL_SIZE;
	}