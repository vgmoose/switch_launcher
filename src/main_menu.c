#include "main_menu.h"

void main_menu_init(struct main_menu* self)
{
	// set all to NULL to free later
	self->name = self->description = self->author = NULL;
}

void display_app(struct main_menu* self, char* app_path, int selected)
{
	char* buffer = NULL;
	size_t size = 0;

	// directory constants
//	const char* apps = "apps/";
//	int APPS_LEN = strlen(apps);
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

		// references to corresponding main_menu components (values and labels) we're interested in
		char** target_vals[3] = {&self->name, &self->description, &self->author};
		SDL_Texture** target_labels[3] = {&self->name_g, &self->desc_g, &self->auth_g};

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
				strncpy(target, buffer + tokens[x+1].start, targ_len);
				target[targ_len] = '\0';

				// update the display
				//update_label(&target_labels[y], target);
			}
		}


		// free current key, and continue onto next key (skip value)
		free(cur_key);
		x += token.size;
	}

	free(path);
	free(buffer);

}
