#include "graphics.h"
#include "waterboi.h"
#include <SDL2/SDL2_gfxPrimitives.h>

void WaterBoi_init(struct WaterBoi* self)
{
    self->x = 0;
    self->y = 0;
    self->width = 0;
    self->height = 0;
    self->waves_length = WAVES_LENGTH;

    self->level = 0;
    self->waves = malloc(sizeof(struct Wave) * WAVES_LENGTH);
    
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    srand(time(0));
    
    Wave_init(&self->waves[0], 0x7A, 0x77, 0xEF, self);
    Wave_init(&self->waves[1], 0x77, 0xB5, 0xEF, self);
    Wave_init(&self->waves[2], 0x77, 0xEF, 0xCA, self);
    Wave_init(&self->waves[3], 0x75, 0x8E, 0xD1, self);
    Wave_init(&self->waves[4], 0x77, 0xD8, 0xEF, self);

    
    WaterBoi_recalculate(self);
}

void WaterBoi_recalculate(struct WaterBoi* self) {
    self->width = WIDTH;
    self->height = HEIGHT / 2.6;
    self->x = 0;
    self->y = HEIGHT - self->height;

    self->level = self->height / 2;
    self->resolution = self->width / 2;

    for (int i = 0; i < self->waves_length; i++)
        Wave_recalculate(&self->waves[i]);
}

void WaterBoi_draw(struct WaterBoi* self, struct graphics* graphics) {
    for (int i = 0; i < self->waves_length; i++)
        Wave_draw(&self->waves[i], graphics);
}

void Wave_init(struct Wave* self, char r, char g, char b, struct WaterBoi* manager)
{
    self->manager = manager;
    self->r = r;
    self->g = g;
    self->b = b;
    
    self->i = 0;
}

void Wave_recalculate(struct Wave* self) {
    self->offset = self->manager->y / 15 * (random() / (double)RAND_MAX);
}

void Wave_draw(struct Wave* self, struct graphics* graphics)
{
    SDL_Renderer* ctx = graphics->renderer;	
	
	// create point vectors (+2 for corners)
	int points_len = 1 + self->manager->width + 2;
	Sint16* pointsX = malloc(sizeof(int)*points_len);
	Sint16* pointsY = malloc(sizeof(int)*points_len);
    
    pointsX[0] = 0;
    pointsY[0] = self->manager->y + self->manager->level;

    int y;
    for (int i = 1; i < self->manager->width+1; i++) {
        y = sin(i * 0.007 + self->i + self->offset * 15) * self->manager->height / 15.0 + self->manager->height / 40 - self->offset;
        //Half assed attempt at cooler waves
        //y = Math.sin(i + this.i * 0.001) * Math.cos(1.5 * i) * this.manager.height / 15 + this.manager.height / 40 - this.offset;;
        pointsX[i] = i;
        pointsY[i] = self->manager->y + y;
    }

    self->i += self->offset / 1000.0;

    // add bottom right and left corners to the wave shape
	pointsX[points_len-2] = self->manager->width;
	pointsY[points_len-2] = self->manager->y + self->manager->height;
	pointsX[points_len-1] = 0;
	pointsY[points_len-1] = self->manager->y + self->manager->height;

	// close the shape path and fill it with the wave's color
	filledPolygonRGBA(ctx, pointsX, pointsY, points_len,
					  self->r, self->g, self->b, 0x40);
	
	free(pointsX);
	free(pointsY);
}