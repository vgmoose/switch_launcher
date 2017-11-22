#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once

#define WIDTH 1280
#define HEIGHT 720

#define FONT_SMALL 0
#define FONT_WRAP 1
#define FONT_LARGE 2

struct graphics
{
	SDL_Window* window;		// main window
	SDL_Renderer* renderer;		// main canvas	
	TTF_Font* fonts[3];
};

void graphics_init(struct graphics* self);
void clear(struct graphics* self);
void repaint(struct graphics* self);
void drawText(struct graphics* self, int x, int y, char* text);
void drawText_adv(struct graphics* self, int x, int y, int size, char* text);
