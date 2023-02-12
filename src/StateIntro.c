#include "Banks/SetAutoBank.h"

#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Print.h"

IMPORT_TILES(font);
IMPORT_MAP(title8);

void START() {
	INIT_BKG(title8);

	INIT_FONT(font, PRINT_BKG);
	PRINT(0, 13, "PRESS START");
	PRINT(1, 16, "TEST TEXT TEXT");
	PRINT(5, 17, "THIS ONE OVERFLOWS");
}

void UPDATE() {
	if (KEY_TICKED(J_START)) {
		SetState(StateGame);
	}
}