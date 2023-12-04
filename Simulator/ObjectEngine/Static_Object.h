#ifndef Static_Object_h
#define Static_Object_h
#include "World_Object.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class Static_Object: public World_Object
{
public:
	Static_Object(glm::vec2 posIn, float massIn) : World_Object(posIn, massIn) {};

	float Get_Velocity_X();
};

#endif