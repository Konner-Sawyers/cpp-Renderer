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

auto Engine_Window::Get_Window_Size() {
	int RETRIEVED_WIDTH, RETRIEVED_HEIGHT;
	SDL_GetWindowSize(engine_window, &RETRIEVED_WIDTH, &RETRIEVED_HEIGHT);
	struct{ 
		int width;
		int height;
	}window_size;

	window_size.width = RETRIEVED_WIDTH;
	window_size.height = RETRIEVED_HEIGHT;

	return window_size;
}

void Engine_Window::Render_Geometry(Entity* entity, SDL_Texture* texture) {
	//SDL_Texture* texture = IMG_LoadTexture(simulation_renderer, (entity->texture_file_name).c_str());
	SDL_RenderGeometry(simulation_renderer, texture, entity->VERTEX_ARRAY.data(), entity->VERTEX_ARRAY.size(), entity->INDICIES_ARRAY.data(), entity->INDICIES_ARRAY.size());

}

void Engine_Window::Render_Crosshair() {
	SDL_SetRenderDrawColor(simulation_renderer, 255.f, 255.f, 255.f, 255.f);
	auto window_size = Get_Window_Size();
	SDL_RenderDrawLine(simulation_renderer, (window_size.width / 2) - 15, window_size.height / 2, (window_size.width / 2) + 15, window_size.height / 2);
	SDL_RenderDrawLine(simulation_renderer, window_size.width / 2, (window_size.height / 2) - 15, window_size.width / 2, (window_size.height / 2) + 15);
	SDL_RenderPresent(simulation_renderer);
}

void Engine_Window::Prepare_Window() {
	SDL_SetRenderDrawColor(simulation_renderer, 50.f, 0.f, 50.f, 255.f);
	SDL_RenderClear(simulation_renderer);
}

void Draw_Window_Entities() {

}