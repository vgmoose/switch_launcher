#include "graphics.h"

#define WIDTH 1280
#define HEIGHT 720

void graphics_init(struct graphics* self)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("[FATAL] SDL initialization failed!");
		return;
	}

	// Create SDL window
	self->window = SDL_CreateWindow("Switch-Inspired Launcher Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
//	SDL_Surface *bmpSurf = IMG_Load("apps/demo.app/icon.png");
//	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
//	SDL_FreeSurface(bmpSurf);
//
//	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 128, 128);
//	
//	//Now render to the texture
//	SDL_SetRenderTarget(renderer, texTarget);
//	SDL_RenderClear(renderer);
//	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);

	//Detach the texture
	SDL_SetRenderTarget(self->renderer, NULL);

	// Draw background color
	SDL_SetRenderDrawColor(self->renderer, 0x31, 0x39, 0x44, 255);

	// commit the changes
	repaint(self);

	TTF_Init();

//	// Draw some text
//	TTF_Font* sans = TTF_OpenFont("res/overpass.otf", 40);
//	SDL_Color white = {0xff, 0xff, 0xff};
//	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, "Homebrew Application", white);
//	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//	int w, h;
//	SDL_QueryTexture(message, NULL, NULL, &w, &h);
//	SDL_Rect message_rect = {.x = 0, .y = 0, .w = w, .h = h}; //create a rect
//	
//	SDL_RenderClear(renderer);
//	SDL_RenderCopy(renderer, message, NULL, &message_rect);
//
//	SDL_Rect icon_rect = {.x = 200, .y = 200, .w = 128, .h = 128};
//
//	//Now render the texture target to our screen, but upside down
//	SDL_RenderCopy(renderer, texTarget, NULL, &icon_rect);
}

void clear(struct graphics* self)
{
	SDL_RenderClear(self->renderer);
}

void repaint(struct graphics* self)
{
	SDL_RenderPresent(self->renderer);
}
