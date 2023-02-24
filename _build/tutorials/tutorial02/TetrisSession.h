#include "HGEQuadFactory.h"
static struct TetrisSession
{
	static const char splitter = ' ';
	static std::string TetrisSession::get_session_path();
	static void TetrisSession::recreate_session_file();
	static bool TetrisSession::session_file_exists();
	static std::string TetrisSession::guarantee_get_session_path();
	static void TetrisSession::append_figure(TetrominoBase* figure);
	static void TetrisSession::append_figures(std::vector<TetrominoBase*> figures);
	static void TetrisSession::write_figures(std::vector<TetrominoBase*> figures);
	static std::vector<std::string> TetrisSession::read_figure_lines();
	static void TetrisSession::reset_session();
	static std::string TetrisSession::extract_figures(HGE*hge, std::vector<TetrominoBase*>&figures);
};
