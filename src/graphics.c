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

	//Detach the texture
	SDL_SetRenderTarget(self->renderer, NULL);

	// Draw background color
	SDL_SetRenderDrawColor(self->renderer, 0x31, 0x39, 0x44, 255);

	// commit the changes
	repaint(self);

	TTF_Init();
	self->font = TTF_OpenFont("res/overpass.otf", 40);

//	
//	SDL_RenderClear(renderer);
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

void drawText(struct graphics* self, int x, int y, char* text)
{
	// Draw some text
	SDL_Color white = {0xff, 0xff, 0xff};
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(self->font, text, white);
	SDL_Texture* message = SDL_CreateTextureFromSurface(self->renderer, surfaceMessage);
	int w, h;
	SDL_QueryTexture(message, NULL, NULL, &w, &h);
	SDL_Rect message_rect = {.x = x, .y = y, .w = w, .h = h}; //create a rect

	SDL_RenderCopy(self->renderer, message, NULL, &message_rect);

	SDL_FreeSurface(surfaceMessage);
	//SDL_FreeTexture(message);


}
