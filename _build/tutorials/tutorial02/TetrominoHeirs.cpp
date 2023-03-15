#include "TetrominoHeirs.h"

	void TetrominoI::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::I;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,0));
		initialPosition.push_back(Position(0,1));
		initialPosition.push_back(Position(0,2));
		initialPosition.push_back(Position(0,3));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoI::copy()
	{
		TetrominoI temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoI::TetrominoI()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoI::TetrominoI(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoI::detect_center()
	{
		center = &batch.squares[1].pos;
	}
	void TetrominoJ::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::J;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,0));
		initialPosition.push_back(Position(1,0));
		initialPosition.push_back(Position(1,1));
		initialPosition.push_back(Position(1,2));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoJ::copy()
	{
		TetrominoJ temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoJ::TetrominoJ()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoJ::TetrominoJ(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoJ::detect_center()
	{
		center = &batch.squares[2].pos;
	}
	void TetrominoL::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::L;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,2));
		initialPosition.push_back(Position(1,0));
		initialPosition.push_back(Position(1,1));
		initialPosition.push_back(Position(1,2));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoL::TetrominoL()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoL::TetrominoL(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoL::detect_center()
	{
		center = &batch.squares[2].pos;
	}
	void TetrominoO::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::O;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,0));
		initialPosition.push_back(Position(0,1));
		initialPosition.push_back(Position(1,0));
		initialPosition.push_back(Position(1,1));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoO::copy()
	{
		TetrominoO temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoO::TetrominoO()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoO::TetrominoO(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoO::detect_center()
	{
		center = NULL;
	}
	void TetrominoS::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::S;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,1));
		initialPosition.push_back(Position(0,2));
		initialPosition.push_back(Position(1,0));
		initialPosition.push_back(Position(1,1));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoS::copy()
	{
		TetrominoS temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoS::TetrominoS()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoS::TetrominoS(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoS::detect_center()
	{
		center = &batch.squares[0].pos;
	}
	void TetrominoT::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::T;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,1));
		initialPosition.push_back(Position(1,0));
		initialPosition.push_back(Position(1,1));
		initialPosition.push_back(Position(1,2));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoT::copy()
	{
		TetrominoT temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoT::TetrominoT()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoT::TetrominoT(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoT::detect_center()
	{
		center = &batch.squares[2].pos;
	}
	void TetrominoZ::init_figure(int initI, int initJ)
	{
		figureType = TetrominoTypes::Z;

		std::vector<Position>initialPosition;
		initialPosition.push_back(Position(0,0));
		initialPosition.push_back(Position(0,1));
		initialPosition.push_back(Position(1,1));
		initialPosition.push_back(Position(1,2));

		for(int i = 0; i < initialPosition.size(); i++)
		{
			GameSquare square = GameSquare();
			square.pos.i = initialPosition[i].i+initI;
			square.pos.j = initialPosition[i].j+initJ;
			square.landed = false;
			batch.squares.push_back(square);
		}
		detect_center();
	}
	TetrominoBase* TetrominoZ::copy()
	{
		TetrominoZ temp;
		temp.figureType = figureType;
		temp.rotations = rotations;
		temp.batch.squares = batch.squares;
		temp.center = center;
		return &temp;
	}
	TetrominoZ::TetrominoZ()
	{
		init_figure(GameConstants::INIT_I, GameConstants::RESERVE_INIT_J);
	}
	TetrominoZ::TetrominoZ(int initI, int initJ)
	{
		init_figure(initI, initJ);
	}
	void TetrominoZ::detect_center()
	{
		center = &batch.squares[1].pos;
	}
