#ifndef Primitives_h
#define Primitives_h
#include <SDL.h>



SDL_Point SDL_RECTANGLE_PRIMITIVE[7] = 
						{SDL_Point{-1, 1}, SDL_Point{ 1,-1}, 
						 SDL_Point{-1,-1}, SDL_Point{-1, 1}, 
						 SDL_Point{ 1, 1}, SDL_Point{ 1,-1},
						 SDL_Point{-1, 1}};

SDL_Point SDL_TRIANGLE_PRIMITIVE[7] =
						{ SDL_Point{ 0, 1}, SDL_Point{ 1,-1},
						  SDL_Point{-1,-1}, SDL_Point{ 0, 1}};

#endif


