#include <dirent.h>
#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "tile.h"

void menu_init(struct menu* self)
{
	// set all to NULL to free later
	self->name = self->description = self->author = NULL;
	self->apps = NULL;

	// no selected app by default
	self->apps_count = 0;
	self->selected = -1;
}

void list_apps(struct menu* self, struct graphics* g)
{
	DIR *dir = opendir(APP_PATH);

	if (!dir) // directory doesn't exist TODO: notify user
		return;
	
	struct dirent *entry = readdir(dir);

	// find valid apps to count them up
	while (entry != NULL)
	{
		if (is_valid_app(entry))
			self->apps_count ++;

		entry = readdir(dir);
	}

	// rewind directory, then go through it again to create the app tiles
	rewinddir(dir);
	entry = readdir(dir);

	// allocate memory for list of apps array
	self->apps = malloc(sizeof(struct tile)*self->apps_count);

	int count = 0;
	while (entry != NULL)
	{
		if (is_valid_app(entry))
		{
			// create an app tile
			tile_init(&self->apps[count], g, entry->d_name, count);
			count ++;
		}

		entry = readdir(dir);
	}

	// if there's at least one app found, set the selected to the first app
	if (self->apps_count > 0)
		self->selected = 0;
	
	closedir(dir);
}

void display_app(struct menu* self)
{
	char* buffer = NULL;
	size_t size = 0;

	if (self->selected < 0 || self->apps_count <= 0) // no valid apps, nothing to render TODO: display a message
		return;

	char* app_path = self->apps[self->selected].path;

	// directory constants
	const char* info = "/info.json";
	int INFO_LEN = strlen(info);

	// construct path
	char* path = malloc(strlen(app_path) + INFO_LEN + 1);
	strcpy(path, app_path);
	strcat(path, info);

	// load file on disk into memory
	FILE* fp = fopen(path, "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buffer = malloc((size+1)*sizeof(*buffer));
	fread(buffer, size, 1, fp);
	buffer[size] = '\0';

	// parse author name using jsmn
	jsmn_parser p;
	jsmntok_t tokens[100];
	jsmn_init(&p);

	int val = jsmn_parse(&p, buffer, strlen(buffer), tokens, 100);

	for (int x=0; x<val; x++)
	{
		// read one token
		jsmntok_t token = tokens[x];

		// if it's not a string, keep going
		if (token.type != JSMN_STRING)
			continue;

		// read a string out
		int key_len = token.end - token.start;
		char* cur_key = malloc(key_len + 1);
		strncpy(cur_key, buffer + token.start, key_len);
		cur_key[key_len] = '\0';

		// names of keys that we are interested in
		const char* target_keys[3] = {"name", "description", "author"};

		// references to corresponding menu components (values and labels) we're interested in
		char** target_vals[3] = {&self->name, &self->description, &self->author};

		for (int y=0; y<3; y++)
		{
			const char* targ_key = target_keys[y];
			char* target = *target_vals[y];

			// if it's the target key string
			if (strcmp(cur_key, targ_key) == 0)
			{
				// free the old target (string) in the self's struct
				free(target);

				// grab the value of this key and break
				int targ_len = tokens[x+1].end - tokens[x+1].start;
				target = malloc(targ_len + 1);
				*target_vals[y] = target;
				strncpy(target, buffer + tokens[x+1].start, targ_len);
				target[targ_len] = '\0';
			}
		}

		// free current key, and continue onto next key (skip value)
		free(cur_key);
		x += token.size;
	}

	free(path);
	free(buffer);

}

void render_menu(struct menu* self, struct graphics* g)
{
	// clear the rendering canvas
	clear(g);

	int xIn = 200;
	int yIn = 130;

	// draw the text of the selected app
	drawText_adv(g, xIn, yIn, FONT_LARGE, self->name);
	drawText_adv(g, xIn, yIn + 70, FONT_WRAP, self->description);

	const char* author = "Author: ";
	char* authorString = malloc(strlen(self->author) + strlen(author) + 1);
	strcpy(authorString, author);
	strcat(authorString, self->author);
	drawText_adv(g, xIn, yIn + 220, FONT_SMALL, authorString);
	free(authorString);

	SDL_Rect icon_rect = {.x = 800, .y = 100, .w = 256, .h = 256};
	SDL_RenderCopy(g->renderer, self->apps[self->selected].icon_g, NULL, &icon_rect);
	
	// render all app tile icons
	for (int x=0; x<self->apps_count; x++)
	{
		render_tile(&self->apps[x], g, self->selected);
	}
	
	// commit the changes to the screen
	repaint(g);
}

void process_key(struct menu* self, int keycode)
{
	int selected = self->selected - (keycode == SDLK_LEFT) + (keycode == SDLK_RIGHT);

	// updated selected index if it's within valid bounds
	if (selected >= 0 && selected < self->apps_count)
		self->selected = selected;

	// update display
	display_app(self);
}
