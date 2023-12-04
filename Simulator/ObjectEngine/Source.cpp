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

int main(){

	std::cout << "Launching Program..." << std::endl;

	int SIMULATION_WINDOW_WIDTH = 720;
	int SIMULATION_WINDOW_HEIGHT = 560;

	int CAMERA_POS_X = 0;
	int CAMERA_POS_Y = 0;

	Engine_Window window;

	//Defining rectangle objects
	Static_Rectangle Static_Rectangle_Array[3];
		for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
			if (i == 0) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 500.f, 300.f }, 55); }
			if (i == 1) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 100.f, 700.f }, 55); }
			if (i == 2) { Static_Rectangle_Array[i] = Static_Rectangle(100.f, 100.f, glm::vec2{ 300.f, 10.f }, 55); }
		};

	/*
	 *
	 *CONVER PROGRAM TO USE RENDER_GEOMETRY INSTEAD OF RENDER_LINES
	 *
	 */

	SDL_Event Events;

	int Speed = 8;

	bool simRunning = true;

	SDL_Texture* obama = IMG_LoadTexture(window.simulation_renderer, "ObamaFace.png");


	while (simRunning) {

		while (SDL_PollEvent(&Events) != 0) {
			
			if (Events.type == SDL_QUIT) {
				simRunning = false;
			}

			//Handling for keyboard input
			if (Events.type == SDL_KEYDOWN) {
				if (Events.key.keysym.sym == SDLK_w) {
					CAMERA_POS_Y += Speed;
				}
				if (Events.key.keysym.sym == SDLK_s) {
					CAMERA_POS_Y -= Speed;
				}
				if (Events.key.keysym.sym == SDLK_a) {
					CAMERA_POS_X += Speed;
				}
				if (Events.key.keysym.sym == SDLK_d) {
					CAMERA_POS_X -= Speed;
				}
			}

			//Translates all objects to match relative position with camera
			for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
				Static_Rectangle_Array[i].VERTEX_ARRAY[0].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[0].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[1].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[1].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[2].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[2].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[3].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[3].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[4].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[4].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[5].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[5].x + CAMERA_POS_X;
				Static_Rectangle_Array[i].VERTEX_ARRAY[6].x = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[6].x + CAMERA_POS_X;

				Static_Rectangle_Array[i].VERTEX_ARRAY[0].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[0].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[1].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[1].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[2].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[2].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[3].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[3].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[4].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[4].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[5].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[5].y + CAMERA_POS_Y;
				Static_Rectangle_Array[i].VERTEX_ARRAY[6].y = Static_Rectangle_Array[i].VERTEX_ARRAY_WORLD_POS[6].y + CAMERA_POS_Y;

			}
			
			std::cout << (CAMERA_POS_X) << " : " << (CAMERA_POS_Y) << std::endl;

		}



		//Clear Screen
		SDL_SetRenderDrawColor(window.simulation_renderer, 50.f, 0.f, 50.f, 255.f);
		SDL_RenderClear(window.simulation_renderer);

		//Draws all vertex array points
		for (int i = 0; i < sizeof(Static_Rectangle_Array) / sizeof(Static_Rectangle_Array[0]); i++) {
			SDL_SetRenderDrawColor(window.simulation_renderer, i * 50.f, 255.f, 255.f, 255.f);
			SDL_RenderDrawLines(window.simulation_renderer, Static_Rectangle_Array[i].VERTEX_ARRAY, 7);
		}

		//Crosshair
		SDL_SetRenderDrawColor(window.simulation_renderer, 255.f, 255.f, 255.f, 255.f);
		SDL_RenderDrawLine(window.simulation_renderer, (SIMULATION_WINDOW_WIDTH / 2) - 15, SIMULATION_WINDOW_HEIGHT / 2, (SIMULATION_WINDOW_WIDTH / 2) + 15, SIMULATION_WINDOW_HEIGHT / 2);
		SDL_RenderDrawLine(window.simulation_renderer, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) - 15, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) + 15);
		SDL_RenderPresent(window.simulation_renderer);
	}


	return 0;
}