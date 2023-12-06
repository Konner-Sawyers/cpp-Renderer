#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include "Engine_Window.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>



Engine_Window::Engine_Window(int SIMULATION_WINDOW_WIDTH, int SIMULATION_WINDOW_HEIGHT) {

	SDL_Init(SDL_INIT_VIDEO);

	//Create Window
	engine_window = SDL_CreateWindow("Simulation Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	//Define Renderer
	simulation_renderer = SDL_CreateRenderer(engine_window, -1, SDL_RENDERER_ACCELERATED);
}

int Engine_Window::Get_Size() {
	int RETRIEVED_WIDTH, RETRIEVED_HEIGHT;
	SDL_GetWindowSize(engine_window, &RETRIEVED_WIDTH, &RETRIEVED_HEIGHT);
	return(RETRIEVED_WIDTH);
}