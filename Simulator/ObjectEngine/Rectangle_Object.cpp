#include "Rectangle_Object.h"

void Rectangle_Object::ZoomUpdate(float ZOOM, int WIDTH, int HEIGHT, float CAM_X, float CAM_Y)
{
	for (int i = 0; i < 4; i++) {
		VERTEX_ARRAY[i] = RECT_VERTEX_ARRAY[i];
		VERTEX_ARRAY_WORLD[i] = RECT_VERTEX_ARRAY[i];
	}

	for (int i = 0; i < sizeof(VERTEX_ARRAY) / sizeof(VERTEX_ARRAY[0]); i++) {
		VERTEX_ARRAY[i].position.x = ZOOM * ((VERTEX_ARRAY_WORLD[i].position.x * scale[0] + pos[0]) - CAM_X) + (WIDTH/2);
		VERTEX_ARRAY[i].position.y = ZOOM * ((VERTEX_ARRAY_WORLD[i].position.y * scale[1] + pos[1]) - CAM_Y) + (HEIGHT / 2);
	}
}
