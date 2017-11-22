#include "tile.h"
#include "menu.h"
#include "graphics.h"
#include "utils.h"
#include <SDL2/SDL_image.h>

void tile_init(struct tile* self, struct graphics* g, char* path, int index)
{
	// set path for this app
	int path_len = strlen(path);
	self->path = malloc(APP_PATH_LEN + path_len + 1);
	strcpy(self->path, APP_PATH);
	strcat(self->path, path);

	self->index = index;

	// icon path
	const char* ICON_PATH = "/icon.png";
	char* iconPath = malloc(APP_PATH_LEN + path_len + strlen(ICON_PATH) + 1);
	strcpy(iconPath, self->path);
	strcat(iconPath, ICON_PATH);

	// load icon into memory
	SDL_Surface *bmpSurf = IMG_Load(iconPath);
	self->icon_g = SDL_CreateTextureFromSurface(g->renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);
}

void update_position(struct tile* self, int selected)
{
	// update the x-coordinate of this icon according to the menu
	// current frame
	self->x = 70 + self->index*ICON_WIDTH + self->index*SPACE_BETWEEN_ICONS;

	if (selected != self->index)
	{
		// pad the spacing some more to account for this
		int xOff = ((ICON_WIDTH*ICON_ACTIVE_SCALE) - ICON_WIDTH)/2;

		// positive offset to the right, negative to the left
		self->x += (self->index > selected)*xOff - (self->index < selected)*xOff;
	}
}

int is_valid_app(struct dirent* entry)
{
	// valid app if it's a directory and ends with '.app'
	// TODO: add more validation criteria here
	return (entry->d_type == DT_DIR && ends_with(entry->d_name, APP_SUFFIX));
}

void render_tile(struct tile* self, struct graphics* g, int selected)
{
	int active = selected == self->index;

	update_position(self, selected);

	int xyOffset = 0;

	int app_width = ICON_WIDTH;
	if (active)
	{
		// make icon bigger if active
		app_width *= ICON_ACTIVE_SCALE;

		// offset the position a bit so that it grows from the center
		xyOffset = -1*((app_width - ICON_WIDTH)/2);
	}

	SDL_Rect icon_rect = {.x = self->x + xyOffset, .y = 410 + xyOffset, .w = app_width, .h = app_width};
	
	//Now render the texture target to our screen, but upside down
	SDL_RenderCopy(g->renderer, self->icon_g, NULL, &icon_rect);
}
