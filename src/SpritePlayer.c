#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "types.h"
#include <rand.h>

const UINT8 anim_walk_u[] = { 2, 0, 1 };
const UINT8 anim_walk_r[] = { 2, 2, 3 };
const UINT8 anim_walk_d[] = { 2, 4, 5 };
const UINT8 anim_walk_l[] = { 2, 6, 7 };

UINT16 seed;
UINT8 score;

UINT8 new_spawn_x;
UINT8 new_spawn_y;

UBYTE sprite_direction = 0x08U;
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

	if (user_input != 0)
	{
		sprite_direction = user_input;
	}

	switch (sprite_direction)
	{
	case J_UP:
		TranslateSprite(THIS, 0, -1);
		SetSpriteAnim(THIS, anim_walk_u, 15);
		break;
	case J_DOWN:
		TranslateSprite(THIS, 0, 1);
		SetSpriteAnim(THIS, anim_walk_d, 15);
		break;
	case J_LEFT:
		TranslateSprite(THIS, -1, 0);
		SetSpriteAnim(THIS, anim_walk_l, 15);
		break;
	case J_RIGHT:
		TranslateSprite(THIS, 1, 0);
		SetSpriteAnim(THIS, anim_walk_r, 15);
		break;
	}


	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpriteTab) {
			if (CheckCollision(THIS, spr)) {
				score++;
				SpriteManagerRemove(i);
				//312 = map width, 136 = map height
				// clamp within map range
				// TODO: fix rand
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