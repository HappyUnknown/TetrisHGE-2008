#include "TetrisMath.h"
struct Position
{
	int i;
	int j;
	Position::Position();
	Position::Position(int i, int j);
	bool Position::intersects(Position pos);
	Position Position::above();
	Position Position::under();
	Position Position::leftside();
	Position Position::rightside();
	bool Position::is_above(Position pos);
	bool Position::is_under(Position pos);
	bool Position::is_leftside(Position pos);
	bool Position::is_rightside(Position pos);
	//bool intersects_any(std::vector<Position>crowd)
	//{
	//	for(int i=0;i<crowd.size();i++)
	//		if(this->intersects(crowd[i]))
	//			return true;
	//	return false;
	//}
};
