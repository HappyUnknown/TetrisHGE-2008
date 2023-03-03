#include "TetrisAudio.h"

struct TetrisGUI
{	
	#pragma region SCORE DISPLAY
	int score;
	hgeFont	*scorefont;
	//void init_score_font();
	//void print_message(std::string msg);
	//void render_score();
	//void render_lose();
	//void dispose_score_font();
	#pragma endregion
	#pragma region MENU
		HEFFECT	menuSND;
		HTEXTURE menuCRSTex;
		hgeQuad	menuBackIMG;
		hgeGUI *menuGUI;
		hgeFont	*menuFNT;
		hgeSprite *menuCursorSPR;

		//void animate_background(HGE*hge, float dt, float speedMultiplier = 1.0f);
		//void enter_game(bool resume);
		//int read_correct_field_width();
		//int read_correct_field_height();
		//bool menu_process_selection(HGE*hge, float dt);
		//bool menu_frame_func(HGE*hge);
		//bool menu_setup(HGE*hge, bool animate = true);
		//void enter_menu();
		//void menu_render_func(float animationSpeed = 1.0f);
		//void render_animated_background(HGE* hge, float dt, float speedMultiplier);
		//void menu_dispose(HGE*hge);
	#pragma endregion

	void TetrisGUI::init_score_font()
	{
		scorefont=new hgeFont("font1.fnt");
	}
	void TetrisGUI::print_message(std::string msg)
	{
		scorefont->printf(7, 7, HGETEXT_LEFT, msg.c_str());
	}
	void TetrisGUI::render_score()
	{
		print_message("SCORE: "+StringExtensions::to_string(score));
	}
	void TetrisGUI::render_lose()
	{
		print_message("YOU LOSE WITH SCORE OF "+StringExtensions::to_string(score)+"\nPress any key to continue...");
	}
	void TetrisGUI::dispose_score_font()
	{
		delete scorefont;
	}
		void TetrisGUI::animate_background(HGE*hge, float dt, float speedMultiplier)
		{
			static float t=0.0f;
			float tx,ty;
			t += dt * speedMultiplier;
			tx = 50*cosf(t/60);
			ty = 50*sinf(t/60);
			menuBackIMG.v[0].tx = tx;        
			menuBackIMG.v[0].ty = ty;
			menuBackIMG.v[1].tx = tx+GameConstants::FRAMEX/64; 
			menuBackIMG.v[1].ty = ty;
			menuBackIMG.v[2].tx = tx+GameConstants::FRAMEX/64; 
			menuBackIMG.v[2].ty = ty+GameConstants::FRAMEY/64;
			menuBackIMG.v[3].tx = tx;
			menuBackIMG.v[3].ty = ty+GameConstants::FRAMEY/64;
		}
		void TetrisGUI::enter_game(HGE*hge, TetrisPlayer player, bool resume)
		{
			player.setup_boom(hge);
			player.play_random_music(hge);

			fieldHeight = read_correct_field_height();
			fieldWidth = read_correct_field_width();
			loopTime = TetrisMath::math_fall_period((Hardness)StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode")));
			initJ = StringExtensions::int_parse(TetrisSettings::read_setting_value("init_j"));
			initI = StringExtensions::int_parse(TetrisSettings::read_setting_value("init_i"));
			brickPath = TetrisSettings::read_setting_value("brick_path");
			squarePath = TetrisSettings::read_setting_value("square_path");
			brickTexFraction = StringExtensions::double_parse(TetrisSettings::read_setting_value("brick_tex_fraction"));
			brickTexStartX = StringExtensions::double_parse(TetrisSettings::read_setting_value("brick_tex_start_x"));
			brickTexStartY = StringExtensions::double_parse(TetrisSettings::read_setting_value("brick_tex_start_y"));
			squareTexFraction = StringExtensions::double_parse(TetrisSettings::read_setting_value("square_tex_fraction"));
			squareTexStartX = StringExtensions::double_parse(TetrisSettings::read_setting_value("square_tex_start_x"));
			squareTexStartY = StringExtensions::double_parse(TetrisSettings::read_setting_value("square_tex_start_y"));
			brickPath = brickPath!="NO_VALUE"?brickPath:GameConstants::get_texture_path();
			squarePath = squarePath!="NO_VALUE"?squarePath:GameConstants::get_texture_path();

			init_wall(TetrominoColors::get_color_by_id(TetrominoColors::Colors::Yellow));
			imagine_wall();
			player.play_backmusic(hge);
			
			figures.clear();
			if(resume)
				TetrisSession::extract_figures(hge, figures);
			
			mode = GameMode::Game;
		}
		int TetrisGUI::read_correct_field_width()
		{
			const int WIDEST_GAP = 5;
			int width = StringExtensions::int_parse(TetrisSettings::read_setting_value("field_width"));
			int widthRequired = StringExtensions::int_parse(TetrisSettings::read_setting_value("init_j")) + WIDEST_GAP;
			if(width < widthRequired)
			{
				TetrisSettings::edit_setting("field_width", StringExtensions::to_string(widthRequired));
				width = StringExtensions::int_parse(TetrisSettings::read_setting_value("field_width"));
			}
			return width;
		}
		int TetrisGUI::read_correct_field_height()
		{
			const int LONGEST_GAP = 2;
			int height = StringExtensions::int_parse(TetrisSettings::read_setting_value("field_height"));
			int heightRequired = StringExtensions::int_parse(TetrisSettings::read_setting_value("init_i")) + LONGEST_GAP;
			if(height < heightRequired)
			{
				TetrisSettings::edit_setting("field_height", StringExtensions::to_string(heightRequired));
				height = StringExtensions::int_parse(TetrisSettings::read_setting_value("field_height"));
			}
			return height;

		}
		int TetrisGUI::menu_process_selection(HGE*hge, float dt)
		{
			int valueRead;

			int id;
			static int lastid=0;
			id=menuGUI->Update(dt);
			if(id == -1)
			{
				switch(lastid)
				{
				case MenuOptions::Play:
					enter_game(false);
					break;
				case MenuOptions::Resume:
					enter_game(true);
					break;
				case MenuOptions::WidthLess:
					 valueRead = read_correct_field_width();
					 if(valueRead > get_min_width())
					 {	
						if(TetrisSettings::setting_exists("field_width"))
							TetrisSettings::edit_setting("field_width", StringExtensions::to_string(--valueRead));
						else
							TetrisSettings::add_setting("field_width", StringExtensions::to_string(--valueRead));
						menu_setup(hge, false);//refreshes menu settings
						TetrisSession::reset_session();
					 }
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::WidthMore:
					valueRead = read_correct_field_width();
					if(valueRead < GameConstants::MAX_FIELD_WIDTH)
					{
						if(TetrisSettings::setting_exists("field_width"))
							TetrisSettings::edit_setting("field_width", StringExtensions::to_string(++valueRead));
						else
							TetrisSettings::add_setting("field_width", StringExtensions::to_string(++valueRead));
						menu_setup(hge, false);
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::HeightLess:
					valueRead = read_correct_field_height();
					if(valueRead > GameConstants::MIN_FIELD_HEIGHT)
					{
						if(TetrisSettings::setting_exists("field_height"))
							TetrisSettings::edit_setting("field_height", StringExtensions::to_string(--valueRead));
						else
							TetrisSettings::add_setting("field_height", StringExtensions::to_string(--valueRead));
						menu_setup(hge, false);
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::HeightMore:
					valueRead = read_correct_field_height();
					if(valueRead < GameConstants::MAX_FIELD_HEIGHT)
					{
						if(TetrisSettings::setting_exists("field_height"))
							TetrisSettings::edit_setting("field_height", StringExtensions::to_string(++valueRead));
						else
							TetrisSettings::add_setting("field_height", StringExtensions::to_string(++valueRead));
						menu_setup(hge, false);
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::HardnessLess:
					valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
					if(valueRead > Hardness::Easy)
					{
						if(TetrisSettings::setting_exists("hardness_mode"))
							TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(--valueRead));
						else
							TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(--valueRead));
						menu_setup(hge, false);
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::HardnessMore:
					valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
					if(valueRead < Hardness::Hard)
					{
						if(TetrisSettings::setting_exists("hardness_mode"))
							TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(++valueRead));
						else
							TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(++valueRead));
						menu_setup(hge, false);
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					break;
				case MenuOptions::Exit:
					return true;
				}
			}
			else if(id) 
			{ 
				lastid=id; 
				menuGUI->Leave(); 
			}
			return false;
		}
		bool TetrisGUI::menu_frame_func(HGE*hge)
		{
			float dt=hge->Timer_GetDelta();
			if(menu_process_selection(hge,dt) || hge->Input_KeyDown(HGEK_ESCAPE)) return true;

			return false;
		}
		
		bool TetrisGUI::menu_setup(HGE*hge, bool animate)
		{
			// Load sound and textures
			menuBackIMG.tex=hge->Texture_Load(GameConstants::get_background_path().c_str());
			menuCRSTex=hge->Texture_Load("cursor.png");
			menuSND=hge->Effect_Load("menu.wav");
			if(!menuBackIMG.tex || !menuCRSTex || !menuSND)
			{
				// If one of the data files is not found, display
				// an error message and shutdown.
				MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
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

			char* charlineWidth = StringExtensions::to_char_array(StringExtensions::to_string(read_correct_field_width()));
			char* charlineHeight = StringExtensions::to_char_array(StringExtensions::to_string(read_correct_field_height()));
			char* charlineHardness = StringExtensions::to_char_array(TetrisSettings::read_setting_value("hardness_mode"));

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
		void TetrisGUI::enter_menu(HGE*hge)
		{
			menu_setup(hge);
			mode = GameMode::Menu;
		}
		void TetrisGUI::menu_render_func(float animationSpeed)
		{
			float dt = hge->Timer_GetDelta();
			render_animated_background(hge, dt, animationSpeed); //multiplier just does not care
			menuGUI->Render();
			menuFNT->SetColor(TetrominoColors::White);
		}
		void TetrisGUI::render_animated_background(HGE* hge, float dt, float speedMultiplier)
		{
			hge->Gfx_RenderQuad(&menuBackIMG);
			animate_background(hge,dt,speedMultiplier);
		}
		void TetrisGUI::menu_dispose(HGE*hge)
		{
			// Delete created objects and free loaded resources
			delete menuGUI;
			delete menuFNT;
			delete menuCursorSPR;
			hge->Effect_Free(menuSND);
			hge->Texture_Free(menuCRSTex);
			hge->Texture_Free(menuBackIMG.tex);
		}
};