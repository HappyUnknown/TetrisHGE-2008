#include "TetrominoTypes.h"
struct TetrominoBase
{
	int rotations;
	std::vector<GameSquare> squares;
	Position* center;
	TetrominoTypes figureType;
	TetrominoBase();

	void rotate_clockwise();
	void rotate_counterclockwise();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void place();
	//default value required to be false, because if there's no blocks left - we cannot judge accurately with "true" as default
	bool is_landed();
	bool intersects(TetrominoBase*tetromino);
	bool intersects_any(std::vector<TetrominoBase*>crowd);
	bool intersects_any(std::vector<GameSquare>crowd);
	bool is_above(TetrominoBase*tetromino);
	bool is_above(std::vector<GameSquare>squares);
	bool is_under(TetrominoBase*tetromino);
	bool is_under(std::vector<GameSquare>squares);
	bool is_leftside(TetrominoBase*tetromino);
	bool is_leftside(std::vector<GameSquare>squares);
	bool is_rightside(TetrominoBase*tetromino);
	bool is_rightside(std::vector<GameSquare>squares);
	std::vector<GameSquare> preview_down();
	std::vector<GameSquare> preview_up();
	std::vector<GameSquare> preview_left();
	std::vector<GameSquare> preview_right();
	std::vector<GameSquare> preview_clockwise(Position* center);
	std::vector<GameSquare> preview_counterclockwise(Position* center);
	int clear_row(int iVal);
	int count_row_squares(int iVal);
	void fall_above_row(int iVal);
	virtual void detect_center() = 0;
};
