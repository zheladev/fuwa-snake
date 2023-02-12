#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "types.h"
#include "Print.h"
#include <rand.h>

const UINT8 anim_walk_d[] = { 2, 1, 2 };
const UINT8 anim_walk_l[] = { 2, 3, 4 };
const UINT8 anim_walk_r[] = { 2, 5, 6 };
const UINT8 anim_walk_u[] = { 2, 7, 8 };


UINT16 seed;
UINT8 score;
UINT8 movement_delay;
UINT8 target_x;
UINT8 target_y;
UINT8 map_height = 128;
UINT8 map_width = 152;
UINT8 tile_size = 16;
UINT8 tile_half = 8;

UINT8 new_spawn_x;
UINT8 new_spawn_y;

UBYTE sprite_direction = 0x08U;
UBYTE user_input;
UBYTE queued_input = 0x08U;

void START() {
	score = 0;

	seed = DIV_REG;
	seed |= (UINT16)DIV_REG << 8;
	initrand(seed);
	getNextTargetPosition();
}
void UPDATE() {
	user_input = joypad();

	// if user input is opposite of sprite_direction, don't queue
	if (user_input != 0) {
		if (!(sprite_direction & J_UP && user_input & J_DOWN
			|| sprite_direction & J_DOWN && user_input & J_UP
			|| sprite_direction & J_LEFT && user_input & J_RIGHT
			|| sprite_direction & J_RIGHT && user_input & J_LEFT))
		{
			queued_input = user_input;
		}
	}

	// update target position, change direction
	if (target_x == THIS->x && target_y == THIS->y) {
		sprite_direction = queued_input;
		getNextTargetPosition();
	}

	handleMovement();
	handleCollision();
	checkGameOver();
}

void DESTROY() {
}

void checkGameOver() {
	if ((target_x <= 0 || target_y <= 0 ||
		target_x >= map_width - tile_half || target_y == map_height - tile_half)) {
		SetState(StateIntro);
	}
}

void getNextTargetPosition() {
	switch (sprite_direction) {
	case J_UP: // y-1
		target_x = THIS->x;
		target_y = THIS->y - 8;
		break;
	case J_DOWN: // y+1
		target_x = THIS->x;
		target_y = THIS->y + 8;
		break;
	case J_LEFT: // x-1
		target_x = THIS->x - 8;
		target_y = THIS->y;
		break;
	case J_RIGHT: // x+1
		target_x = THIS->x + 8;
		target_y = THIS->y;
		break;
	}
}

void handleCollision() {
	UINT8 i;
	Sprite* spr;
	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpriteTab) {
			if (CheckCollision(THIS, spr)) {
				score++;
				SpriteManagerRemove(i);
				//312 = map width, 136 = map height
				// clamp within map range
				// TODO: fix rand
				new_spawn_x = (UINT8)rand() % (UINT8)(map_width - tile_size);
				new_spawn_y = (UINT8)rand() % (UINT8)(map_height - tile_size);

				// center and prevent spawning in walls
				new_spawn_x = (new_spawn_x + tile_size) - (new_spawn_x % tile_size);
				new_spawn_y = (new_spawn_y + tile_size) - (new_spawn_y % tile_size);

				SpriteManagerAdd(SpriteTab, new_spawn_x, new_spawn_y);
			}
		}
	}
}

void handleMovement() {
	switch (sprite_direction) {
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
}