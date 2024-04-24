#include "CharacterClass.h"
CharacterClass::CharacterClass(int x ,int y ,Sprite stays,Sprite runs) {
	this->x = x;
	this->y = y;
	this->stays = stays;
	this->runs = runs;
}

void CharacterClass::moveLeft(int steps) {
	runs.Draw(this->x,this->y);
	this->x -= 2;
}

void CharacterClass::present() {
	stays.Draw(this->x, this->y);
}