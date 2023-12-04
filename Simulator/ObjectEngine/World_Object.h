#ifndef World_Object_h
#define World_Object_h
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class World_Object
{
	

public:
	glm::vec2 pos;
	float mass;

	World_Object(glm::vec2 posIn, float massIn);
	float Get_Position_X();
};

#endif