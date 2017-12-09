#include "graphics.h"

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

	// commit the changes
	repaint(self);

	TTF_Init();
	char* font = "res/inter-ui.ttf";
	self->fonts[FONT_LARGE] = TTF_OpenFont("res/inter-ui-bold.ttf", 45);
	self->fonts[FONT_WRAP]  = TTF_OpenFont(font, 29);
	self->fonts[FONT_SMALL] = TTF_OpenFont(font, 17);
	
	if (self->fonts[FONT_LARGE] == NULL || self->fonts[FONT_SMALL] == NULL)
	{
		printf("[WARNING] Couldn't find res/overpass.otf or res/overpass-bold.otf! For now these files are required to display text.\n");
	}

	self->frame = 0;
}

void clear(struct graphics* self)
{
	SDL_RenderClear(self->renderer);
}

void repaint(struct graphics* self)
{
	// Draw background color
	SDL_SetRenderDrawColor(self->renderer, 0x31, 0x39, 0x44, 255);
	
	SDL_RenderPresent(self->renderer);
}

void drawText_adv(struct graphics* self, int x, int y, int size, char* text)
{
	// Draw some text
	SDL_Color white = {0xff, 0xff, 0xff};
	
	if (self->fonts[size] == NULL) 
		return;

	SDL_Surface* surfaceMessage;
	if (size == FONT_WRAP)
		surfaceMessage = TTF_RenderText_Blended_Wrapped(self->fonts[FONT_WRAP], text, white, 460);
	else
		surfaceMessage = TTF_RenderText_Blended(self->fonts[size], text, white);

	SDL_Texture* message = SDL_CreateTextureFromSurface(self->renderer, surfaceMessage);
	int w, h;
	SDL_QueryTexture(message, NULL, NULL, &w, &h);
	SDL_Rect message_rect = {.x = x, .y = y, .w = w, .h = h}; //create a rect

	SDL_RenderCopy(self->renderer, message, NULL, &message_rect);

	SDL_FreeSurface(surfaceMessage);

	// increment the current animation frame
	self->frame ++;
}

void drawText(struct graphics* self, int x, int y, char* text)
{
	drawText_adv(self, x, y, FONT_LARGE, text);
}
