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

	particle particlesArray[2];
	int max_speed;
	max_speed = 2000;

	for (int i = 0; i < sizeof(particlesArray) / sizeof(particlesArray[0]); i++) {
		//glm::vec3 posIn(rand() % windowWidth, rand() % windowHeight, 0.f), velIn((rand() % max_speed) - max_speed/2, (rand() % max_speed) - max_speed/2, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(rand() % 255, 100.f, rand() % 255);
		//particlesArray[i].SetVariables(posIn, velIn, forceIn, colorIn, 5.f, 250.f);
		
		if (i == 0) {
			glm::vec3 posIn(300.f, 150.f, 0.f), velIn(0.f, 0.f, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(rand() % 255, 100.f, rand() % 255);
			particlesArray[0].SetVariables(posIn, velIn, forceIn, colorIn, 5.f, 120.f);
		}
		else {
			glm::vec3 posIn(320.f, 300.f, 0.f), velIn(0.f, -350.f, 0.f), forceIn(0.f, 0.f, 0.f), colorIn(rand() % 255, 100.f, rand() % 255);
			particlesArray[1].SetVariables(posIn, velIn, forceIn, colorIn, 5.f, 120.f);
		}

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
					float disX = (particlesArray[j].getPosX() - particlesArray[i].getPosX());
					float disY = (particlesArray[j].getPosY() - particlesArray[i].getPosY());

					float disH = std::sqrt((disX * disX) + (disY * disY));
					float adjustDistance = (particlesArray[j].getRadius() + particlesArray[i].getRadius() - disH)/2;



					float directionSecondary = atan(disY / disX);
					float directionPrimary = directionSecondary + M_PI;
					if (disX >= 0 && disY >= 0) {
						directionPrimary = M_PI + directionPrimary;
						directionSecondary = M_PI + directionSecondary;
					}
					else if (disX >= 0 && disY <= 0) {
						directionPrimary = M_PI + directionPrimary;
						directionSecondary = M_PI + directionSecondary;
					}
					else if (disX <= 0 && disY <= 0) {
						directionPrimary = 2 * M_PI + directionPrimary;
						directionSecondary = 2 * M_PI + directionSecondary;
					}

						

					particlesArray[j].SetPosition(glm::vec3(adjustDistance * (cos(directionPrimary)) + particlesArray[j].getPosX(), adjustDistance * (sin(directionPrimary)) + particlesArray[j].getPosY(), 0.f));
					particlesArray[i].SetPosition(glm::vec3(adjustDistance * (cos(directionSecondary)) + particlesArray[i].getPosX(), adjustDistance * (sin(directionSecondary)) + particlesArray[i].getPosY(), 0.f));
					


					//Object velocity relative
					float preCollisionVelocity1;
					float preCollisionVelocity2;

					preCollisionVelocity1 = sqrt(pow((particlesArray[j].getVelX() * cos(directionPrimary)), 2) + pow((particlesArray[j].getVelY() * sin(directionPrimary)), 2));
					preCollisionVelocity2 = sqrt(pow((particlesArray[i].getVelX() * cos(directionSecondary)), 2) + pow((particlesArray[i].getVelY() * sin(directionSecondary)), 2));

					std::cout << "PRE COLLISION " << preCollisionVelocity1 << ":" << preCollisionVelocity2 << " TOTAL: " << preCollisionVelocity1+preCollisionVelocity2 << std::endl;

					//Momentum Functions
					float postCollisionVelocity1;
					float postCollisionVelocity2;
					postCollisionVelocity1 = ((particlesArray[i].getMass() - particlesArray[j].getMass()) * preCollisionVelocity1 +2 * particlesArray[j].getMass() * preCollisionVelocity2 / (particlesArray[i].getMass() + particlesArray[j].getMass()));
					postCollisionVelocity2 = ((particlesArray[j].getMass() - particlesArray[i].getMass()) * preCollisionVelocity2 +2 * particlesArray[i].getMass() * preCollisionVelocity1 / (particlesArray[i].getMass() + particlesArray[j].getMass()));

					

					std::cout << "POST COLLISION " << postCollisionVelocity1 << ":" << postCollisionVelocity2 << " TOTAL: " << postCollisionVelocity1+postCollisionVelocity2 <<  std::endl;

					std::cout << "POST FUNCTIONS " << abs(postCollisionVelocity1 * cos(directionPrimary)) + abs(postCollisionVelocity2 * cos(directionSecondary)) << " : " << abs(postCollisionVelocity1 * sin(directionPrimary)) + abs(postCollisionVelocity2 * sin(directionSecondary)) << std::endl;


					particlesArray[j].SetVelocity(glm::vec3(postCollisionVelocity1 * cos(directionPrimary), postCollisionVelocity1 * sin(directionPrimary), 0.f));
					particlesArray[i].SetVelocity(glm::vec3(postCollisionVelocity2 * cos(directionSecondary), postCollisionVelocity2* sin(directionSecondary), 0.f));



					SDL_SetRenderDrawColor(simulationRenderer, 255, 255, 255, 255);
					
					SDL_RenderDrawLine(simulationRenderer, particlesArray[i].getPosX(), particlesArray[i].getPosY(), adjustDistance * (cos(M_PI / 2 + directionPrimary)) + particlesArray[i].getPosX(), adjustDistance * (sin(M_PI / 2 + directionPrimary))+ particlesArray[i].getPosY());
					SDL_RenderDrawLine(simulationRenderer, particlesArray[j].getPosX(), particlesArray[j].getPosY(), adjustDistance * (cos(M_PI / 2 + directionSecondary)) + particlesArray[j].getPosX(), adjustDistance * (sin(M_PI / 2 + directionSecondary)) + particlesArray[j].getPosY());
					SDL_SetRenderDrawColor(simulationRenderer, particlesArray[i].getColor()[0], particlesArray[i].getColor()[1], particlesArray[i].getColor()[2], 255);

					//std::cout << disH << std::endl;
				}
			}
			SDL_RenderDrawLine(simulationRenderer, particlesArray[i].getPosX(), particlesArray[i].getPosY(), particlesArray[i].getPosX() + particlesArray[i].getVelX(), particlesArray[i].getPosY() + particlesArray[i].getVelY());
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