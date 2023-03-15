#include "TetrominoBase.h"

	TetrominoBase::TetrominoBase()
	{
		rotations = 0;
		figureType = TetrominoTypes::tetrominoUFO;
		center = NULL;
	}

	void TetrominoBase::rotate_clockwise()
	{
		if (center != NULL)
		{
			for (int i = 0; i < batch.squares.size(); i++)
				batch.squares[i].rotate_clockwise(*center);
			rotations++;
			if (rotations >= 4) rotations = 0;
		}
	}
	void TetrominoBase::rotate_counterclockwise()
	{
		if (center != NULL)
		{
			for (int i = 0; i < batch.squares.size(); i++)
				batch.squares[i].rotate_counterclockwise(*center);
			rotations++;
			if (rotations >= 4) rotations = 0;
		}
	}
	void TetrominoBase::move_up()
	{
		for(int i=0;i<batch.squares.size();i++)
			batch.squares[i].move_up();
	}
	void TetrominoBase::move_down(int step)
	{
		for(int i=0;i<batch.squares.size();i++)
			batch.squares[i].move_down(step);
	}
	void TetrominoBase::move_left()
	{
		for(int i=0;i<batch.squares.size();i++)
			batch.squares[i].move_left();
	}
	void TetrominoBase::move_right()
	{
		for(int i=0;i<batch.squares.size();i++)
			batch.squares[i].move_right();
	}
	void TetrominoBase::place()
	{
		for(int i=0;i<batch.squares.size();i++)
			batch.squares[i].land();
	}
	//default value required to be false, because if there's no blocks left - we cannot judge accurately with "true" as default
	bool TetrominoBase::is_landed()
	{
		for(int i=0;i<batch.squares.size();i++)
			if(!batch.squares[i].landed)
				return false;
		return true;
	}
	bool TetrominoBase::intersects(TetrominoBase*tetromino)
	{
		for(int i=0;i<batch.squares.size();i++)
			if(batch.squares[i].intersects_any(tetromino->batch.squares))
				return true;
		return false;
	}
	bool TetrominoBase::intersects_any(std::vector<TetrominoBase*>crowd)
	{
		for(int i=0;i<crowd.size();i++)
			if(intersects(crowd[i]) && crowd[i]!=this)
				return true;
		return false;
	}
	bool TetrominoBase::intersects_any(std::vector<GameSquare>crowd)
	{
		for(int i=0;i<crowd.size();i++)
			if(crowd[i].intersects_any(this->batch.squares))
				return true;
		return false;
	}
	bool TetrominoBase::is_above(TetrominoBase*tetromino)
	{
		return is_above(tetromino->batch.squares);
	}
	bool TetrominoBase::is_above(std::vector<GameSquare>squares)
	{
		for(int i=0;i<this->batch.squares.size();i++)
			for(int j=0;j<batch.squares.size();j++)
				if(this->batch.squares[i].is_above(squares[j]))
					return true;
		return false;
	}
	bool TetrominoBase::is_under(TetrominoBase*tetromino)
	{
		return is_under(tetromino->batch.squares);
	}
	bool TetrominoBase::is_under(std::vector<GameSquare>squares)
	{
		for(int i=0;i<this->batch.squares.size();i++)
			for(int j=0;j<batch.squares.size();j++)
				if(this->batch.squares[i].is_under(squares[j]))
					return true;
		return false;
	}
	bool TetrominoBase::is_leftside(TetrominoBase*tetromino)
	{
		return is_leftside(tetromino->batch.squares);
	}
	bool TetrominoBase::is_leftside(std::vector<GameSquare>squares)
	{
		for(int i=0;i<this->batch.squares.size();i++)
			for(int j=0;j<batch.squares.size();j++)
				if(this->batch.squares[i].is_leftside(squares[j]))
					return true;
		return false;
	}
	bool TetrominoBase::is_rightside(TetrominoBase*tetromino)
	{
		return is_rightside(tetromino->batch.squares);
	}
	bool TetrominoBase::is_rightside(std::vector<GameSquare>squares)
	{
		for(int i=0;i<this->batch.squares.size();i++)
			for(int j=0;j<batch.squares.size();j++)
				if(this->batch.squares[i].is_rightside(squares[j]))
					return true;
		return false;
	}
	std::vector<GameSquare> TetrominoBase::preview_down(int step)
	{
		std::vector<GameSquare> preview;
		for(int i=0;i<batch.squares.size();i++)
		{
			GameSquare temp = batch.squares[i];
			temp.move_down(step);
			preview.push_back(temp);
		}
		return preview;
	}
	std::vector<GameSquare> TetrominoBase::preview_up()
	{
		std::vector<GameSquare> preview;
		for(int i=0;i<batch.squares.size();i++)
		{
			GameSquare temp = batch.squares[i];
			temp.move_up();
			preview.push_back(temp);
		}
		return preview;
	}
	std::vector<GameSquare> TetrominoBase::preview_left()
	{
		std::vector<GameSquare> preview;
		for(int i=0;i<batch.squares.size();i++)
		{
			GameSquare temp = batch.squares[i];
			temp.move_left();
			preview.push_back(temp);
		}
		return preview;
	}
	std::vector<GameSquare> TetrominoBase::preview_right()
	{
		std::vector<GameSquare> preview;
		for(int i=0;i<batch.squares.size();i++)
		{
			GameSquare temp = batch.squares[i];
			temp.move_right();
			preview.push_back(temp);
		}
		return preview;
	}
	std::vector<GameSquare> TetrominoBase::preview_clockwise(Position* center)
	{
		std::vector<GameSquare> preview;
		if(center!=NULL)
			for(int i=0;i<batch.squares.size();i++)
			{
				GameSquare temp = batch.squares[i];
				temp.rotate_clockwise(*center);
				preview.push_back(temp);
			}
		return preview;
	}
	std::vector<GameSquare> TetrominoBase::preview_counterclockwise(Position* center)
	{
		std::vector<GameSquare> preview;
		if(center!=NULL)
			for(int i=0;i<batch.squares.size();i++)
			{
				GameSquare temp = batch.squares[i];
				temp.rotate_counterclockwise(*center);
				preview.push_back(temp);
			}
		return preview;
	}
	int TetrominoBase::clear_row(int iVal)
	{
		int squareEntries = 0;
		std::vector<GameSquare>keptSquares;
		for(int i=0;i<batch.squares.size();i++)
			if(batch.squares[i].pos.i != iVal)
			{
				keptSquares.push_back(batch.squares[i]);
				squareEntries++;
			}
			batch.squares = keptSquares;
			return squareEntries;
	}
	int TetrominoBase::count_row_squares(int iVal)
	{
		int squareEntries = 0;
		for(int i=0;i<batch.squares.size();i++)
			if(batch.squares[i].pos.i==iVal)
				squareEntries++;
		return squareEntries;
	}
	void TetrominoBase::fall_above_row(int iVal)
	{
		for(int i=0;i<batch.squares.size();i++)
			if(batch.squares[i].pos.i < iVal)
				batch.squares[i].pos.i++;
	}
	bool TetrominoBase::takes_position(Position pos)
	{
		for(int i=0;i<batch.squares.size();i++)
			if(batch.squares[i].pos.i == pos.i && batch.squares[i].pos.j == pos.j)
				return true;
		return false;
	}
	//j parameter overload is not being used in code, but can be used when we need to define currents's maximum on column
	int TetrominoBase::max_i(int j)
	{
		int maxI = INT_MIN;
		for(int i=0;i<batch.squares.size();i++)
			if(maxI < batch.squares[i].pos.i)
				if(j==-1 || j==batch.squares[i].pos.j)
					maxI = batch.squares[i].pos.i;
		return maxI;
	}
