#include "Banks/SetAutoBank.h"

#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Print.h"

IMPORT_MAP(title8);

void START() {
	INIT_BKG(title8);
}

void UPDATE() {
	if (KEY_TICKED(J_START)) {
		SetState(StateGame);
	}
}