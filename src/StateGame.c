#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "../include//SpritePlayer.h"

extern UINT8 score;

UINT8 collision_tiles[] = { 1, 0 };

IMPORT_MAP(map);
IMPORT_TILES(font);

void START() {
	INIT_CONSOLE(font, 1);
	scroll_target = SpriteManagerAdd(SpritePlayer, 64, 64);
	SpriteManagerAdd(SpriteTab, 16, 16);
	InitScroll(BANK(map), &map, collision_tiles, 0);

}

void UPDATE() {
	UINT8 i;
	Sprite* spr;

	DPRINT_POS(0, 0);
	DPrintf("score:%d  ", score);
}
