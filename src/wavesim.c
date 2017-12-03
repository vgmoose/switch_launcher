#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "wavesim.h"

void spring_init(struct spring* self, float x, float y, float speed)
{
	self->x = x;
	self->y = y;
	self->target = y;
	self->speed = speed;
}

void spring_update(struct spring* self, float dampening, float tension)
{
	float dist = self->target - self->y;
	self->speed += tension * dist - self->speed * dampening;
	self->y += self->speed;
}

void wave_init(struct wave* self, char r, char g, char b)
{
	self->springs = malloc(sizeof(struct spring)*WATER_RESOLUTION);
	self->springs_len = WATER_RESOLUTION;
	
	for (int i = 0; i < WATER_RESOLUTION; i++) {
	  int x = (WIDTH / (WATER_RESOLUTION - 1)) * i;
	  spring_init(&self->springs[i], x, WATER_LEVEL, 0);
	}
	
//	self->fillStyle = {r, g, b};
}

void wave_update(struct wave* self)
{
	struct spring* springs = self->springs;
	int count = self->springs_len;

	for (int i = 0; i < count; i++) {
		spring_update(&self->springs[i], DAMPENING, TENSION);
	}

	float* lDeltas = malloc(sizeof(float)*count);
	float* rDeltas = malloc(sizeof(float)*count);
	
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < count; i++) {
			if (i > 0) {
				lDeltas[i] = SPREAD * (springs[i].y - springs[i - 1].y);
				springs[i - 1].speed += lDeltas[i];
			}
			if (i < count - 1) {
				rDeltas[i] = SPREAD * (springs[i].y - springs[i + 1].y);
				springs[i + 1].speed += rDeltas[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (i > 0) {
				springs[i - 1].y += lDeltas[i];
			}
			if (i < count - 1) {
				springs[i + 1].y += rDeltas[i];
			}
		}
	}
	
	free(lDeltas);
	free(rDeltas);
}

void wave_draw(struct wave* self, struct graphics* graphics)
{
	SDL_Renderer* ctx = graphics->renderer;	
	
	// create point vectors (+2 for corners)
	int points_len = self->springs_len + 2;
	Sint16* pointsX = malloc(sizeof(int)*points_len);
	Sint16* pointsY = malloc(sizeof(int)*points_len);
	
	// start drawing the top edge of the wave shape using values from the springs
	for (int i = 0; i < self->springs_len; i++) {
		int x = self->springs[i].x;
		int y = self->springs[i].y;
		
		pointsX[i] = x;
		pointsY[i] = y;
	}
	
	// add bottom right and left corners to the wave shape
	pointsX[points_len-2] = WIDTH;
	pointsY[points_len-2] = HEIGHT;
	pointsX[points_len-1] = 0;
	pointsY[points_len-1] = HEIGHT;
	
	// close the shape path and fill it with the wave's color
	filledPolygonRGBA(ctx, pointsX, pointsY, points_len,
					  0x7A, 0x77, 0xEF, 0xaa);
	
	free(pointsX);
	free(pointsY);
}