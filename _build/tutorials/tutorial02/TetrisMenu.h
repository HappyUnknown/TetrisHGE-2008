#include "TetrisAudio.h"

struct TetrisMenu
{
	HEFFECT	menuSND;
	HTEXTURE menuCRSTex;
	hgeQuad	menuBackIMG;
	hgeGUI *menuGUI;
	hgeFont	*menuFNT;
	hgeSprite *menuCursorSPR;

		void TetrisMenu::animate_background(HGE*hge, float dt, float speedMultiplier)
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
		MenuOptions TetrisMenu::menu_process_selection(HGE*hge, float dt)
		{
			int valueRead;

			int id;
			static int lastid=MenuOptions::Default;
			id=menuGUI->Update(dt);
			if(id == -1)
			{
				switch(lastid)
				{
				case MenuOptions::Play:
					return MenuOptions::Play;
				case MenuOptions::Resume:
					return MenuOptions::Resume;
				case MenuOptions::WidthLess:
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					return MenuOptions::WidthLess;
				case MenuOptions::WidthMore:
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					return MenuOptions::WidthMore;
				case MenuOptions::HeightLess:
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					return MenuOptions::HeightLess;
				case MenuOptions::HeightMore:
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					return MenuOptions::HeightMore;
				case MenuOptions::HardnessLess:
					valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
					if(valueRead > Hardness::Easy)
					{
						if(TetrisSettings::setting_exists("hardness_mode"))
							TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(--valueRead));
						else
							TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(--valueRead));
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
					return MenuOptions::HardnessLess;
				case MenuOptions::HardnessMore:
					valueRead = StringExtensions::int_parse(TetrisSettings::read_setting_value("hardness_mode"));
					if(valueRead < Hardness::Hard)
					{
						if(TetrisSettings::setting_exists("hardness_mode"))
							TetrisSettings::edit_setting("hardness_mode", StringExtensions::to_string(++valueRead));
						else
							TetrisSettings::add_setting("hardness_mode", StringExtensions::to_string(++valueRead));
						TetrisSession::reset_session();
					}
					menuGUI->SetFocus(1);
					menuGUI->Enter();
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
		MenuOptions TetrisMenu::menu_frame_func(HGE*hge)
		{
			float dt=hge->Timer_GetDelta();
			MenuOptions options = menu_process_selection(hge, dt);
			if(options == MenuOptions::Exit || hge->Input_KeyDown(HGEK_ESCAPE))
				return MenuOptions::Exit;

			return MenuOptions::Default;
		}
		
		void TetrisMenu::menu_render_func(HGE*hge, float animationSpeed)
		{
			float dt = hge->Timer_GetDelta();
			render_animated_background(hge, dt, animationSpeed); //multiplier just does not care
			menuGUI->Render();
			menuFNT->SetColor(TetrominoColors::White);
		}
		void TetrisMenu::render_animated_background(HGE* hge, float dt, float speedMultiplier)
		{
			hge->Gfx_RenderQuad(&menuBackIMG);
			animate_background(hge,dt,speedMultiplier);
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
};