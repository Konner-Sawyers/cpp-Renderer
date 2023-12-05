#ifndef Primitives_h
#define Primitives_h
#include <SDL.h>

/*
* DEFINE ENUM
*/

static enum Shape {RECTANGLE, TRIANGLE};


/*
*
* DEFINE COLORS
*
*/

static SDL_Color RED = { 255, 0, 0, 255 };
static SDL_Color GREEN = { 0, 255, 0, 255 };
static SDL_Color BLUE = { 0, 0, 255, 255 };
static SDL_Color WHITE = { 255, 255, 255, 255 };

/*
*
* DEFINE VERTEX ARRAYS BELOW
*
*/

static SDL_Vertex RECT_VERTEX_ARRAY[4] = {
								SDL_Vertex{{-1, 1}, RED,  {0, 0}} ,  //Top Left
								SDL_Vertex{{ 1, 1}, GREEN, {1, 0}} , //Top Right
								SDL_Vertex{{ 1,-1}, BLUE, {1, 1}} ,  //Bottom Right
								SDL_Vertex{{-1,-1}, RED, {0, 1}} };  //Bottom Left

static SDL_Vertex SDL_TRIANGLE_PRIMITIVE[3] = {
								SDL_Vertex{{-1, 1}, RED,  {0, 0}} ,  //Top Left
								SDL_Vertex{{ 1, 1}, GREEN, {1, 0}} , //Top Right
								SDL_Vertex{{ 0,-1}, BLUE, {1, 1}} }; //Bottom Right

									  
/*
*
* DEFINE INDICIES ARRAYS BELOW
*
*/

static int RECT_INDICIES_ARRAY[6] = { 0,2,3,0,1,2 };

#endif


