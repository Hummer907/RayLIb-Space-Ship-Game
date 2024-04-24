#pragma once
#include "Sprite.h"
enum Direction
{
	LEFT, RIGHT, UP, DOWN
};
class CharacterClass
{
public:
	int x;
	int y;
	Sprite stays;
	Sprite runs;

	CharacterClass(int x ,int y ,Sprite stays,Sprite runs);
	void moveLeft(int steps);
	void present();
};

