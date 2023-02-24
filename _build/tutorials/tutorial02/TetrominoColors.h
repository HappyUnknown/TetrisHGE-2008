#include "TetrisSettings.h"
static struct TetrominoColors
{
	static const int COLOR_QUANTITY = 7;
	enum Colors
	{
	  White = 1,
	  Red,
	  Orange,
	  Yellow,
	  Green,
	  Blue,
	  Purple,
	  Black
	};
	static hgeU32 TetrominoColors::get_color_by_id(Colors id)
	{
	  switch (id)
	  {
	  case Colors::Blue:
		return 0xFF0000FF;
	  case Colors::Green:
		return 0xFF00FF00;
	  case Colors::Red:
		return 0xFFFF0000;
	  case Colors::Purple:
		return 0xFFFF00FF;
	  case Colors::Yellow:
		return 0xFFAAAA00;
	  case Colors::Orange:
		return 0xFFFFAA00;
		//case Colors::Black:
		//  return 0xFF000000;
	  case Colors::White:
	  default:
		return 0xFFFFFFFF;
	  }
	}
	static hgeU32 get_random_color()
	{
	  srand(time(NULL));
	  int randomColorID = rand() % COLOR_QUANTITY + 1;
	  return get_color_by_id((Colors)randomColorID);
	}
	static Colors detect_color(hgeU32 colorHex)
	{
	  switch (colorHex)
	  {
	  case 0xFF0000FF:
		return Colors::Blue;
	  case 0xFF00FF00:
		return Colors::Green;
	  case 0xFFFF0000:
		return Colors::Red;
	  case 0xFFFF00FF:
		return Colors::Purple;
	  case 0xFFAAAA00:
		return Colors::Yellow;
	  case 0xFFFFAA00:
		return Colors::Orange;
		//case 0xFF000000:
		//  return Colors::Black;
	  case 0xFFFFFFFF:
	  default:
		return Colors::White;
	  }
	}
};
