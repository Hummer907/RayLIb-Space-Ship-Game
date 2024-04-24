#include "missile.h"

missile::missile(int x,int y ) {
	this->x = x;
	this->y = y;
}
void missile::move() {
	this->y -= 5;
}