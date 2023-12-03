#ifndef particle_h
#define particle_h
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <SDL.h>
#include <SDL_image.h>

class particle
{

	glm::vec3 pos, vel, force, color;
	float mass, radius;
	SDL_Point pointsArray[360];

public:

	particle(glm::vec3  = { 0.f, 0.f, 0.f }, glm::vec3  = { 0.f, 0.f, 0.f }, glm::vec3  = { 0.f, 0.f, 0.f }, glm::vec3  = { 255.f, 255.f, 255.f }, float  = 1, float  = 10);

	void SetVariables(glm::vec3 posIn = { 0.f, 0.f, 0.f }, glm::vec3 velIn = { 0.f, 0.f, 0.f }, glm::vec3 forceIn = { 0.f, 0.f, 0.f }, glm::vec3 colorIn = { 255.f, 255.f, 255.f }, float massIn = 1, float radiusIn = 10);

	void SetPosition(glm::vec3 posIn);

	void BoundryCheck(int width, int height);

	void PrintPosition();

	void UpdateVelocity(float timeDelta);

	void UpdatePosition(float timeDelta);

	float getPosX();

	float getPosY();

	float getPosZ();

	float getRadius();

	void drawArray(SDL_Renderer* simulationRenderer);

	glm::vec3 getColor();
	
};

#endif