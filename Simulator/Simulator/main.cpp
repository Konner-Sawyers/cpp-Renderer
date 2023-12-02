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
#include "particle.h"



int main() {

	int windowWidth = 720;
	int windowHeight = 560;

	particle particlesArray[30];

	for (int i = 0; i < sizeof(particlesArray)/sizeof(particlesArray[0]); i++) {
		glm::vec3 posIn(rand() % windowWidth, rand() % windowHeight, 0.f), velIn((rand() % 15) - 8, (rand() % 15) - 8, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(rand() % 255, 100.f, rand() % 255);
		particlesArray[i].SetVariables(posIn, velIn, forceIn, colorIn, 5.f, 20.f);
	}
	

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf(SDL_GetError());
	}



	//Window creation
	SDL_Window* myWindow = SDL_CreateWindow("Simulation Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

	//Define renderer
	SDL_Renderer* simulationRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);


	bool simRunning = true;
	
	auto pastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto timeDelta = std::chrono::duration<float>(currentTime - pastTime);
	
	SDL_Event Events;

	//Infinite loop to keep window open 
	while (simRunning) {

		while (SDL_PollEvent(&Events) != 0){
			if (Events.type == SDL_QUIT) {
				simRunning = false;
			}
		}

		SDL_SetRenderDrawColor(simulationRenderer, 0, 0, 0, 255);
		SDL_RenderClear(simulationRenderer);

		currentTime = std::chrono::high_resolution_clock::now();
		timeDelta = std::chrono::duration<float>(currentTime - pastTime);

		for (int i = 0; i < sizeof(particlesArray) / sizeof(particlesArray[0]); i++) {
			SDL_SetRenderDrawColor(simulationRenderer, particlesArray[i].getColor()[0], particlesArray[i].getColor()[1], particlesArray[i].getColor()[2], 255);
			
			//Collision checker
			for (int j = i + 1; j < sizeof(particlesArray) / sizeof(particlesArray[0]); j++) {
				if (pow(pow(particlesArray[i].getPosX() - particlesArray[j].getPosX(), 2) + pow(particlesArray[i].getPosY() - particlesArray[j].getPosY(), 2), 0.5) <= particlesArray[i].getRadius() + particlesArray[j].getRadius()) {
					std::cout << "COLLISION" << std::endl;
					float disX = (particlesArray[i].getPosX() - particlesArray[j].getPosX()/2);
					float disY = (particlesArray[i].getPosY() - particlesArray[j].getPosY() / 2);
				}
			}
			
			particlesArray[i].BoundryCheck(windowWidth, windowHeight);
			particlesArray[i].UpdateVelocity(timeDelta.count());
			particlesArray[i].UpdatePosition(timeDelta.count());
			particlesArray[i].drawArray(simulationRenderer);
		}
		SDL_RenderPresent(simulationRenderer);
		
		pastTime = currentTime;
	}

	return 0;
}