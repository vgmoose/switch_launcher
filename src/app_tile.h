#include <SDL2/SDL.h>

#define ICON_WIDTH 128
#define SPACE_BETWEEN_ICONS 20

#pragma once

struct app_tile
{
	char* path;		// path to .app folder
	SDL_Texture* icon;	// icon from .app folder
	int y;			// current y position of tile
	int index;		// index of this tile in apps array
};
