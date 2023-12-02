#define _USE_MATH_DEFINES
#include "particle.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <iostream>


glm::vec3 pos, vel, force, color;
float mass, radius;
SDL_Point pointsArray[360];


particle::particle(glm::vec3 posIn, glm::vec3 velIn, glm::vec3 forceIn, glm::vec3 colorIn, float massIn, float radiusIn) {
	pos = posIn;
	vel = velIn;
	force = forceIn;
	color = colorIn;
	mass = massIn;
	radius = radiusIn;


	for (int i = 0; i < 360; i++) {

		pointsArray[i].x = (cos(i * (M_PI / 180)) * radius) + pos[0];
		pointsArray[i].y = (sin(i * (M_PI / 180)) * radius) + pos[1];

	}

}

void particle::SetVariables(glm::vec3 posIn, glm::vec3 velIn, glm::vec3 forceIn, glm::vec3 colorIn, float massIn, float radiusIn) {
	pos = posIn;
	vel = velIn;
	force = forceIn;
	color = colorIn;
	mass = massIn;
	radius = radiusIn;
}

void particle::BoundryCheck(int width, int height) {
	if (pos[0] - radius <= 0) {
		pos[0] = 0 + radius;
		vel[0] *= -1;
	}

	if (pos[0] + radius >= width) {
		pos[0] = width - radius;
		vel[0] *= -1;
	}

	if (pos[1] - radius <= 0) {
		pos[1] = 0 + radius;
		vel[1] *= -1;
	}

	if (pos[1] + radius >= height) {
		pos[1] = height - radius;
		vel[1] *= -1;
	}
}

void particle::PrintPosition() {
	std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
}

void particle::UpdateVelocity(float timeDelta) {
	vel = vel + force * (timeDelta);
}

void particle::UpdatePosition(float timeDelta) {
	pos = pos + vel * timeDelta;

	for (int i = 0; i < 360; i++) {

		pointsArray[i].x = ((cos(i * (M_PI / 180)) * radius)) + pos[0];
		pointsArray[i].y = ((sin(i * (M_PI / 180)) * radius)) + pos[1];

	}

}

float particle::getPosX() {
	return pos[0];
}

float particle::getPosY() {
	return pos[1];
}

float particle::getPosZ() {
	return pos[2];
}

float particle::getRadius() {
	return radius;
}

void particle::drawArray(SDL_Renderer* simulationRenderer) {
	SDL_RenderDrawPoints(simulationRenderer, pointsArray, 360);
}

glm::vec3 particle::getColor() {
	return color;
}
