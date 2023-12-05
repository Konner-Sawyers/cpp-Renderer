#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <array>
#include <vector>
#include <chrono>
#include <conio.h>
#include "Engine_Window.h"
#include "World_Object.h"
#include "Static_Object.h"
//#include "Primitives.h"
#include "Static_Triangle.h"
#include "Static_Rectangle.h"

int main() {

	std::cout << "Launching Program..." << std::endl;

	int SIMULATION_WINDOW_WIDTH = 720;
	int SIMULATION_WINDOW_HEIGHT = 560;

	int CAMERA_POS_X = 0;
	int CAMERA_POS_Y = 0;

	Engine_Window window;

	//Defining rectangle objects
	Static_Rectangle Static_Rectangle_Array[3];
	for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
		if (i == 0) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 300.f, 300.f }, 55); }
		if (i == 1) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 100.f, 700.f }, 55); }
		if (i == 2) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 300.f, 10.f }, 55); }
	};

	/*
	 *
	 *CONVERT PROGRAM TO USE RENDER_GEOMETRY INSTEAD OF RENDER_LINES
	 *
	 */

	SDL_Event Events;

	int Speed = 1;

	bool simRunning = true;

	bool moveUp = false;
	bool moveDown = false;
	bool moveRight = false;
	bool moveLeft = false;

	SDL_Texture* obama = IMG_LoadTexture(window.simulation_renderer, "ObamaFace.png");


	while (simRunning) {

		while (SDL_PollEvent(&Events) != 0) {

			if (Events.type == SDL_QUIT) {
				simRunning = false;
			}


			//Handling for keyboard input
			if (Events.type == SDL_KEYDOWN) {
				switch (Events.key.keysym.sym) {
				case SDLK_w:
					moveUp = true;
					break;
				case SDLK_s:
					moveDown = true;
					break;
				case SDLK_a:
					moveLeft = true;
					break;
				case SDLK_d:
					moveRight = true;
					break;
				}
			}

			if (Events.type == SDL_KEYUP) {
				switch (Events.key.keysym.sym) {
				case SDLK_w:
					moveUp = false;
					break;
				case SDLK_s:
					moveDown = false;
					break;
				case SDLK_a:
					moveLeft = false;
					break;
				case SDLK_d:
					moveRight = false;
					break;
				}
			}

			std::cout << (CAMERA_POS_X) << " : " << (CAMERA_POS_Y) << std::endl;

		}

		if (moveUp == true) {
			CAMERA_POS_Y += Speed;
		}
		else if (moveDown == true) {
			CAMERA_POS_Y -= Speed;
		}
		if (moveLeft == true) {
			CAMERA_POS_X += Speed;
		}
		else if (moveRight == true) {
			CAMERA_POS_X -= Speed;
		}

		//Translates all objects to match relative position with camera
		for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
			Static_Rectangle_Array[i].VERTEX_ARRAY[0].position.x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[0].position.x + CAMERA_POS_X;
			Static_Rectangle_Array[i].VERTEX_ARRAY[1].position.x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[1].position.x + CAMERA_POS_X;
			Static_Rectangle_Array[i].VERTEX_ARRAY[2].position.x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[2].position.x + CAMERA_POS_X;
			Static_Rectangle_Array[i].VERTEX_ARRAY[3].position.x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[3].position.x + CAMERA_POS_X;

			Static_Rectangle_Array[i].VERTEX_ARRAY[0].position.y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[0].position.y + CAMERA_POS_Y;
			Static_Rectangle_Array[i].VERTEX_ARRAY[1].position.y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[1].position.y + CAMERA_POS_Y;
			Static_Rectangle_Array[i].VERTEX_ARRAY[2].position.y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[2].position.y + CAMERA_POS_Y;
			Static_Rectangle_Array[i].VERTEX_ARRAY[3].position.y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[3].position.y + CAMERA_POS_Y;

		}

		//Clear Screen
		SDL_SetRenderDrawColor(window.simulation_renderer, 50.f, 0.f, 50.f, 255.f);
		SDL_RenderClear(window.simulation_renderer);

		//Draws all vertex array points
		for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
			//SDL_SetRenderDrawColor(window.simulation_renderer, 255.f, 255.f, 255.f, 255.f);
			SDL_RenderGeometry(window.simulation_renderer, obama, Static_Rectangle_Array[i].VERTEX_ARRAY, 4, Static_Rectangle_Array[i].INDICIES_ARRAY, 6);
		}


		//Crosshair
		SDL_SetRenderDrawColor(window.simulation_renderer, 255.f, 255.f, 255.f, 255.f);
		SDL_RenderDrawLine(window.simulation_renderer, (SIMULATION_WINDOW_WIDTH / 2) - 15, SIMULATION_WINDOW_HEIGHT / 2, (SIMULATION_WINDOW_WIDTH / 2) + 15, SIMULATION_WINDOW_HEIGHT / 2);
		SDL_RenderDrawLine(window.simulation_renderer, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) - 15, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) + 15);
		SDL_RenderPresent(window.simulation_renderer);
	}

	

	return 0;
}