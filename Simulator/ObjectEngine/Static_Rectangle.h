#ifndef Static_Rectangle_h
#define Static_Rectangle_h
#include "Static_Object.h"
#include "Primitives.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <SDL.h>

class Static_Rectangle : public Static_Object
{

public:
	float SHAPE_WIDTH, SHAPE_HEIGHT;



	SDL_Vertex VERTEX_ARRAY[4];


	int INDICIES_ARRAY[6] = { 0,2,3,0,1,2 };

	SDL_Vertex VERTEX_ARRAY_WORLD_POS[4] = {
											SDL_Vertex{{-1, 1}, RED,  {-1, 1}} ,
											SDL_Vertex{{ 1, 1}, GREEN, {-1, 1}} ,
											SDL_Vertex{{ 1,-1}, BLUE, {-1, 1}} ,
											SDL_Vertex{{-1,-1}, RED, {-1, 1}} };


	Static_Rectangle(float width = 10, float height = 10, glm::vec2 posIn = {0,0}, float massIn = 1) : Static_Object(posIn, massIn) {
		SHAPE_WIDTH = width; SHAPE_HEIGHT = height; 
		


		for (int i = 0; i < sizeof(VERTEX_ARRAY)/sizeof(VERTEX_ARRAY[0]); i++) {
			VERTEX_ARRAY_WORLD_POS[i].position.x = pos[0] + (VERTEX_ARRAY_WORLD_POS[i].position.x * SHAPE_WIDTH * 1);
			VERTEX_ARRAY_WORLD_POS[i].position.y = pos[1] + (VERTEX_ARRAY_WORLD_POS[i].position.y * SHAPE_HEIGHT * -1);
		}

		for (int i = 0; i < sizeof(INDICIES_ARRAY) / sizeof(INDICIES_ARRAY[0]); i++) {

		}
		

		for (int i = 0; i < sizeof(RECT_VERTEX_ARRAY) / sizeof(RECT_VERTEX_ARRAY[0]); i++) {
			VERTEX_ARRAY[i] = RECT_VERTEX_ARRAY[i];
		}


		for (int i = 0; i < 4; i++) {
			VERTEX_ARRAY[i].position.x = VERTEX_ARRAY_WORLD_POS[i].position.x;
			VERTEX_ARRAY[i].position.y = VERTEX_ARRAY_WORLD_POS[i].position.y;
		}
	};

};

#endif
