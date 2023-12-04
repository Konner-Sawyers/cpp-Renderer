#ifndef Static_Rectangle_h
#define Static_Rectangle_h
#include "Static_Object.h"
//#include "Primitives.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <SDL.h>

class Static_Rectangle : public Static_Object
{

public:
	float SHAPE_WIDTH, SHAPE_HEIGHT;
	SDL_Point VERTEX_ARRAY[7] = {
									SDL_Point{-1, 1}, SDL_Point{1,-1},
									SDL_Point{-1,-1}, SDL_Point{-1, 1},
									SDL_Point{ 1, 1}, SDL_Point{ 1,-1},
									SDL_Point{-1, 1} };

	SDL_Point VERTEX_ARRAY_WORLD_POS[7] = {
											SDL_Point{-1, 1}, SDL_Point{1,-1},
											SDL_Point{-1,-1}, SDL_Point{-1, 1},
											SDL_Point{ 1, 1}, SDL_Point{ 1,-1},
											SDL_Point{-1, 1} };



	Static_Rectangle(float width = 10, float height = 10, glm::vec2 posIn = {0,0}, float massIn = 1) : Static_Object(posIn, massIn) {
		SHAPE_WIDTH = width; SHAPE_HEIGHT = height; 
		
		for (int i = 0; i < 7; i++) {
			VERTEX_ARRAY_WORLD_POS[i].x = pos[0] + (VERTEX_ARRAY_WORLD_POS[i].x * SHAPE_WIDTH * 1);
			VERTEX_ARRAY_WORLD_POS[i].y = pos[1] + (VERTEX_ARRAY_WORLD_POS[i].y * SHAPE_HEIGHT * -1);
		}

		for (int i = 0; i < 7; i++) {
			VERTEX_ARRAY[i].x = VERTEX_ARRAY_WORLD_POS[i].x;
			VERTEX_ARRAY[i].y = VERTEX_ARRAY_WORLD_POS[i].y;
		}
	};

};

#endif
