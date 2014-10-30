#pragma once

struct PlayerControls
{
	int up;
	int down;
	int clockwise;
	int anticlockwise;
	int throwBall;
};

struct PlayerInitialisers
{
	float initialRotation;
	float initialX;
	float initialY;
	string spritePath;
	bool invertX;
	float ballSpawnRotationOffset;
	float ballSpawnPositionOffset;
	int zoneTextX;
	int zoneTextY;
};