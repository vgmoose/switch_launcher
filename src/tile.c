#include "tile.h"
#include "menu.h"
#include "graphics.h"
#include "utils.h"
#include <SDL2/SDL_image.h>

void tile_init(struct tile* self, struct graphics* g, char* path, int index)
{
	// set path for this app
	self->path = malloc(APP_PATH_LEN + strlen(path));
	strcpy(self->path, APP_PATH);
	strcat(self->path, path);

	self->index = index;

	// load icon into memory
	SDL_Surface *bmpSurf = IMG_Load("apps/demo.app/icon.png");
	self->icon_g = SDL_CreateTextureFromSurface(g->renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);
}

void update_position(struct tile* self)
{
	// update the y-coordinate of this icon according to the menu
	// current frame
	self->y = 50 + self->index*ICON_WIDTH + self->index*SPACE_BETWEEN_ICONS;
}

int is_valid_app(struct dirent* entry)
{
	// valid app if it's a directory and ends with '.app'
	// TODO: add more validation criteria here
	return (entry->d_type == DT_DIR && ends_with(entry->d_name, APP_SUFFIX));
}
