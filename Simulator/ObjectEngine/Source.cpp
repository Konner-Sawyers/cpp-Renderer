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


	Engine_Window window(SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT);
	
	std::string myFile = "Test2.obj";
	std::string texture_file = "wall.png";

	//Entity TEST_OBJECT = Entity(myFile, glm::vec2{ 100.f, 100.f }, glm::vec2{ 10.f, 10.f }, 55);

	std::vector <Entity> entity_vector;
	entity_vector.push_back(Entity(myFile, texture_file, glm::vec2{ 100.f, 100.f }, glm::vec2{ 10.f, 10.f }, 55));



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
		for (int i = 0; i < entity_vector.size(); i++) {
			entity_vector[i].ZoomUpdate(ZOOM, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT, CAMERA_POS_X, CAMERA_POS_Y);
		}
		//Clear Screen
		window.Prepare_Window();

		//Draw Geometry
		for (int i = 0; i < entity_vector.size(); i++) {
			window.Render_Geometry(&entity_vector[i], wall);
		}
		//SDL_RenderGeometry(window.simulation_renderer, wall, TEST_OBJECT.VERTEX_ARRAY.data(), TEST_OBJECT.VERTEX_ARRAY.size(), TEST_OBJECT.INDICIES_ARRAY.data(), TEST_OBJECT.INDICIES_ARRAY.size());


		//Crosshair
		window.Render_Crosshair();
	}

	

	return 0;
}