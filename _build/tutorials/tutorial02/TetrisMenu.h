#include "TetrisAudio.h"

struct TetrisMenu
{
	HEFFECT	menuSND;
	HTEXTURE menuCRSTex;
	hgeQuad	menuBackIMG;
	hgeGUI *menuGUI;
	hgeFont	*menuFNT;
	hgeSprite *menuCursorSPR;
	bool menu_setup(HGE*, bool, char*, char*,char*, TetrisAudio&);
	MenuOptions menu_process_selection(HGE*, float, char*, char*, char*);
	void TetrisMenu::menu_dispose(HGE*);
};