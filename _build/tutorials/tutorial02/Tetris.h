#include "TetrisMenu.h"

struct Tetris
{	
	TetrisAudio player;
	#pragma region SCORE DISPLAY
	int score;
	hgeFont	*scorefont;
	void init_score_font();
	void print_message(std::string);
	void render_score();
	void render_lose();
	void dispose_score_font();
	#pragma endregion
	#pragma region MENU
		TetrisMenu menu;
		//MenuOptions menu_process_selection(HGE*hge, float dt, char* charlineWidth, char* charlineHeight, char* charlineHardness);
		MenuOptions menu_frame_func(HGE*);
		//bool Tetris::menu_setup(HGE*hge, bool animate, char*charlineWidth, char*charlineHeight,char*charlineHardness);
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
	void menu_render_func(float = 1.0f);
	void animate_background(HGE*, float, float = 1.0f);
	void render_animated_background(HGE*, float, float);
	void enter_game(bool);
	int get_min_width();
	void set_sessional_hardness(Hardness);
	void current_left();
	void current_right();
	void current_up();
	void current_down(int);
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
	void in_game_render_func(float = 1.0f);
	bool in_game_frame_func();
	void limbo_render_func(float = 0.1f);
	bool limbo_frame_func();
	TetrominoBase* get_random_tetromino(int, int);
	//returns curent, if figures are not empty, and last is not landed 
	TetrominoBase* current_tetromino();
	bool spawn(hgeU32 col);
	void dispose_textures();
	void place_all();
	bool all_landed();
	bool current_collides_downside(int);
	bool current_collides_upside();
	bool current_collides_leftside();
	bool current_collides_rightside();
	bool current_collides_clockwise();
	bool current_collides_counterclockwise();
	bool all_in_box(std::vector<GameSquare>squares);
	void popup(std::string);
	void popup_error();
	GameSquare* init_brick(int, int, hgeU32);
	void init_wall(hgeU32);
	void title_squares();//when figures are 10, and above - the field becomes all overloaded
	int clear_row(int);
	int count_row_squares(int);
	bool count_fulfills_score(int);
	bool row_is_full(int);
	void fall_above_row(int);
	void clear_row_full(int);
	void clear_all_rows_full();
	void timer_tick();
	void reset_timer();
	int projection_delta(Position);
	int current_min_projection_delta();
	bool bell_rings_on_tick();
	void enter_menu();
	void menu_setup_loaded(bool = false);
};
