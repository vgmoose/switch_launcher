#include "tile.h"
#include "menu.h"
#include "graphics.h"

void update_position(struct graphics* g, struct tile* self)
{
	// update the y-coordinate of this icon according to the menu
	// current frame
	self->y = 50 + self->index*ICON_WIDTH + self->index*SPACE_BETWEEN_ICONS;
}
