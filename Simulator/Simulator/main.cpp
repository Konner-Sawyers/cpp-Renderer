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
#include <conio.h>



int main() {

	int windowWidth = 720;
	int windowHeight = 560;

	particle particlesArray[6];
	int max_speed;
	max_speed = 500;

	for (int i = 0; i < sizeof(particlesArray)/sizeof(particlesArray[0]); i++) {
		glm::vec3 posIn(rand() % windowWidth, rand() % windowHeight, 0.f), velIn((rand() % max_speed) - max_speed/2, (rand() % max_speed) - max_speed/2, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(rand() % 255, 100.f, rand() % 255);
		particlesArray[i].SetVariables(posIn, velIn, forceIn, colorIn, 5.f, 120.f);
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

	int x_pos;
	int y_pos;
	x_pos = 0;
	y_pos = 0;

	SDL_SetRenderDrawColor(simulationRenderer, 255, 255, 255, 255);
	int horizontalLine = (simulationRenderer, x_pos, 0, x_pos, windowHeight);
	int verticleLine = (simulationRenderer, 0, y_pos, 0, windowWidth);



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
					float disX = (particlesArray[j].getPosX() - particlesArray[i].getPosX());
					float disY = (particlesArray[j].getPosY() - particlesArray[i].getPosY());

					float disH = std::sqrt((disX * disX) + (disY * disY));

					float adjustDistance = (particlesArray[j].getRadius() + particlesArray[i].getRadius() - disH)/2;



					//float directionPrimary = atan(disX / disY);
					float directionSecondary = atan(disY / disX);
					float directionPrimary = directionSecondary + M_PI;
					if (disX > 0 && disY > 0) {
						directionPrimary = M_PI + directionPrimary;
						directionSecondary = M_PI + directionSecondary;
					}
					else if (disX > 0 && disY < 0) {
						directionPrimary = M_PI + directionPrimary;
						directionSecondary = M_PI + directionSecondary;
					}
					else if (disX < 0 && disY < 0) {
						directionPrimary = 2 * M_PI + directionPrimary;
						directionSecondary = 2 * M_PI + directionSecondary;
					}

						



					//adjustDistance * (cos(directionPrimary));



					
					SDL_SetRenderDrawColor(simulationRenderer, 255, 255, 255, 255);

					SDL_RenderDrawLine(simulationRenderer, particlesArray[i].getPosX(), particlesArray[i].getPosY(), adjustDistance * (cos(directionPrimary)) + particlesArray[i].getPosX(), adjustDistance * (sin(directionPrimary))+ particlesArray[i].getPosY());
					SDL_RenderDrawLine(simulationRenderer, particlesArray[j].getPosX(), particlesArray[j].getPosY(), adjustDistance * (cos(directionSecondary)) + particlesArray[j].getPosX(), adjustDistance * (sin(directionSecondary)) + particlesArray[j].getPosY());
					//SDL_RenderDrawLine(simulationRenderer, particlesArray[j].getPosX(), particlesArray[j].getPosY(), particlesArray[i].getPosX(), particlesArray[i].getPosY());

					//system("cls");
					std::cout << disH << std::endl;
				}
			}
			particlesArray[i].BoundryCheck(windowWidth, windowHeight);
			particlesArray[i].UpdateVelocity(timeDelta.count());
			particlesArray[i].UpdatePosition(timeDelta.count());
			particlesArray[i].drawArray(simulationRenderer);
		}



		//Get mouse position and display it on screen
		SDL_GetMouseState(&x_pos, &y_pos);
		SDL_SetRenderDrawColor(simulationRenderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(simulationRenderer, x_pos, 0, x_pos, windowHeight);
		SDL_RenderDrawLine(simulationRenderer, 0, y_pos, windowWidth, y_pos);


		SDL_RenderPresent(simulationRenderer);
		
		pastTime = currentTime;
	}

	return 0;
}