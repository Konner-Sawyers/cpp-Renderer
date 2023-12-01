#define SDL_MAIN_HANDLED //Need this to avoid SDL error. Idk why tho :)
#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>


class Particle {
	glm::vec3 pos, vel, force, color;
	float mass, radius;
public:
	Particle(glm::vec3& posIn, glm::vec3 velIn, glm::vec3 forceIn, glm::vec3 colorIn, float massIn, float radiusIn) {
		pos = posIn;
		vel = velIn;
		force = forceIn;
		color = colorIn;
		mass = massIn;
		radius = radiusIn;
	}

	void BoundryCheck() {
		
	}

	void PrintPosition() {
		std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
	}

	void UpdatePosition() {
		pos = pos + vel;
	}

	float getPosX() {
		return pos[0];
	}

	float getPosY() {
		return pos[1];
	}

	float getPosZ() {
		return pos[2];
	}

};



int main() {
	glm::vec3 posIn(300.f, 300.f, 0.f), velIn(2.f, 2.f, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(255.f, 255.f, 255.f);

	Particle testObject(posIn, velIn, forceIn, colorIn, 5.f, 3.f);

	testObject.PrintPosition();
	testObject.UpdatePosition();
	testObject.PrintPosition();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf(SDL_GetError());
	}

	int windowWidth = 720;
	int windowHeight = 560;

	//Window creation
	SDL_Window* myWindow = SDL_CreateWindow("Simulation Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

	//Define renderer
	SDL_Renderer* simulationRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);


	SDL_Point pointsArray[360];
	float radians;
	for (int i = 0; i < 360; i++) {
		
		radians = i * (M_PI / 180);
		
		pointsArray[i].x = cos(radians);
		pointsArray[i].y = sin(radians);


	}

	bool simRunning = true;

	//Infinite loop to keep window open 
	while (simRunning) {

		SDL_SetRenderDrawColor(simulationRenderer, 0, 0, 0, 255);
		//SDL_RenderClear(simulationRenderer);

		testObject.BoundryCheck();
		testObject.UpdatePosition();
		
		
		SDL_SetRenderDrawColor(simulationRenderer, 255, 255, 255, 255);
		SDL_RenderDrawPoint(simulationRenderer, testObject.getPosX(), testObject.getPosY());




		//SDL_RenderDrawLines(simulationRenderer, pointsArray, 360);

		SDL_RenderPresent(simulationRenderer);

	}

	return 0;
}