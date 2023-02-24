#include "TetrominoColors.h"
static struct HGEQuadFactory
{
	static hgeQuad* init_visual_square(HGE*hge, std::string texturePath, hgeU32 col, float tfrac = GameConstants::get_texture_fraction(), float tstartx=0, float tstarty=0);
};
