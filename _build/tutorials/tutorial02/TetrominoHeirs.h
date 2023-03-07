#include "TetrominoBase.h"

struct TetrominoI : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoI();
	TetrominoI(int, int);
	void detect_center();
};
struct TetrominoJ : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoJ();
	TetrominoJ(int, int);
	void detect_center();
};
struct TetrominoL : TetrominoBase
{
	void init_figure(int, int);
	TetrominoL();
	TetrominoL(int, int);
	void detect_center();
};
struct TetrominoO : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoO();
	TetrominoO(int, int);
	void detect_center();
};
struct TetrominoS : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoS();
	TetrominoS(int, int);
	void detect_center();
};
struct TetrominoT : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoT();
	TetrominoT(int, int);
	void detect_center();
};
struct TetrominoZ : TetrominoBase
{
	void init_figure(int, int);
	TetrominoBase* copy();
	TetrominoZ();
	TetrominoZ(int, int);
	void detect_center();
};
