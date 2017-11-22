#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once

struct graphics
{
	SDL_Window* window;		// main window
	SDL_Renderer* renderer;		// main canvas	
};

void graphics_init(struct graphics* self);
void clear(struct graphics* self);
void repaint(struct graphics* self);
void drawText(struct graphics* self, int x, int y, char* text);
