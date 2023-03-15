#include "TetrominoTypes.h"
struct SquareBatch
{
	std::vector<GameSquare> squares;
};
struct TetrominoBase
{
	SquareBatch batch;
	int rotations;
	Position* center;
	TetrominoTypes figureType;
	TetrominoBase();

	void rotate_clockwise();
	void rotate_counterclockwise();
	void move_up();
	void move_down(int);
	void move_left();
	void move_right();
	void place();
	//default value required to be false, because if there's no blocks left - we cannot judge accurately with "true" as default
	bool is_landed();
	bool intersects(TetrominoBase*tetromino);
	bool intersects_any(std::vector<TetrominoBase*>);
	bool intersects_any(std::vector<GameSquare>);
	bool is_above(TetrominoBase*);
	bool is_above(std::vector<GameSquare>);
	bool is_under(TetrominoBase*tetromino);
	bool is_under(std::vector<GameSquare>);
	bool is_leftside(TetrominoBase*);
	bool is_leftside(std::vector<GameSquare>);
	bool is_rightside(TetrominoBase*);
	bool is_rightside(std::vector<GameSquare>);
	std::vector<GameSquare> preview_down(int);
	std::vector<GameSquare> preview_up();
	std::vector<GameSquare> preview_left();
	std::vector<GameSquare> preview_right();
	std::vector<GameSquare> preview_clockwise(Position*);
	std::vector<GameSquare> preview_counterclockwise(Position*);
	int clear_row(int);
	int count_row_squares(int);
	void fall_above_row(int);
	bool TetrominoBase::takes_position(Position);
	//j parameter overload is not being used in code, but can be used when we need to define currents's maximum on column
	int TetrominoBase::max_i(int = -1);
	virtual void detect_center() = 0;
};
