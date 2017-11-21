#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


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

void display_app(char* app_name)
{
	char* buffer = NULL;
	size_t size = 0;

	// directory constants
	const char* apps = "apps/";
	int APPS_LEN = strlen(apps);
	const char* info = "/info.json";
	int INFO_LEN = strlen(info);

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

			// update the display
			
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
	display_app("demo.app");

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
		printf("[FATAL] SDL initialization failed!");
		return;
	}

	// Create SDL window
	SDL_Window *win = SDL_CreateWindow("Switch-Inspired Launcher Template", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
	SDL_Surface *bmpSurf = IMG_Load("apps/demo.app/icon.png");
	printf("Image: %s\n", IMG_GetError());
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);

	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 128, 128);
	
	//Now render to the texture
	SDL_SetRenderTarget(renderer, texTarget);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);

	//Detach the texture
	SDL_SetRenderTarget(renderer, NULL);

	// Draw background color
	SDL_SetRenderDrawColor(renderer, 0x31, 0x39, 0x44, 255);

	TTF_Init();

	// Draw some text
	TTF_Font* sans = TTF_OpenFont("res/overpass.otf", 40);
	SDL_Color white = {0xff, 0xff, 0xff};
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, "Homebrew Application", white);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	int w, h;
	SDL_QueryTexture(message, NULL, NULL, &w, &h);
	SDL_Rect message_rect = {.x = 0, .y = 0, .w = w, .h = h}; //create a rect
	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, message, NULL, &message_rect);

	SDL_Rect icon_rect = {.x = 200, .y = 200, .w = 128, .h = 128};

	//Now render the texture target to our screen, but upside down
	SDL_RenderCopy(renderer, texTarget, NULL, &icon_rect);
	SDL_RenderPresent(renderer);
}
