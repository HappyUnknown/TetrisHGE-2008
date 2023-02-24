#include "MenuOptions.h"
struct Tetris
{	
	#pragma region SOUND
	HEFFECT boomEffect;
	void Tetris::setup_boom();
	void Tetris::play_place();
	void Tetris::play_pop();
	#pragma endregion
	#pragma region STREAMS
	HSTREAM backmusic;
	void setup_backmusic(std::string path);
	void play_backmusic();
	void stop_backmusic();
	std::string guarantee_get_playlist_path();
	std::vector<std::string> read_playlist();
	std::string playlist_get_random_path();
	void play_random_music();
	#pragma endregion
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
		HEFFECT	menuSND;
		HTEXTURE menuCRSTex;
		hgeQuad	menuBackIMG;
		hgeGUI *menuGUI;
		hgeFont	*menuFNT;
		hgeSprite *menuCursorSPR;

		void animate_background(HGE*hge, float dt, float speedMultiplier = 1.0f);
		void enter_game(bool resume);
		int read_correct_field_width();
		int read_correct_field_height();
		bool menu_process_selection(HGE*hge, float dt);
		bool menu_frame_func(HGE*hge);
		bool menu_setup(HGE*hge, bool animate = true);
		void enter_menu();
		void menu_render_func(float animationSpeed = 1.0f);
		void render_animated_background(HGE* hge, float dt, float speedMultiplier);
		void menu_dispose(HGE*hge);
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
	int get_min_width();
	void set_sessional_hardness(Hardness hardness);
	void current_left();
	void current_right();
	void current_up();
	void current_down();
	void current_clockwise();
	void current_counterclockwise();
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
	bool current_collides_downside();
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
	bool bell_rings_on_tick();
};
