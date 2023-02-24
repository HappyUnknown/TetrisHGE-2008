#include "StringExtensions.h"
static struct GameConstants
{
	static const int QUAD_RADIUS = 25, VISUAL_SIZE = QUAD_RADIUS * 2;
	static const int FRAMEX = 800, FRAMEY = 600;
	static const int INIT_I = 0, RESERVE_INIT_J = 0;
	static const int DEFAULT_FIELD_WIDTH = 5, DEFAULT_FIELD_HEIGHT = 10;
	static const int MIN_FIELD_WIDTH = RESERVE_INIT_J + 4, MIN_FIELD_HEIGHT = 5;
	static const int MAX_FIELD_WIDTH = 20, MAX_FIELD_HEIGHT = 20;

	static float GameConstants::get_texture_start_x();
	static float GameConstants::get_texture_start_y();
	static float GameConstants::get_texture_fraction();
	static double GameConstants::get_max_fall_period();
	static std::string GameConstants::get_texture_path();
	static std::string GameConstants::get_background_path();
	static std::string GameConstants::get_playlist_path();
	/// <summary>
	/// 2023.02.08/18:27 - Counts, how many of regular squares window's row can contain
	/// </summary>
	/// <returns></returns>
	static int GameConstants::squares_on_width();
	/// <summary>
	/// 2023.02.08/18:27 - Counts, how many of regular squares window's columns can contain
	/// </summary>
	/// <returns></returns>
	static int GameConstants::squares_on_height();
};
