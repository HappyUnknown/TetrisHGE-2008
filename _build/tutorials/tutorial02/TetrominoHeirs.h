#include "TetrominoBase.h"

struct TetrominoI : TetrominoBase
{
	void TetrominoI::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoI::copy();
	TetrominoI::TetrominoI();
	TetrominoI::TetrominoI(int initI, int initJ);
	void TetrominoI::detect_center();
};
struct TetrominoJ : TetrominoBase
{
	void TetrominoJ::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoJ::copy();
	TetrominoJ::TetrominoJ();
	TetrominoJ::TetrominoJ(int initI, int initJ);
	void TetrominoJ::detect_center();
};
struct TetrominoL : TetrominoBase
{
	void TetrominoL::init_figure(int initI, int initJ);
	TetrominoL::TetrominoL();
	TetrominoL::TetrominoL(int initI, int initJ);
	void TetrominoL::detect_center();
};
struct TetrominoO : TetrominoBase
{
	void TetrominoO::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoO::copy();
	TetrominoO::TetrominoO();
	TetrominoO::TetrominoO(int initI, int initJ);
	void TetrominoO::detect_center();
};
struct TetrominoS : TetrominoBase
{
	void TetrominoS::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoS::copy();
	TetrominoS::TetrominoS();
	TetrominoS::TetrominoS(int initI, int initJ);
	void TetrominoS::detect_center();
};
struct TetrominoT : TetrominoBase
{
	void TetrominoT::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoT::copy();
	TetrominoT::TetrominoT();
	TetrominoT::TetrominoT(int initI, int initJ);
	void TetrominoT::detect_center();
};
struct TetrominoZ : TetrominoBase
{
	void TetrominoZ::init_figure(int initI, int initJ);
	TetrominoBase* TetrominoZ::copy();
	TetrominoZ::TetrominoZ();
	TetrominoZ::TetrominoZ(int initI, int initJ);
	void TetrominoZ::detect_center();
};
