#ifndef Engine_Window_h
#define Engine_Window_h
#include "Entity.h"
#include <SDL.h>

class Engine_Window
{
	
public:
	SDL_Window* engine_window;
	SDL_Renderer* simulation_renderer;

	Engine_Window(int = 720, int = 560);

	auto Get_Window_Size();

	void Render_Geometry(Entity* entity, SDL_Texture* texture);

	void Render_Crosshair();

	void Prepare_Window();
};



#endif