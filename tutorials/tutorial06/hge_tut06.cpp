#include "..\..\include\hge.h"
#include "..\..\include\hgefont.h"
#include "..\..\include\hgegui.h"
#include "menuitem.h"
#include <math.h>

HGE *menuHGE=0;

struct MenuGUI
{
	HEFFECT				snd;
	HTEXTURE			tex;
	hgeQuad				quad;
	hgeGUI				*gui;
	hgeFont				*fnt;
	hgeSprite			*spr;

	void animate_background(HGE*hge, float dt)
	{
		static float t=0.0f;
		float tx,ty;
		t+=dt;
		tx=50*cosf(t/60);
		ty=50*sinf(t/60);
		quad.v[0].tx=tx;        
		quad.v[0].ty=ty;
		quad.v[1].tx=tx+800/64; 
		quad.v[1].ty=ty;
		quad.v[2].tx=tx+800/64; 
		quad.v[2].ty=ty+600/64;
		quad.v[3].tx=tx;
		quad.v[3].ty=ty+600/64;

	}
	bool process_selection(HGE*hge, float dt)
	{
		int id;
		static int lastid=0;
		if(hge->Input_GetKeyState(HGEK_ESCAPE)) 
		{ 
			lastid=5; 
			gui->Leave(); 
		}
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:
			case 2:
			case 3:
			case 4:
				gui->SetFocus(1);
				gui->Enter();
				break;

			case 5: return true;
			}
		}
		else if(id) 
		{ 
			lastid=id; 
			gui->Leave(); 
		}
		return false;
	}
	bool frame_func(HGE*hge)
	{
		float dt=hge->Timer_GetDelta();
		if(process_selection(hge,dt)) return true;
		animate_background(hge,dt);

		return false;
	}

	bool setup(HGE*hge)
	{
		// Load sound and textures
		quad.tex=hge->Texture_Load("bg.png");
		tex=hge->Texture_Load("cursor.png");
		snd=hge->Effect_Load("menu.wav");
		if(!quad.tex || !tex || !snd)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return false;
		}

		// Set up the quad we will use for background animation
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFFFFF;
		}

		quad.v[0].x=0; quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0; quad.v[3].y=600; 


		// Load the font, create the cursor sprite
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		// Create and initialize the GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Exit"));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();
		return true;
	}
	void render_func(HGE*hge)
	{
		hge->Gfx_RenderQuad(&quad);
		gui->Render();
		fnt->SetColor(0xFFFFFFFF);
	}
	void dispose(HGE*hge)
	{
		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(tex);
		hge->Texture_Free(quad.tex);
	}
};

MenuGUI menu;

bool FrameFunc()
{
	if(menu.frame_func(menuHGE))
		return true;

	return false;
}


bool RenderFunc()
{
	// Render graphics
	menuHGE->Gfx_BeginScene();
	menu.render_func(menuHGE);
	menuHGE->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	menuHGE = hgeCreate(HGE_VERSION);

	menuHGE->System_SetState(HGE_LOGFILE, "hge_tut06.log");
	menuHGE->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	menuHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
	menuHGE->System_SetState(HGE_TITLE, "HGE Tutorial 06 - Creating menus");
	menuHGE->System_SetState(HGE_WINDOWED, true);
	menuHGE->System_SetState(HGE_SCREENWIDTH, 800);
	menuHGE->System_SetState(HGE_SCREENHEIGHT, 600);
	menuHGE->System_SetState(HGE_SCREENBPP, 32);

	if(menuHGE->System_Initiate())
	{

		menu.setup(menuHGE);

		// Let's rock now!
		menuHGE->System_Start();

		menu.dispose(menuHGE);
	}

	// Clean up and shutdown
	menuHGE->System_Shutdown();
	menuHGE->Release();
	return 0;
}
