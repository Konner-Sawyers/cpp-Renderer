#ifndef World_Object_h
#define World_Object_h
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class World_Object
{
	

public:
	glm::vec2 pos, scale;
	float mass;


	World_Object(glm::vec2 scaleIn = { 1,1 }, glm::vec2 posIn = { 0,0 }, float massIn = 1) {
		pos = posIn;
		mass = massIn;
		scale = scaleIn;
	};


};

#endif