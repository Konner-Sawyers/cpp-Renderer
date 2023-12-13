#ifndef Keyboard_h
#define Keyboard_h
#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <SDL.h>



class Keyboard
{
private:
	bool moveUp, moveDown,
		 moveRight, moveLeft,
		 zoomIn, zoomOut;

public:
	SDL_Event Events;


	Keyboard();

	void update_keybord_events(bool* running);

	void update_keypress_values(float* camera_pos_x, float* camera_pos_y, float* zoom, float* cameraSpeed, float* zoomSpeed, float timeDelta);

};

#endif