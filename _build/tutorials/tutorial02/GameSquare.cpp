#include "GameSquare.h"
	GameSquare::GameSquare()
	{
		landed = false;
	}
	int GameSquare::get_clockwise_i(Position center)//Y
	{
		const int SIN90 = 1, COS90 = 0;
		return (pos.j - center.j) * SIN90 + (pos.i - center.i) * COS90 + center.i;
	}
	int GameSquare::get_clockwise_j(Position center)//X
	{
		const int SIN90 = 1, COS90 = 0;
		return (pos.j - center.j) * COS90 + (center.i - pos.i) * SIN90 + center.j;
	}
	int GameSquare::get_counterclockwise_i(Position center)//Y
	{
		const int SIN90 = 1, COS90 = 0;
		return (center.j - pos.j) * SIN90 + (center.i - pos.i) * COS90 + center.i;
	}
	int GameSquare::get_counterclockwise_j(Position center)//X
	{
		const int SIN90 = 1, COS90 = 0;
		return (center.j - pos.j) * COS90 + (pos.i - center.i) * SIN90 + center.j;
	}
	void GameSquare::rotate_clockwise(Position center)
	{
		const int SIN90 = 1, COS90 = 0;
		pos = Position(get_clockwise_i(center), get_clockwise_j(center));
	}
	void GameSquare::rotate_counterclockwise(Position center)
	{
		const int SIN90 = 1, COS90 = 0;
		pos = Position(get_counterclockwise_i(center), get_counterclockwise_j(center));
	}
	void GameSquare::move_up()
	{
		pos.i--;
	}
	void GameSquare::move_down()
	{
		pos.i++;
	}
	void GameSquare::move_left()
	{
		pos.j--;
	}
	void GameSquare::move_right()
	{
		pos.j++;
	}
	void GameSquare::land()
	{
		landed = true;
	}
	bool GameSquare::intersects(GameSquare square)
	{
		if(this->pos.intersects(square.pos))
			return true;
		return false;
	}
	bool GameSquare::intersects_any(std::vector<GameSquare>crowd)
	{
		for(int i=0;i<crowd.size();i++)
			if(intersects(crowd[i]))
				return true;
		return false;
	}
	bool GameSquare::is_above(GameSquare square)
	{
		return this->pos.is_above(square.pos);
	}
	bool GameSquare::is_under(GameSquare square)
	{
		return this->pos.is_under(square.pos);
	}
	bool GameSquare::is_leftside(GameSquare square)
	{
		return this->pos.is_leftside(square.pos);
	}
	bool GameSquare::is_rightside(GameSquare square)
	{
		return this->pos.is_rightside(square.pos);
	}