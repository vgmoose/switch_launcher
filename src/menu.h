#include <SDL2/SDL.h>
#include "../jsmn/jsmn.h"
#include "tile.h"
#include "graphics.h"

#pragma once

struct menu
{
	char* name;			// app name parsed from json
	char* description;		// app (short) description
	char* author;			// author of selected app
	int current;			// currently selected app index

	// graphic pieces for labels
	SDL_Texture* name_g;
	SDL_Texture* desc_g;
	SDL_Texture* auth_g;

	struct graphics* g;		// reference to main graphics struct

	struct tile* apps;		// all apps along the bottom
};

void display_app(struct menu* self, char* path, int selected);
void menu_init(struct menu* self, struct graphics* g);
void render_menu(struct menu* self, struct graphics* g);
