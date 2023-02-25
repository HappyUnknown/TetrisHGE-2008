#include "Position.h"
Position::Position()
	{
		i = 0;
		j = 0;
	}
	Position::Position(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
	bool Position::intersects(Position pos)
	{
		if(this->i == pos.i && this->j == pos.j)
			return true;
		return false;
	}
	Position Position::above()
	{
		return Position(i-1,j);
	}
	Position Position::under()
	{
		return Position(i+1,j);
	}
	Position Position::leftside()
	{
		return Position(i,j-1);
	}
	Position Position::rightside()
	{
		return Position(i,j+1);
	}
	bool Position::is_above(Position pos)
	{
		if(this->i == pos.above().i && this->j == pos.above().j)
			return true;
		return false;
	}
	bool Position::is_under(Position pos)
	{
		if(this->i == pos.under().i && this->j == pos.under().j)
			return true;
		return false;
	}
	bool Position::is_leftside(Position pos)
	{
		if(this->i == pos.leftside().i && this->j == pos.leftside().j)
			return true;
		return false;
	}
	bool Position::is_rightside(Position pos)
	{
		if(this->i == pos.rightside().i && this->j == pos.rightside().j)
			return true;
		return false;
	}
	//bool intersects_any(std::vector<Position>crowd)
	//{
	//	for(int i=0;i<crowd.size();i++)
	//		if(this->intersects(crowd[i]))
	//			return true;
	//	return false;
	//}

	Position Position::operator-(Position right)
	{
		return Position(this->i-right.i, this->j-right.j);
	}