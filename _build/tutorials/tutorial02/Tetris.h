#include "TetrisAudio.h"
struct TetrisMenu
{
	HEFFECT	menuSND;
	HTEXTURE menuCRSTex;
	hgeQuad	menuBackIMG;
	hgeGUI *menuGUI;
	hgeFont	*menuFNT;
	hgeSprite *menuCursorSPR;
	bool menu_setup(HGE*hge, bool animate, char*charlineWidth, char*charlineHeight,char*charlineHardness, TetrisAudio& player)
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
	void menu_dispose(HGE*hge)
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
struct Tetris
{	
	TetrisAudio player;
	#pragma region SCORE DISPLAY
	int score;
	hgeFont	*scorefont;
	void init_score_font();
	void print_message(std::string msg);
	void render_score();
	void render_lose();
	void dispose_score_font();
	#pragma endregion
	#pragma region MENU
		TetrisMenu menu;
		void enter_game(bool resume);
		MenuOptions menu_process_selection(HGE*hge, float dt);
		MenuOptions menu_frame_func(HGE*hge);
		//bool Tetris::menu_setup(HGE*hge, bool animate, char*charlineWidth, char*charlineHeight,char*charlineHardness);
		void enter_menu();
		//void menu_dispose(HGE*hge);
	#pragma endregion

	GameMode mode;
	int fieldWidth, fieldHeight;
	std::vector<TetrominoBase*> figures;
	std::vector<GameSquare>bricks;
	HGE *hge;
	std::string brickPath, squarePath;
	double loopTime;
	double loopMaxTime;
	double brickTexFraction;
	double brickTexStartX, brickTexStartY;
	double squareTexFraction;
	double squareTexStartX, squareTexStartY;
	int initI, initJ;
	Tetris();
	void menu_render_func(float animationSpeed = 1.0f);
	void animate_background(HGE*hge, float dt, float speedMultiplier = 1.0f);
	void render_animated_background(HGE* hge, float dt, float speedMultiplier);
	int get_min_width();
	void set_sessional_hardness(Hardness hardness);
	void current_left();
	void current_right();
	void current_up();
	void current_down(int step);
	void current_clockwise();
	void current_counterclockwise();
	int read_correct_field_width();
	int read_correct_field_height();
	int squares_on_width();
	int squares_on_height();
	int free_framecells_x();
	int free_framecells_y();
	int area_cell_align_x();
	int area_cell_align_y();
	int area_align_x();
	int area_align_y();
	void reimagine_field();
	void imagine_wall();
	void render_inbox();
	void render_wall();
	void render_field();
	void in_game_render_func(float animationSpeed = 1.0f);
	bool in_game_frame_func();
	void limbo_render_func(float animationSpeed = 0.1f);
	bool limbo_frame_func();
	TetrominoBase* get_random_tetromino(int initI, int initJ);
	//returns curent, if figures are not empty, and last is not landed 
	TetrominoBase* current_tetromino();
	bool spawn(hgeU32 col);
	void dispose_textures();
	void place_all();
	bool all_landed();
	bool current_collides_downside(int step);
	bool current_collides_upside();
	bool current_collides_leftside();
	bool current_collides_rightside();
	bool current_collides_clockwise();
	bool current_collides_counterclockwise();
	bool all_in_box(std::vector<GameSquare>squares);
	void popup(std::string message);
	void popup_error();
	GameSquare* init_brick(int i, int j, hgeU32 col);
	void init_wall(hgeU32 col);
	void title_squares();//when figures are 10, and above - the field becomes all overloaded
	int clear_row(int iVal);
	int count_row_squares(int iVal);
	bool count_fulfills_score(int count);
	bool row_is_full(int iVal);
	void fall_above_row(int iVal);
	void clear_row_full(int iVal);
	void clear_all_rows_full();
	void timer_tick();
	void reset_timer();
	int projection_delta(Position currentPos);
	int current_min_projection_delta();
	bool bell_rings_on_tick();
};
