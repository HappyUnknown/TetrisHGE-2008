#include "HGEQuadFactory.h"
hgeQuad* HGEQuadFactory::init_visual_square(HGE*hge, std::string texturePath, hgeU32 col, float tfrac, float tstartx, float tstarty)
	{
		hgeQuad*quad = new hgeQuad();
		quad->tex=hge->Texture_Load(texturePath.c_str());
		if(!quad->tex)
		{
			MessageBox(NULL, "Can't load game square texture", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
		}
		quad->blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
		for(int i=0;i<4;i++)
		{
			quad->v[i].z=tfrac;
			quad->v[i].col=col;
		}
		quad->v[0].tx=tstartx; 
		quad->v[0].ty=tstarty; 
		quad->v[1].tx=tstartx+tfrac;
		quad->v[1].ty=tstarty; 
		quad->v[2].tx=tstartx+tfrac;
		quad->v[2].ty=tstarty+tfrac;
		quad->v[3].tx=tstartx; 
		quad->v[3].ty=tstarty+tfrac;
		return quad;
	}