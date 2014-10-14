#include <math.h>
#include <cstdlib>
#include "MathHelpers.h"
#include <time.h>

//generate a random number from from to to inclusive
int RandomNumber(int from, int to)
{
	int diff = to - from;
	int result = rand() % diff + from;
	return result;
}

float RandomPercentage()
{
	int res = RandomNumber(0, 100);
	float fres = (float)res / 100.f;
	return fres;
}

float RandomPercentageAbove(float above_)
{
	float temp = RandomPercentage();
	if ( temp < above_ )
		return above_;
	return temp;
}

float Lerp(float min, float max, float percent) //percent between 0 and 1
{
	return (min + percent*(max - min));
}