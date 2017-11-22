#include <SDL2/SDL.h>
#include "../jsmn/jsmn.h"
#include "app_tile.h"

#pragma once

struct main_menu
{
	char* name;			// app name parsed from json
	char* description;		// app (short) description
	char* author;			// author of selected app
	int current;			// currently selected app index

	// graphic pieces for labels
	SDL_Texture* name_g;
	SDL_Texture* desc_g;
	SDL_Texture* auth_g;

	struct app_tile* apps;		// all apps along the bottom
};

void display_app(struct main_menu* self, char* path, int selected);
void main_menu_init(struct main_menu* self);
