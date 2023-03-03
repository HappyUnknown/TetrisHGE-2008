#include "Tetris.h"


	void Tetris::init_score_font()
	{
		scorefont=new hgeFont("font1.fnt");
	}
	void Tetris::print_message(std::string msg)
	{
		scorefont->printf(7, 7, HGETEXT_LEFT, msg.c_str());
	}
	void Tetris::render_score()
	{
		print_message("SCORE: "+StringExtensions::to_string(score));
	}
	void Tetris::render_lose()
	{
		print_message("YOU LOSE WITH SCORE OF "+StringExtensions::to_string(score)+"\nPress any key to continue...");
	}
	void Tetris::dispose_score_font()
	{
		delete scorefont;
	}
		void Tetris::animate_background(HGE*hge, float dt, float speedMultiplier)
		{
			static float t=0.0f;
			float tx,ty;
			t += dt * speedMultiplier;
			tx = 50*cosf(t/60);
			ty = 50*sinf(t/60);
			menu.menuBackIMG.v[0].tx = tx;        
			menu.menuBackIMG.v[0].ty = ty;
			menu.menuBackIMG.v[1].tx = tx+GameConstants::FRAMEX/64; 
			menu.menuBackIMG.v[1].ty = ty;
			menu.menuBackIMG.v[2].tx = tx+GameConstants::FRAMEX/64; 
			menu.menuBackIMG.v[2].ty = ty+GameConstants::FRAMEY/64;
			menu.menuBackIMG.v[3].tx = tx;
			menu.menuBackIMG.v[3].ty = ty+GameConstants::FRAMEY/64;
		}
		void Tetris::enter_game(bool resume)
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
		int Tetris::read_correct_field_width()
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
		int Tetris::read_correct_field_height()
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
		MenuOptions Tetris::menu_frame_func(HGE*hge)
		{
			float dt=hge->Timer_GetDelta();
			
			char* charlineWidth = StringExtensions::to_char_array(StringExtensions::to_string(read_correct_field_width()));
			char* charlineHeight = StringExtensions::to_char_array(StringExtensions::to_string(read_correct_field_height()));
			char* charlineHardness = StringExtensions::to_char_array(TetrisSettings::read_setting_value("hardness_mode"));

			MenuOptions options = menu.menu_process_selection(hge, dt, charlineWidth, charlineHeight, charlineHardness);
			if(options == MenuOptions::Play)
				enter_game(false);
			else if(options == MenuOptions::Resume)
				enter_game(true);
			else if(options == MenuOptions::WidthLess)
			{
				int valueRead = read_correct_field_width();
				if(valueRead > get_min_width())
				{	
					if(TetrisSettings::setting_exists("field_width"))
						TetrisSettings::edit_setting("field_width", StringExtensions::to_string(--valueRead));
					else
						TetrisSettings::add_setting("field_width", StringExtensions::to_string(--valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::WidthMore)
			{
				int valueRead = read_correct_field_width();
				if(valueRead < GameConstants::MAX_FIELD_WIDTH)
				{
					if(TetrisSettings::setting_exists("field_width"))
						TetrisSettings::edit_setting("field_width", StringExtensions::to_string(++valueRead));
					else
						TetrisSettings::add_setting("field_width", StringExtensions::to_string(++valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::HeightLess)
			{
				int valueRead = read_correct_field_height();
				if(valueRead > GameConstants::MIN_FIELD_HEIGHT)
				{
					if(TetrisSettings::setting_exists("field_height"))
						TetrisSettings::edit_setting("field_height", StringExtensions::to_string(--valueRead));
					else
						TetrisSettings::add_setting("field_height", StringExtensions::to_string(--valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::HeightMore)
			{
				int valueRead = read_correct_field_height();
				if(valueRead < GameConstants::MAX_FIELD_HEIGHT)
				{
					if(TetrisSettings::setting_exists("field_height"))
						TetrisSettings::edit_setting("field_height", StringExtensions::to_string(++valueRead));
					else
						TetrisSettings::add_setting("field_height", StringExtensions::to_string(++valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::HardnessLess)
			{
				int valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
				if(valueRead > Hardness::Easy)
				{
					if(TetrisSettings::setting_exists("hardness_mode"))
						TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(--valueRead));
					else
						TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(--valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::HardnessMore)
			{
				int valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
				if(valueRead < Hardness::Hard)
				{
					if(TetrisSettings::setting_exists("hardness_mode"))
						TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(++valueRead));
					else
						TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(++valueRead));
					this->menu_setup_loaded();//refreshes menu settings
					TetrisSession::reset_session();
				}
				menu.menuGUI->SetFocus(1);
				menu.menuGUI->Enter();
			}
			else if(options == MenuOptions::Exit || hge->Input_KeyDown(HGEK_ESCAPE))
				return MenuOptions::Exit;

			return MenuOptions::Default;
		}
		
		void Tetris::enter_menu()
		{
			menu_setup_loaded(true);
			mode = GameMode::Menu;
		}
		void Tetris::menu_render_func(float animationSpeed)
		{
			float dt = hge->Timer_GetDelta();
			render_animated_background(hge, dt, animationSpeed); //multiplier just does not care
			menu.menuGUI->Render();
			menu.menuFNT->SetColor(TetrominoColors::White);
		}
		void Tetris::render_animated_background(HGE* hge, float dt, float speedMultiplier)
		{
			hge->Gfx_RenderQuad(&menu.menuBackIMG);
			animate_background(hge,dt,speedMultiplier);
		}
	Tetris::Tetris()
	{
		hge = 0;
		fieldWidth = GameConstants::DEFAULT_FIELD_WIDTH;
		fieldHeight = GameConstants::DEFAULT_FIELD_HEIGHT;
		loopTime = 0;
		set_sessional_hardness(Hardness::Hard);
		mode = GameMode::Frozen;
		score = 0;
		initI = GameConstants::INIT_I;
		initJ = GameConstants::RESERVE_INIT_J;
	}
	int Tetris::get_min_width()
	{
		return initJ + 4;
	}
	void Tetris::set_sessional_hardness(Hardness hardness)
	{
		loopMaxTime = TetrisMath::math_fall_period(hardness);
	}
	//std::vector<TetrominoBase*>Tetris::get_moving_figures()
	//{
	//	std::vector<TetrominoBase*>movings;
	//	for(int i=0;i<figures.size();i++)
	//		if(figures[i]->is_moving())
	//			movings.push_back(figures[i]);
	//	return movings;
	//}
	void Tetris::current_left()
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->move_left();
		if(!current_collides_leftside() && this->all_in_box(current_tetromino()->preview_left()))
			current_tetromino()->move_left();
	}
	void Tetris::current_right()
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->move_right();
		if(!current_collides_rightside() && this->all_in_box(current_tetromino()->preview_right()))
			current_tetromino()->move_right();
	}
	void Tetris::current_up()
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->move_up();
		if(!current_collides_upside() && this->all_in_box(current_tetromino()->preview_up()))
			current_tetromino()->move_up();
	}
	void Tetris::current_down(int step)
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->move_down();
		if(!current_collides_downside(step) && this->all_in_box(current_tetromino()->preview_down(step)))
			current_tetromino()->move_down(step);
	}
	void Tetris::current_clockwise()
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->rotate_clockwise();
		if(!current_collides_clockwise() && this->all_in_box(current_tetromino()->preview_clockwise(current_tetromino()->center)))
			current_tetromino()->rotate_clockwise();
	}
	void Tetris::current_counterclockwise()
	{
		//std::vector<TetrominoBase*> movings = get_moving_figures();
		//for(int i=0;i<movings.size();i++)
		//	movings[i]->rotate_counterclockwise();
		if(!current_collides_counterclockwise() && this->all_in_box(current_tetromino()->preview_counterclockwise(current_tetromino()->center)))
			current_tetromino()->rotate_counterclockwise();
	}
	int Tetris::squares_on_width()
	{
		return GameConstants::FRAMEX/GameConstants::VISUAL_SIZE;
	}
	int Tetris::squares_on_height()
	{
		return GameConstants::FRAMEY/GameConstants::VISUAL_SIZE;
	}
	int Tetris::free_framecells_x()
	{
		const int OUTLINE_BLOCKS = 2;
		int areaFieldWidth = fieldWidth + OUTLINE_BLOCKS;
		int areaCellsOnHalf = areaFieldWidth;
		return GameConstants::squares_on_width() - areaCellsOnHalf;
	}
	int Tetris::free_framecells_y()
	{
		const int OUTLINE_BLOCKS = 2;
		int areaFieldHeight = fieldHeight + OUTLINE_BLOCKS;
		int areaCellsOnHalf = areaFieldHeight;
		return GameConstants::squares_on_height() - areaCellsOnHalf;
	}
	int Tetris::area_cell_align_x()
	{
		const int CORRECTION_VALUE = 1;
		return free_framecells_x() / 2+CORRECTION_VALUE;
	}
	int Tetris::area_cell_align_y()
	{
		const int CORRECTION_VALUE = 1;
		return free_framecells_y() / 2+CORRECTION_VALUE;
	}
	int Tetris::area_align_x()
	{
		return area_cell_align_x()*GameConstants::VISUAL_SIZE;
	}
	int Tetris::area_align_y()
	{
		return area_cell_align_y()*GameConstants::VISUAL_SIZE;
	}
	void Tetris::reimagine_field()
	{
		for(int i=0;i<figures.size();i++)
			for (int j=0;j<figures[i]->squares.size();j++)
			{
				figures[i]->squares[j].graphics.v[0].x=figures[i]->squares[j].pos.j*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_x(); 
				figures[i]->squares[j].graphics.v[0].y=figures[i]->squares[j].pos.i*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_y();
				figures[i]->squares[j].graphics.v[1].x=figures[i]->squares[j].pos.j*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_x(); 
				figures[i]->squares[j].graphics.v[1].y=figures[i]->squares[j].pos.i*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_y();
				figures[i]->squares[j].graphics.v[2].x=figures[i]->squares[j].pos.j*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_x(); 
				figures[i]->squares[j].graphics.v[2].y=figures[i]->squares[j].pos.i*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_y();
				figures[i]->squares[j].graphics.v[3].x=figures[i]->squares[j].pos.j*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_x(); 
				figures[i]->squares[j].graphics.v[3].y=figures[i]->squares[j].pos.i*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_y();
				for (int vi = 0; vi < 4; vi++)
				{
					figures[i]->squares[j].graphics.v[vi].x += GameConstants::QUAD_RADIUS;
					figures[i]->squares[j].graphics.v[vi].y += GameConstants::QUAD_RADIUS;
				}
			}	
	}
	void Tetris::imagine_wall()
	{
		for (int i=0;i<bricks.size();i++)
		{
			bricks[i].graphics.v[0].x=bricks[i].pos.j*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_x(); 
			bricks[i].graphics.v[0].y=bricks[i].pos.i*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_y();
			bricks[i].graphics.v[1].x=bricks[i].pos.j*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_x(); 
			bricks[i].graphics.v[1].y=bricks[i].pos.i*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_y();
			bricks[i].graphics.v[2].x=bricks[i].pos.j*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_x(); 
			bricks[i].graphics.v[2].y=bricks[i].pos.i*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_y();
			bricks[i].graphics.v[3].x=bricks[i].pos.j*GameConstants::VISUAL_SIZE-GameConstants::QUAD_RADIUS+area_align_x(); 
			bricks[i].graphics.v[3].y=bricks[i].pos.i*GameConstants::VISUAL_SIZE+GameConstants::QUAD_RADIUS+area_align_y();
			for (int vi = 0; vi < 4; vi++)
			{
				bricks[i].graphics.v[vi].x += GameConstants::QUAD_RADIUS;
				bricks[i].graphics.v[vi].y += GameConstants::QUAD_RADIUS;
			}
		}	
	}
	void Tetris::render_inbox()
	{
		for(int i=0;i<figures.size();i++)
			for (int j=0;j<figures[i]->squares.size();j++)
				hge->Gfx_RenderQuad(&figures[i]->squares[j].graphics);
	}
	void Tetris::render_wall()
	{
		for(int i=0;i<bricks.size();i++)
			hge->Gfx_RenderQuad(&bricks[i].graphics);
	}
	void Tetris::render_field()
	{
		render_inbox();
		render_wall();
	}
	void Tetris::in_game_render_func(float animationSpeed)
	{
		float dt = hge->Timer_GetDelta();
		render_animated_background(hge,dt,animationSpeed);
		render_field();
		render_score();
	}
	bool Tetris::in_game_frame_func()
	{
		float dt = hge->Timer_GetDelta();

		if (hge->Input_KeyDown(HGEK_ESCAPE)) 
			enter_menu();
		if (hge->Input_KeyDown(HGEK_LEFT))
			current_left();
		if (hge->Input_KeyDown(HGEK_RIGHT))
			current_right();
		if (hge->Input_KeyDown(HGEK_UP))
			current_up();
		if (hge->Input_KeyDown(HGEK_DOWN) || bell_rings_on_tick())
		{
			int step = 1;
			reset_timer();
			bool downgoInBox = all_in_box(current_tetromino()->preview_down(step));
			bool canMoveDown = !current_collides_downside(step);
			if(canMoveDown && downgoInBox)
				current_down(step);
			else
				//no need to create new random examplar - random examplar creation is an automatic process
				place_all();
		}
		if (hge->Input_KeyDown(HGEK_SPACE))
			current_tetromino()->move_down(current_min_projection_delta());
		if (hge->Input_KeyDown(HGEK_TAB))
			current_clockwise();
		if (hge->Input_KeyDown(HGEK_SHIFT))
			current_counterclockwise();
		if (hge->Input_KeyDown(HGEK_ENTER))
			place_all();

		clear_all_rows_full();

		TetrisSession::write_figures(figures);

		if(all_landed())
			if(!spawn(TetrominoColors::get_random_color()))
				mode=GameMode::Limbo;

		reimagine_field();
		title_squares();

		return false;
	}
	void Tetris::limbo_render_func(float animationSpeed)
	{
		render_animated_background(hge, hge->Timer_GetDelta(), animationSpeed);
		render_field();
		render_lose();
	}
	bool Tetris::limbo_frame_func()
	{
		if(hge->Input_KeyDown(HGEK_ESCAPE))
			return true;
		else if(hge->Input_GetKey())
			enter_menu();

		return false;
	}
	TetrominoBase* Tetris::get_random_tetromino(int initI, int initJ)
	{
		srand(time(NULL));
		TetrominoTypes type = (TetrominoTypes)(rand() % 7 + 1);
		switch (type)
		{
		case TetrominoTypes::I:
			return new TetrominoI(initI, initJ);
		case TetrominoTypes::J:
			return new TetrominoJ(initI, initJ);
		case TetrominoTypes::L:
			return new TetrominoL(initI, initJ);
		case TetrominoTypes::O:
			return new TetrominoO(initI, initJ);
		case TetrominoTypes::S:
			return new TetrominoS(initI, initJ);
		case TetrominoTypes::T:
			return new TetrominoT(initI, initJ);
		case TetrominoTypes::Z:
			return new TetrominoZ(initI, initJ);
		default:
			return new TetrominoO(initI, initJ);
		}
	}
	//returns curent, if figures are not empty, and last is not landed 
	TetrominoBase* Tetris::current_tetromino()
	{
		if(figures.size()>0)
		if(!figures[figures.size()-1]->is_landed())
			return figures[figures.size()-1];
		return get_random_tetromino(initI, initJ);
	}
	bool Tetris::spawn(hgeU32 col)
	{
		TetrominoBase*figure = get_random_tetromino(initI, initJ);
		if(figure->intersects_any(figures)) return false;
		for(int i=0;i<figure->squares.size();i++)
			figure->squares[i].graphics = *HGEQuadFactory::init_visual_square(hge, this->squarePath, col, this->brickTexFraction, this->brickTexStartX, this->brickTexStartY);
		figures.push_back(figure);
		for(int i=0;i<current_tetromino()->squares.size();i++)
		{
			current_tetromino()->squares[i].graphics.tex=hge->Texture_Load(GameConstants::get_texture_path().c_str());
			if(!current_tetromino()->squares[i].graphics.tex)
			{
				MessageBox(NULL, "Can't load MENU.WAV or PARTICLES.PNG", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
				hge->System_Shutdown();
				hge->Release();
			}
		}
		return true;
	}
	void Tetris::dispose_textures()
	{
		for(int i=0;i<figures.size();i++)
			for (int j=0;j<figures[i]->squares.size();j++)
				hge->Texture_Free(figures[i]->squares[j].graphics.tex);
	}
	void Tetris::place_all()
	{
		for(int i=0;i<figures.size();i++)
			figures[i]->place();
		player.play_place(hge);
	}
	bool Tetris::all_landed()
	{
		for(int i=0;i<figures.size();i++)
			if(!figures[i]->is_landed())
				return false;
		return true;
	}
	bool Tetris::current_collides_downside(int step)
	{
		for(int i=0;i<figures.size();i++)
			if(figures[i]->intersects_any(current_tetromino()->preview_down(step)) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::current_collides_upside()
	{
		for(int i=0;i<figures.size();i++)
			if(figures[i]->intersects_any(current_tetromino()->preview_up()) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::current_collides_leftside()
	{
		for(int i=0;i<figures.size();i++)
			//if(current_tetromino()->is_rightside(figures[i]) && current_tetromino() != figures[i])
			if(figures[i]->intersects_any(current_tetromino()->preview_left()) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::current_collides_rightside()
	{
		for(int i=0;i<figures.size();i++)
			if(figures[i]->intersects_any(current_tetromino()->preview_right()) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::current_collides_clockwise()
	{
		for(int i=0;i<figures.size();i++)
			if(figures[i]->intersects_any(current_tetromino()->preview_clockwise(current_tetromino()->center)) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::current_collides_counterclockwise()
	{
		for(int i=0;i<figures.size();i++)
			if(figures[i]->intersects_any(current_tetromino()->preview_counterclockwise(current_tetromino()->center)) && current_tetromino() != figures[i])
				return true;
		return false;
	}
	bool Tetris::all_in_box(std::vector<GameSquare>squares)
	{
		for(int i=0;i<squares.size();i++)
			if(squares[i].pos.i < 0 || squares[i].pos.i>=fieldHeight || squares[i].pos.j < 0 || squares[i].pos.j>=fieldWidth)
				return false;
		return true;
	}
	void Tetris::popup(std::string message)
	{
		MessageBox(NULL, message.c_str(), "Achtung", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	}
	void Tetris::popup_error()
	{
		popup(hge->System_GetErrorMessage());
	}
	GameSquare* Tetris::init_brick(int i, int j, hgeU32 col)
	{
		GameSquare*brick = new GameSquare();
		brick->graphics = *HGEQuadFactory::init_visual_square(hge, brickPath, col, this->brickTexFraction, this->brickTexStartX, this->brickTexStartY);
		brick->landed = true;
		brick->pos = Position(i,j);
		return brick;
	}
	void Tetris::init_wall(hgeU32 col)
	{
		bricks.clear();
		for(int j=-1;j<fieldWidth;j++)
			bricks.push_back(*init_brick(-1, j, col));
		for(int i=-1;i<fieldHeight;i++)
			bricks.push_back(*init_brick(i, fieldWidth,col));
		for(int j=fieldWidth;j>=0;j--)
			bricks.push_back(*init_brick(fieldHeight, j,col));
		for(int i=fieldHeight;i>=0;i--)
			bricks.push_back(*init_brick(i, -1,col));
	}
	void Tetris::title_squares()//when figures are 10, and above - the field becomes all overloaded
	{
		std::string msg = "Tetris ["+StringExtensions::to_string(figures.size())+"] => ";
		int lastIndex = figures.size() - 1;
		for(int j=figures[lastIndex]->squares.size()-1;j>=0;j--)
			msg+="["+StringExtensions::to_string(figures[lastIndex]->squares[j].pos.i)+";"+StringExtensions::to_string(figures[lastIndex]->squares[j].pos.j)+"|"+(figures[lastIndex]->squares[j].landed == true ? "!" : "?")+"]";
		//for(int i=figures.size()-1;i>=0;i--)
		//	for(int j=figures[i]->squares.size()-1;j>=0;j--)
		//		msg+="["+StringExtensions::to_string(figures[i]->squares[j].pos.i)+";"+StringExtensions::to_string(figures[i]->squares[j].pos.j)+"|"+(figures[i]->squares[j].landed == true ? "!" : "?")+"]";
		hge->System_SetState(HGE_TITLE, msg.c_str());
	}
	int Tetris::clear_row(int iVal)
	{	
		score+=fieldWidth;
		int totalRowEntries = 0;
		for(int i=0;i<figures.size();i++)
			totalRowEntries += figures[i]->clear_row(iVal);
		if(totalRowEntries>fieldWidth)
			totalRowEntries=fieldWidth;
		return totalRowEntries;
	}
	int Tetris::count_row_squares(int iVal)
	{
		int rowSquares = 0;
		for(int i=0;i<figures.size();i++)
			rowSquares+=figures[i]->count_row_squares(iVal);
		return rowSquares;
	}
	bool Tetris::count_fulfills_score(int count)
	{
		return count>=fieldWidth;
	}
	bool Tetris::row_is_full(int iVal)
	{
		int rowSquareCount = count_row_squares(iVal);
		if(count_fulfills_score(rowSquareCount))
			return true;
		return false;
	}
	void Tetris::fall_above_row(int iVal)
	{
		for(int i=0;i<figures.size();i++)
			figures[i]->fall_above_row(iVal);
	}
	void Tetris::clear_row_full(int iVal)
	{
		int totalCount = 0;
		for(int i=0;i<figures.size();i++)
			if(figures[i]->is_landed())
				totalCount += figures[i]->count_row_squares(iVal);
		if(count_fulfills_score(totalCount))
		{
			clear_row(iVal);
			fall_above_row(iVal);
			player.play_pop(hge);
		}
	}
	void Tetris::clear_all_rows_full()
	{
		for(int i=fieldHeight-1;i>=0;i--)
			clear_row_full(i);
	}
	void Tetris::timer_tick()
	{
		loopTime +=	hge->Timer_GetDelta();
	}
	void Tetris::reset_timer()
	{
		loopTime = 0;
	}
	bool Tetris::bell_rings_on_tick()
	{
		timer_tick();
		if(loopTime >= loopMaxTime)
			return true;
		return false;
	}
	int Tetris::projection_delta(Position currentPos)
	{
		int minDeltaI = fieldHeight;
		for(int fi = 0; fi < figures.size(); fi++)
			for(int fj = 0; fj < figures[fi]->squares.size();fj++)
			{
				Position placedPos = figures[fi]->squares[fj].pos;
				if(!current_tetromino()->takes_position(placedPos))//if figure square considered is not related to current
					if(placedPos.j == currentPos.j)
					{
						int thisDeltaI = (placedPos - currentPos).i;
						if(minDeltaI > thisDeltaI)
							minDeltaI = thisDeltaI;
					}
			}
		if(minDeltaI == fieldHeight) //if none of the figures is lower than current (except current) - get lowest figure position, and fall
		{
			minDeltaI -= current_tetromino()->max_i();
		}
		return minDeltaI;
	}
	int Tetris::current_min_projection_delta()
	{
		TetrominoBase*current = current_tetromino();
		int minDeltaI = INT_MAX;
		for(int i = 0; i < current->squares.size(); i++)
		{
			int currentDelta = projection_delta(current->squares[i].pos) - 1;
			if(minDeltaI > currentDelta)
				minDeltaI = currentDelta;
		}
		return minDeltaI;
	}
