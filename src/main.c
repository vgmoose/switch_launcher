#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "../jsmn/jsmn.h"


#include <unistd.h>
#include <signal.h>

const int WIDTH = 1280;
const int HEIGHT = 720;

//SDL_Texture* texTarget = 

void intHandler(int dummy)
{
//	SDL_DestroyTexture(texTarget);
//	SDL_DestroyTexture(bmpTex);
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(win);
//	SDL_Quit();

	// quit the program
	exit(0);
}

void json_read(char* app_name)
{
	char* buffer = NULL;
	size_t size = 0;

	// directory constants
	char* apps = "apps/";
	int APPS_LEN = 5;
	char* info = "/info.json";
	int INFO_LEN = 10;

	// construct path
	char* path = malloc(APPS_LEN + strlen(app_name) + INFO_LEN + 1);
	strcpy(path, apps);
	strcat(path, app_name);
	strcat(path, info);

	// load file on disk into memory
	FILE* fp = fopen(path, "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buffer = malloc((size+1)*sizeof(*buffer));
	fread(buffer, size, 1, fp);
	buffer[size] = '\0';

	// print contents
	printf("%s\n", buffer);

	// parse author name using jsmn
	jsmn_parser p;
	jsmntok_t tokens[100];
	jsmn_init(&p);

	char* author = NULL;

	int val = jsmn_parse(&p, buffer, strlen(buffer), tokens, 100);
	printf("%d tokens found\n", val);

	for (int x=0; x<val; x++)
	{
		// read one token
		jsmntok_t token = tokens[x];

		// if it's not a string, keep going
		if (token.type != JSMN_STRING)
			continue;

		// read a string out
		int key_len = token.end - token.start;
		char* key = malloc(key_len + 1);
		strncpy(key, buffer + token.start, key_len);
		key[key_len] = '\0';

		printf("Checking %s...\n", key);

		// if it's the author string
		if (strcmp(key, "author") == 0)
		{
			printf("Found author key!\n");
			free(key);

			// grab the value of this key and break
			int author_len = tokens[x+1].end - tokens[x+1].start;
			author = malloc(author_len + 1);
			strncpy(author, buffer + tokens[x+1].start, author_len);
			author[author_len] = '\0';
			break;
		}

		// it wasn't the author, check the next key (skip this value)
		free(key);
		x += token.size;
	}

	if (author != NULL)
		printf("Author: %s\n", author);
	else
		printf("No author found\n");

	free(author);
}


int main(int argc, char **argv)
{
	json_read("space.app");

	// setup main window
	init();

	// attach interrupt handler (ctrl+C)
	signal(SIGINT, intHandler);

	// don't exit immediately
	while (1) { sleep(1000000000); }
	return 0;
}

int WinMain(int argc, char* argv[])
{
	// for windows compatibility
	return main(argc, argv);
}

void init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Some problem happened");
		return;
	}

	SDL_Window *win = SDL_CreateWindow("Switch-Inspired Launcher Template", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
	SDL_Surface *bmpSurf = SDL_LoadBMP("res/image.bmp");
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);

	//Make a target texture to render too
	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	
	//Now render to the texture
	SDL_SetRenderTarget(renderer, texTarget);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);

	//Detach the texture
	SDL_SetRenderTarget(renderer, NULL);

	//Now render the texture target to our screen, but upside down
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, 0);
	SDL_RenderPresent(renderer);
}
