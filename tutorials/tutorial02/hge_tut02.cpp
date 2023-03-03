#include "Tetris.h"

Tetris game;

bool FrameFunc()
{
	if(game.mode == GameMode::Menu)
	{
		if(game.menu_frame_func(game.hge) == MenuOptions::Exit)
			return true;
	}
	else if(game.mode == GameMode::Game)
	{
		if(game.in_game_frame_func())
			return true;
	}
	else if(game.mode == GameMode::Limbo)
	{
		if(game.limbo_frame_func())
			return true;
	}
	return false;
}

bool RenderFunc()
{
	game.hge->Gfx_BeginScene();
	game.hge->Gfx_Clear(0);

	if(game.mode == GameMode::Menu)
		game.menu_render_func(0.5);
	else if(game.mode == GameMode::Game)
		game.in_game_render_func(0.05);
	else if(game.mode == GameMode::Limbo)
		game.limbo_render_func(0.1);

	game.hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	game.hge = hgeCreate(HGE_VERSION);

	game.hge->System_SetState(HGE_LOGFILE, "hge_tut02.log");
	game.hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	game.hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	game.hge->System_SetState(HGE_TITLE, "HGE Tutorial 02 - Using input, sound and rendering");
	game.hge->System_SetState(HGE_WINDOWED, true);
	game.hge->System_SetState(HGE_SCREENWIDTH, GameConstants::FRAMEX);
	game.hge->System_SetState(HGE_SCREENHEIGHT, GameConstants::FRAMEY);
	game.hge->System_SetState(HGE_SCREENBPP, 32);

	if(game.hge->System_Initiate())
	{
		game.enter_menu();
		game.init_score_font();

		game.hge->System_Start();

		game.dispose_score_font();
		game.dispose_textures();
	}
	else game.popup_error();

	// Clean up and shutdown
	game.hge->System_Shutdown();
	game.hge->Release();
	return 0;
}
