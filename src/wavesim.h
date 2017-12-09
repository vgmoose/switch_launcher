#include "graphics.h"

#define WATER_RESOLUTION WIDTH / 5.0

// starting water level
#define WATER_LEVEL HEIGHT / 1.75

// height of snap-splash
#define WAVE_HEIGHT 1600

// spring settings
#define TENSION 0.025
#define DAMPENING 0.015
#define SPREAD 0.25

struct spring
{
	float x;
	float y;
	float target;
	float speed;
};

void spring_init(struct spring* self, float x, float y, float speed);
void spring_update(struct spring* self, float dampening, float tension);

struct wave
{
	struct spring* springs;
	int springs_len;
	int* fillStyle;
};

void wave_init(struct wave* self, char r, char g, char b);
void wave_update(struct wave* self);
void wave_draw(struct wave* self, struct graphics* ctx);
void wave_splash(struct wave* self, int springIndex, int value);
