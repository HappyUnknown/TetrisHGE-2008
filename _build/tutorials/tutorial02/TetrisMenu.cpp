#include "TetrisMenu.h"

bool TetrisMenu::menu_setup(HGE*hge, bool animate, char*charlineWidth, char*charlineHeight,char*charlineHardness, TetrisAudio& player)
	{
		// Offload music, in case you are finishing
		player.stop_backmusic(hge);
		// Load sound and textures
		menuBackIMG.tex=hge->Texture_Load(GameConstants::get_background_path().c_str());
		menuCRSTex=hge->Texture_Load("cursor.png");
		menuSND=hge->Effect_Load("menu.wav");
		if(!menuBackIMG.tex || !menuCRSTex || !menuSND)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return false;
		}

		// Set up the quad we will use for background animation
		menuBackIMG.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			menuBackIMG.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			menuBackIMG.v[i].col=TetrominoColors::get_color_by_id(TetrominoColors::Black);
		}

		menuBackIMG.v[0].x=0; menuBackIMG.v[0].y=0; 
		menuBackIMG.v[1].x=800; menuBackIMG.v[1].y=0; 
		menuBackIMG.v[2].x=800; menuBackIMG.v[2].y=600; 
		menuBackIMG.v[3].x=0; menuBackIMG.v[3].y=600; 


		// Load the font, create the cursor sprite
		menuFNT=new hgeFont("font1.fnt");
		menuCursorSPR=new hgeSprite(menuCRSTex,0,0,32,32);

		// Create and initialize the GUI
		menuGUI=new hgeGUI();

		const int START_X = 400, START_Y = 200, STEP_Y = 40, PADDING = 150;
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::Play, menuFNT, menuSND, START_X, START_Y + STEP_Y*0, animate?0.0f:0, "Play"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::Resume, menuFNT, menuSND, START_X, START_Y + STEP_Y*1, animate?0.1f:0, "Resume"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::WidthLess, menuFNT, menuSND, START_X-PADDING, START_Y + STEP_Y*2, animate?0.2f:0, "-WIDTH"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::WidthLess, menuFNT, menuSND, START_X, START_Y + STEP_Y*2, animate?0.2f:0, charlineWidth));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::WidthMore, menuFNT, menuSND, START_X+PADDING, START_Y + STEP_Y*2, animate?0.2f:0, "+WIDTH"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HeightLess, menuFNT, menuSND, START_X-PADDING, START_Y + STEP_Y*3, animate?0.3f:0, "-HEIGTH"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HeightLess, menuFNT, menuSND, START_X, START_Y + STEP_Y*3, animate?0.3f:0, charlineHeight));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HeightMore, menuFNT, menuSND, START_X+PADDING, START_Y + STEP_Y*3, animate?0.3f:0, "+HEIGTH"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HardnessLess, menuFNT, menuSND, START_X-PADDING, START_Y + STEP_Y*4, animate?0.4f:0, "-HARDNESS"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HardnessLess, menuFNT, menuSND, START_X, START_Y + STEP_Y*4, animate?0.4f:0, charlineHardness));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::HardnessMore, menuFNT, menuSND, START_X+PADDING, START_Y + STEP_Y*4, animate?0.4f:0, "+HARDNESS"));
		menuGUI->AddCtrl(new hgeGUIMenuItem(MenuOptions::Exit, menuFNT, menuSND, START_X, START_Y + STEP_Y*5, animate?0.5f:0, "Exit"));

		menuGUI->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		menuGUI->SetCursor(menuCursorSPR);
		menuGUI->SetFocus(1);
		menuGUI->Enter();
		return true;
	}
	MenuOptions TetrisMenu::menu_process_selection(HGE*hge, float dt, char* charlineWidth, char* charlineHeight, char* charlineHardness)
	{
		int id;
		static int lastid=MenuOptions::Default;
		id=menuGUI->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case MenuOptions::Play:
				//enter_game(false);
				return MenuOptions::Play;
			case MenuOptions::Resume:
				//enter_game(true);
				return MenuOptions::Resume;
			case MenuOptions::WidthLess:
				//valueRead = read_correct_field_width();
				//if(valueRead > get_min_width())
				//{	
					//if(TetrisSettings::setting_exists("field_width"))
					//	TetrisSettings::edit_setting("field_width", StringExtensions::to_string(--valueRead));
					//else
					//	TetrisSettings::add_setting("field_width", StringExtensions::to_string(--valueRead));
					//this->menu_setup_loaded();//refreshes menu settings
					//TetrisSession::reset_session();
				//}
				return MenuOptions::WidthLess;
			case MenuOptions::WidthMore:
				//valueRead = read_correct_field_width();
				//if(valueRead < GameConstants::MAX_FIELD_WIDTH)
				//{
				//	if(TetrisSettings::setting_exists("field_width"))
				//		TetrisSettings::edit_setting("field_width", StringExtensions::to_string(++valueRead));
				//	else
				//		TetrisSettings::add_setting("field_width", StringExtensions::to_string(++valueRead));
				//	this->menu_setup_loaded();//refreshes menu settings
				//	TetrisSession::reset_session();
				//}
				//menu.menuGUI->SetFocus(1);
				//menu.menuGUI->Enter();
				return MenuOptions::WidthMore;
			case MenuOptions::HeightLess:
				//valueRead = read_correct_field_height();
				//if(valueRead > GameConstants::MIN_FIELD_HEIGHT)
				//{
				//	if(TetrisSettings::setting_exists("field_height"))
				//		TetrisSettings::edit_setting("field_height", StringExtensions::to_string(--valueRead));
				//	else
				//		TetrisSettings::add_setting("field_height", StringExtensions::to_string(--valueRead));
				//	this->menu_setup_loaded();//refreshes menu settings
				//	TetrisSession::reset_session();
				//}
				//menu.menuGUI->SetFocus(1);
				//menu.menuGUI->Enter();
				return MenuOptions::HeightLess;
			case MenuOptions::HeightMore:
				//valueRead = read_correct_field_height();
				//if(valueRead < GameConstants::MAX_FIELD_HEIGHT)
				//{
				//	if(TetrisSettings::setting_exists("field_height"))
				//		TetrisSettings::edit_setting("field_height", StringExtensions::to_string(++valueRead));
				//	else
				//		TetrisSettings::add_setting("field_height", StringExtensions::to_string(++valueRead));
				//	this->menu_setup_loaded();//refreshes menu settings
				//	TetrisSession::reset_session();
				//}
				//menu.menuGUI->SetFocus(1);
				//menu.menuGUI->Enter();
				return MenuOptions::HeightMore;
			case MenuOptions::HardnessLess:
				//valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
				//if(valueRead > Hardness::Easy)
				//{
				//	if(TetrisSettings::setting_exists("hardness_mode"))
				//		TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(--valueRead));
				//	else
				//		TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(--valueRead));
				//	this->menu_setup_loaded();//refreshes menu settings
				//	TetrisSession::reset_session();
				//}
				//menu.menuGUI->SetFocus(1);
				//menu.menuGUI->Enter();
				return MenuOptions::HardnessLess;
			case MenuOptions::HardnessMore:
				//valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
				//if(valueRead < Hardness::Hard)
				//{
				//	if(TetrisSettings::setting_exists("hardness_mode"))
				//		TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(++valueRead));
				//	else
				//		TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(++valueRead));
				//	this->menu_setup_loaded();//refreshes menu settings
				//	TetrisSession::reset_session();
				//}
				//menu.menuGUI->SetFocus(1);
				//menu.menuGUI->Enter();
				return MenuOptions::HardnessMore;
			case MenuOptions::Exit:
				return MenuOptions::Exit;
			}
		}
		else if(id) 
		{ 
			lastid=id; 
			menuGUI->Leave(); 
		}
		return MenuOptions::Default;
	}
	void TetrisMenu::menu_dispose(HGE*hge)
	{
		// Delete created objects and free loaded resources
		delete menuGUI;
		delete menuFNT;
		delete menuCursorSPR;
		hge->Effect_Free(menuSND);
		hge->Texture_Free(menuCRSTex);
		hge->Texture_Free(menuBackIMG.tex);
	}
