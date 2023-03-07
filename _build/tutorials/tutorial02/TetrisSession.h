#include "HGEQuadFactory.h"
static struct TetrisSession
{
	static const char splitter = ' ';
	static std::string TetrisSession::get_session_path();
	static void recreate_session_file();
	static bool session_file_exists();
	static std::string guarantee_get_session_path();
	static void append_figure(TetrominoBase* figure);
	static void append_figures(std::vector<TetrominoBase*>);
	static void write_figures(std::vector<TetrominoBase*>);
	static std::vector<std::string> read_figure_lines();
	static void reset_session();
	static std::string extract_figures(HGE*, std::vector<TetrominoBase*>&);
};
