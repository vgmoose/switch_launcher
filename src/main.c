#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <unistd.h>
#include <signal.h>

#include "menu.h"
#include "graphics.h"

void intHandler(int dummy)
{
	// quit the program
	exit(0);
}

int main(int argc, char **argv)
{
	// setup main window
	struct graphics g;
	graphics_init(&g);

	// init main menu
	struct menu main_menu;
	menu_init(&main_menu);

	// populate list of all apps (along bottom)
	list_apps(&main_menu, &g);

	// display info about the selected app
	display_app(&main_menu);

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
