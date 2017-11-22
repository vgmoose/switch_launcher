#include <SDL2/SDL.h>
#include "graphics.h"
#include <dirent.h>
#include <stdio.h>

static const char* APP_SUFFIX = ".app";
static const char* APP_PATH = "apps/";
#define APP_PATH_LEN 5

#define ICON_WIDTH 128
#define SPACE_BETWEEN_ICONS 20

#pragma once

struct tile
{
	char* path;		// path to .app folder
	SDL_Texture* icon_g;	// icon from .app folder
	int x;			// current x position of tile
	int index;		// index of this tile in apps array
};

void tile_init(struct tile* self, struct graphics* g, char* path, int index);
void update_position(struct tile* self);
int is_valid_app(struct dirent* entry);
void render_tile(struct tile* self, struct graphics* g);
