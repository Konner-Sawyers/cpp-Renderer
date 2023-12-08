#ifndef Custom_Object_h
#define Custom_Object_h
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

class Custom_Object
{
public:
	std::vector<SDL_Vertex> VERTEX_ARRAY, VERTEX_ARRAY_WORLD, INIT_VERTEX_ARRAY;
	std::vector<int> INDICIES_ARRAY;
	glm::vec2 pos, scale;
	float mass;

	Custom_Object(std::string FileName, glm::vec2 scaleIn = { 1,1 }, glm::vec2 posIn = { 0,0 }, float massIn = 1) {
		Object_From_File OBJECT_DATA = Object_From_File(FileName);

		pos = posIn;
		scale = scaleIn;
		mass = massIn;

		for (int i = 0; i < OBJECT_DATA.VERTEX_ARRAY.size(); i++) {
			INIT_VERTEX_ARRAY.push_back(OBJECT_DATA.VERTEX_ARRAY[i]);
			VERTEX_ARRAY_WORLD.push_back(OBJECT_DATA.VERTEX_ARRAY[i]);
			VERTEX_ARRAY.push_back(OBJECT_DATA.VERTEX_ARRAY[i]);
		}

		for (int i = 0; i < OBJECT_DATA.INDICIES_ARRAY.size(); i++) {
			INDICIES_ARRAY.push_back(OBJECT_DATA.INDICIES_ARRAY[i]);
		}

		for (int i = 0; i < INIT_VERTEX_ARRAY.size(); i++) {
			VERTEX_ARRAY_WORLD[i].position.x = pos[0] + (INIT_VERTEX_ARRAY[i].position.x * scale[0] * 1);
			VERTEX_ARRAY_WORLD[i].position.y = pos[1] + (INIT_VERTEX_ARRAY[i].position.y * scale[1] * -1);
		}

	};

	void ZoomUpdate(float ZOOM, int WIDTH, int HEIGHT, float CAM_X, float CAM_Y);


};

#endif