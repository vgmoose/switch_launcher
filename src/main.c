#include <stdio.h>
#include <SDL2/SDL.h>

#include <unistd.h>
#include <signal.h>

// based on https://gist.github.com/Twinklebear/8265888

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

void intHandler(int dummy)
{
	// quit the program
	exit(0);
}

int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Some problem happened");
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Switch-Inspired Launcher Template", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
	SDL_Surface *bmpSurf = SDL_LoadBMP("res/image.bmp");
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);

	//Make a target texture to render too
	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);
	
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

	// attach interrupt handler
	signal(SIGINT, intHandler);

	while (1) { sleep(1000000000); }

//	SDL_Delay(1000);
//	SDL_DestroyTexture(texTarget);
//	SDL_DestroyTexture(bmpTex);
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(win);
//	SDL_Quit();
	return 0;
}
