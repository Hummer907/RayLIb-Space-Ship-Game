#include "Meteor.h"

void Meteor::move() {
	this->y += 5;
}
Meteor::Meteor(int x){
	this->x = x;
}