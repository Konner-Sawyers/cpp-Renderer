#include "World_Object.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

glm::vec2 pos;
float mass;


World_Object::World_Object(glm::vec2 posIn, float massIn) {
	pos = posIn;
	mass = massIn;
}

float World_Object::Get_Position_X() {
	return pos[0];
}