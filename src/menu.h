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
	int selected;			// currently selected app index

	// graphic pieces for labels
	SDL_Texture* name_g;
	SDL_Texture* desc_g;
	SDL_Texture* auth_g;

	struct tile* apps;		// array of apps along the bottom
	int apps_count;			// number of total apps (tiles)
};

void display_app(struct menu* self);
void menu_init(struct menu* self);
void list_apps(struct menu* self, struct graphics* g);
void render_menu(struct menu* self, struct graphics* g);
