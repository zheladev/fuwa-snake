#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "types.h"

typedef struct {
	INT8 vy;
} CUSTOM_TAB_DATA;

void START() {
	CUSTOM_TAB_DATA* data = (CUSTOM_TAB_DATA*)THIS->custom_data;
	data->vy = 1;
}

void UPDATE() {
	CUSTOM_TAB_DATA* data = (CUSTOM_TAB_DATA*)THIS->custom_data;
}

void DESTROY() {
}