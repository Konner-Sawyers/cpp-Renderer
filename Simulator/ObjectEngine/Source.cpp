#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
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

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf(SDL_GetError());
	}

	std::cout << "Launching Program..." << std::endl;

	int SIMULATION_WINDOW_WIDTH = 1080;
	int SIMULATION_WINDOW_HEIGHT = 800;

	float CAMERA_POS_X = 0;
	float CAMERA_POS_Y = 0;
	float ZOOM = 1;

	float ZOOM_SPEED = 2;
	float Speed = 500;


	Engine_Window window(SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT);
	
	std::string myFile = "Circle32Verts.obj";
	std::string texture_file = "ball.png";

	SDL_Texture* ball = IMG_LoadTexture(window.simulation_renderer, "ball.png");
	SDL_Texture* wall = IMG_LoadTexture(window.simulation_renderer, "wall.png");

	std::vector <Entity> entity_vector;
	entity_vector.push_back(Entity(myFile, ball, glm::vec2{ 100.f, 100.f }, glm::vec2{ 10.f, 10.f }, 55));

	myFile = "Test2.obj";

	entity_vector.push_back(Entity(myFile, wall, glm::vec2{ 10.f, 100.f }, glm::vec2{ 50.f, 0.f }, 55));
	entity_vector.push_back(Entity(myFile, wall, glm::vec2{ 10.f, 100.f }, glm::vec2{ -50.f, 0.f }, 55));
	entity_vector.push_back(Entity(myFile, wall, glm::vec2{ 100.f, 10.f }, glm::vec2{ 0.f, 50.f }, 55));
	entity_vector.push_back(Entity(myFile, wall, glm::vec2{ 100.f, 10.f }, glm::vec2{ 0.f, -50.f }, 55));

	

	bool running = true;
	
	Keyboard userKeyboard;

	auto pastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto timeDelta = std::chrono::duration<float>(currentTime - pastTime);

	while (running) {
		pastTime = currentTime;
		currentTime = std::chrono::high_resolution_clock::now();
		timeDelta = std::chrono::duration<float>(currentTime - pastTime);

		SDL_GetWindowSize(window.engine_window, &SIMULATION_WINDOW_WIDTH, &SIMULATION_WINDOW_HEIGHT);

		while (SDL_PollEvent(&userKeyboard.Events) != 0) {

			//Determines what keys are being pressed
			userKeyboard.update_keybord_events(&running);

		}

		//Updates values based on previously input keyboard presses
		userKeyboard.update_keypress_values(&CAMERA_POS_X, &CAMERA_POS_Y, &ZOOM, &Speed, &ZOOM_SPEED, timeDelta.count());



		//Translates all objects to match relative position with camera
		for (int i = 0; i < entity_vector.size(); i++) {
			entity_vector[i].ZoomUpdate(ZOOM, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT, CAMERA_POS_X, CAMERA_POS_Y);
		}
		//Clear Screen
		window.Prepare_Window();

		//Draw Geometry
		for (int i = 0; i < entity_vector.size(); i++) {
			window.Render_Geometry(&entity_vector[i]);
		}

		//Crosshair
		window.Render_Crosshair();
	}

	

	return 0;
}