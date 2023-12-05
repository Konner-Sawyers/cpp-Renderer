#ifndef Rectangle_Object_h
#define Rectangle_Object_h
#include "World_Object.h"
#include "Primitives.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <SDL.h>

class Rectangle_Object : public World_Object
{
public:

	SDL_Vertex VERTEX_ARRAY[4];
	SDL_Vertex VERTEX_ARRAY_WORLD[4];
	int INDICIES_ARRAY[6];

	Rectangle_Object(glm::vec2 scaleIn = { 1,1 }, glm::vec2 posIn = { 0,0 }, float massIn = 1) : World_Object(scaleIn, posIn, massIn) {

		

		for (int i = 0; i < 4; i++) {
			VERTEX_ARRAY[i] = RECT_VERTEX_ARRAY[i];
			VERTEX_ARRAY_WORLD[i] = RECT_VERTEX_ARRAY[i];
		}
		for (int i = 0; i < 6; i++) {
			INDICIES_ARRAY[i] = RECT_INDICIES_ARRAY[i];

		}


		for (int i = 0; i < sizeof(VERTEX_ARRAY) / sizeof(VERTEX_ARRAY[0]); i++) {
			VERTEX_ARRAY_WORLD[i].position.x = pos[0] + (VERTEX_ARRAY_WORLD[i].position.x * scale[0] * 1);
			VERTEX_ARRAY_WORLD[i].position.y = pos[1] + (VERTEX_ARRAY_WORLD[i].position.y * scale[1] * -1);
		}

		for (int i = 0; i < sizeof(INDICIES_ARRAY) / sizeof(INDICIES_ARRAY[0]); i++) {

		}


		for (int i = 0; i < sizeof(RECT_VERTEX_ARRAY) / sizeof(RECT_VERTEX_ARRAY[0]); i++) {
			VERTEX_ARRAY[i] = RECT_VERTEX_ARRAY[i];
		}


		for (int i = 0; i < 4; i++) {
			VERTEX_ARRAY[i].position.x = VERTEX_ARRAY_WORLD[i].position.x;
			VERTEX_ARRAY[i].position.y = VERTEX_ARRAY_WORLD[i].position.y;
		}
	};

};

#endif