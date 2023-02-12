#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "types.h"
#include <rand.h>

const UINT8 anim_idle_d[] = {1, 0};
const UINT8 anim_idle_l[] = { 1, 9 };
const UINT8 anim_idle_r[] = { 1, 10 };
const UINT8 anim_idle_u[] = { 1, 11 };
const UINT8 anim_walk_d[] = { 2, 1, 2 };
const UINT8 anim_walk_l[] = { 2, 3, 4 };
const UINT8 anim_walk_r[] = { 2, 5, 6 };
const UINT8 anim_walk_u[] = { 2, 7, 8 };

UINT16 seed;
UINT8 score;
UINT8 new_spawn_x;
UINT8 new_spawn_y;
UBYTE last_input = 0x08U;
UBYTE user_input;

void START() {
	score = 0;
	seed = DIV_REG;
	seed |= (UINT16)DIV_REG << 8;
	initrand(seed);
}

void UPDATE() {
	UINT8 i;
	Sprite* spr;
	user_input = joypad();

	handleMovement();

	last_input = user_input;

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpriteTab) {
			if (CheckCollision(THIS, spr)) {
				score++;
				SpriteManagerRemove(i);
				//312 = map width, 136 = map height
				// clamp within map range
				new_spawn_x = (UINT8)rand() % (UINT8)(304 - 16);
				new_spawn_y = (UINT8)rand() % (UINT8)(128 - 16);
				
				// center and prevent spawning in walls
				new_spawn_x = (new_spawn_x + 8) - (new_spawn_x % 8);
				new_spawn_y = (new_spawn_y + 8) - (new_spawn_y % 8);

				SpriteManagerAdd(SpriteTab, new_spawn_x, new_spawn_y);
			}
		}
	}
}

void DESTROY() {
}

void handleMovement()
{
	if (KEY_PRESSED(J_UP)) {
		TranslateSprite(THIS, 0, -1);
		SetSpriteAnim(THIS, anim_walk_u, 15);
	} else if (KEY_PRESSED(J_DOWN)) {
		TranslateSprite(THIS, 0, 1);
		SetSpriteAnim(THIS, anim_walk_d, 15);
	} else if (KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -1, 0);
		SetSpriteAnim(THIS, anim_walk_l, 15);
	} else if (KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, 1, 0);
		SetSpriteAnim(THIS, anim_walk_r, 15);
	} else if (keys == 0) {
		switch (last_input)
		{
		case J_UP:
			SetSpriteAnim(THIS, anim_idle_u, 15);
			break;
		case J_DOWN:
			SetSpriteAnim(THIS, anim_idle_d, 15);
			break;
		case J_LEFT:
			SetSpriteAnim(THIS, anim_idle_l, 15);
			break;
		case J_RIGHT:
			SetSpriteAnim(THIS, anim_idle_r, 15);
			break;
		}
	}
}