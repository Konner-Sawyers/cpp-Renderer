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
#include "Rectangle_Object.h"
#include "Primitives.h"
#include <vector>
#include "Object_From_File.h"
#include <string>
#include "Entity.h"
#include "Keyboard.h"

int main() {

	std::cout << "Launching Program..." << std::endl;

	int SIMULATION_WINDOW_WIDTH = 1080;
	int SIMULATION_WINDOW_HEIGHT = 800;

	float CAMERA_POS_X = 0;
	float CAMERA_POS_Y = 0;
	float ZOOM = 1;

	float ZOOM_SPEED = .01;
	float Speed = 2;

	const int testValue = sizeof(RECT_INDICIES_ARRAY);
	int testArray[testValue];

	Engine_Window window(SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT);

	//Defining rectangle objects
	std::vector<Rectangle_Object> Static_Rectangle_Array;
	Static_Rectangle_Array.push_back(Rectangle_Object(glm::vec2{ 100.f, 100.f }, glm::vec2{ 300.f, 300.f }, 55));
	Static_Rectangle_Array.push_back(Rectangle_Object(glm::vec2{ 100.f, 100.f }, glm::vec2{ 100.f, 700.f }, 55));
	Static_Rectangle_Array.push_back(Rectangle_Object(glm::vec2{ 100.f, 100.f }, glm::vec2{ 300.f, 10.f }, 55));
	
	std::string myFile = "Test2.obj";


	Entity TEST_OBJECT = Entity(myFile, glm::vec2{ 100.f, 100.f }, glm::vec2{ 10.f, 10.f }, 55);


	/*
	 *
	 *CONVERT PROGRAM TO USE RENDER_GEOMETRY INSTEAD OF RENDER_LINES
	 *
	 */

	std::cout << RECT_VERTEX_ARRAY[0].position.x;

	SDL_Texture* wall = IMG_LoadTexture(window.simulation_renderer, "wall.png");

	bool running = true;
	
	Keyboard userKeyboard;

	while (running) {

		SDL_GetWindowSize(window.engine_window, &SIMULATION_WINDOW_WIDTH, &SIMULATION_WINDOW_HEIGHT);

		while (SDL_PollEvent(&userKeyboard.Events) != 0) {

			//Determines what keys are being pressed
			userKeyboard.update_keybord_events(&running);
			
			std::cout << (CAMERA_POS_X) << " : " << (CAMERA_POS_Y) << " ZOOM: " << ZOOM << std::endl;

		}

		//Updates values based on previously input keyboard presses
		userKeyboard.update_keypress_values(&CAMERA_POS_X, &CAMERA_POS_Y, &ZOOM, &Speed, &ZOOM_SPEED);


		//Translates all objects to match relative position with camera
		for (int i = 0; i < Static_Rectangle_Array.size(); i++) {
			Static_Rectangle_Array[i].ZoomUpdate(ZOOM, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT, CAMERA_POS_X, CAMERA_POS_Y);
		}

		TEST_OBJECT.ZoomUpdate(ZOOM, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT, CAMERA_POS_X, CAMERA_POS_Y);

		std::cout << Static_Rectangle_Array[0].VERTEX_ARRAY[0].position.x << " : " << Static_Rectangle_Array[0].VERTEX_ARRAY[0].position.y << std::endl;

		//Clear Screen
		SDL_SetRenderDrawColor(window.simulation_renderer, 50.f, 0.f, 50.f, 255.f);
		SDL_RenderClear(window.simulation_renderer);

		//Draws all vertex array points
		for (int i = 0; i < Static_Rectangle_Array.size(); i++) {
			SDL_RenderGeometry(window.simulation_renderer, wall, Static_Rectangle_Array[i].VERTEX_ARRAY, sizeof(Static_Rectangle_Array[i].VERTEX_ARRAY)/ sizeof(Static_Rectangle_Array[i].VERTEX_ARRAY[0]), Static_Rectangle_Array[i].INDICIES_ARRAY, sizeof(Static_Rectangle_Array[i].INDICIES_ARRAY)/sizeof(Static_Rectangle_Array[i].INDICIES_ARRAY[0]));
		}

		//std::cout << "TEST TEST TEST" << TEST_OBJECT.VERTEX_ARRAY[0].position.x << std::endl;

		SDL_RenderGeometry(window.simulation_renderer, wall, TEST_OBJECT.VERTEX_ARRAY.data(), TEST_OBJECT.VERTEX_ARRAY.size(), TEST_OBJECT.INDICIES_ARRAY.data(), TEST_OBJECT.INDICIES_ARRAY.size());


		//Crosshair
		SDL_SetRenderDrawColor(window.simulation_renderer, 255.f, 255.f, 255.f, 255.f);
		SDL_RenderDrawLine(window.simulation_renderer, (SIMULATION_WINDOW_WIDTH / 2) - 15, SIMULATION_WINDOW_HEIGHT / 2, (SIMULATION_WINDOW_WIDTH / 2) + 15, SIMULATION_WINDOW_HEIGHT / 2);
		SDL_RenderDrawLine(window.simulation_renderer, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) - 15, SIMULATION_WINDOW_WIDTH / 2, (SIMULATION_WINDOW_HEIGHT / 2) + 15);
		SDL_RenderPresent(window.simulation_renderer);
	}

	

	return 0;
}