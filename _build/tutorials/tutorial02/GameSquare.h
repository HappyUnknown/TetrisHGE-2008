#include "Position.h"
struct GameSquare
{
	hgeQuad graphics;
	Position pos;
	bool landed;
	GameSquare();
	int get_clockwise_i(Position center);//Y
	int get_clockwise_j(Position center);//X
	int get_counterclockwise_i(Position center);//Y
	int get_counterclockwise_j(Position center);//X
	void rotate_clockwise(Position center);
	void rotate_counterclockwise(Position center);
	void move_up();
	void move_down(int step);
	void move_left();
	void move_right();
	void land();
	bool intersects(GameSquare square);
	bool intersects_any(std::vector<GameSquare>crowd);
	bool is_above(GameSquare square);
	bool is_under(GameSquare square);
	bool is_leftside(GameSquare square);
	bool is_rightside(GameSquare square);
};
