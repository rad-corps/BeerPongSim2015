#pragma once

#define DEG_TO_RAD 0.01745329252

//generate a random number from from to to inclusive
int RandomNumber(int from, int to);

//percentage expressed between 0.0f and 1.0f;
float RandomPercentage();
float RandomPercentageAbove(float above_);

float Lerp(float min, float max, float norm);
