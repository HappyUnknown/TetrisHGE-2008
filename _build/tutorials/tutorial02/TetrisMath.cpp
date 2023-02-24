#include "TetrisMath.h"

int TetrisMath::power(int base, int powerValue)
{
	int result = 1;
	for(int i=1;i<=powerValue;i++)
		result*=base;
	return result;
}
double TetrisMath::math_fall_period(Hardness hardness)
{
	int level = (int)hardness - 1;
	return GameConstants::get_max_fall_period()/power(2, level);
}
