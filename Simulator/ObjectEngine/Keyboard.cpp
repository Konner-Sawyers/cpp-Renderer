#include "Keyboard.h"

Keyboard::Keyboard(){
	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
	zoomIn = false;
	zoomOut = false;
}

void Keyboard::update_keybord_events(bool* running) {
	
	if (Events.type == SDL_QUIT) {
		*running = false;
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
		case SDLK_r:
			zoomIn = true;
			break;
		case SDLK_f:
			zoomOut = true;
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
		case SDLK_r:
			zoomIn = false;
			break;
		case SDLK_f:
			zoomOut = false;
		}
	}
}

void Keyboard::update_keypress_values(float* camera_pos_x, float* camera_pos_y, float* zoom, float* cameraSpeed, float* zoomSpeed) {
	if (moveUp == true) {
		*camera_pos_y -= *cameraSpeed;
	}
	else if (moveDown == true) {
		*camera_pos_y += *cameraSpeed;
	}
	if (moveLeft == true) {
		*camera_pos_x -= *cameraSpeed;
	}
	else if (moveRight == true) {
		*camera_pos_x += *cameraSpeed;
	}
	if (zoomIn == true) {
		*zoom += *zoomSpeed;
		if (*zoom >= 2) {
			*zoom = 2;
		}
	}
	else if (zoomOut == true) {
		*zoom -= *zoomSpeed;
		if (*zoom <= .5) {
			*zoom = .5;
		}
	}
}