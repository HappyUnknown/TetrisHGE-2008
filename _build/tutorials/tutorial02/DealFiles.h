#include "TetrominoHeirs.h"
static class DealFiles
{
	static std::string get_definite_filename();
public:
	static bool recreate_file(std::string);
	static bool write_lines(std::string filename,std::vector<std::string> lines);
	static bool append_text(std::string filename, std::string line);
	static bool append_line(std::string filename, std::string line);
	static std::vector<std::string> read_lines(std::string filename);
	static bool file_exists(std::string filename);
};
