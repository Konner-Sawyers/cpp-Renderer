#include "Custom_Object.h"
#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include "Object_From_File.h"

void Custom_Object::ZoomUpdate(float ZOOM, int WIDTH, int HEIGHT, float CAM_X, float CAM_Y)
{
	for (int i = 0; i < INIT_VERTEX_ARRAY.size(); i++) {
		VERTEX_ARRAY[i] = INIT_VERTEX_ARRAY[i];
		VERTEX_ARRAY_WORLD[i] = INIT_VERTEX_ARRAY[i];
	}

	for (int i = 0; i < VERTEX_ARRAY.size(); i++) {
		VERTEX_ARRAY[i].position.x = ZOOM * ((INIT_VERTEX_ARRAY[i].position.x * scale[0] + pos[0]) - CAM_X) + (WIDTH / 2);
		VERTEX_ARRAY[i].position.y = ZOOM * ((INIT_VERTEX_ARRAY[i].position.y * scale[1] + pos[1]) - CAM_Y) + (HEIGHT / 2);
	}
}
