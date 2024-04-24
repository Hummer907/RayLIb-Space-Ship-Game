#include "Asteroid.h"
Asteroid::Asteroid(int x) {
	this->x = x;
}
void Asteroid::move() {
	this->y += 5;
}