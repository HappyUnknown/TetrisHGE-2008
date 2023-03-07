#include "DealFiles.h"
static struct TetrisSettings
{
	static const char splitter = '~';
	static std::string TetrisSettings::get_settings_path();
	static std::vector<std::string> TetrisSettings::read_settings();
	static void TetrisSettings::add_setting(std::string, std::string);
	static int TetrisSettings::setting_row_index(std::string);
	static bool TetrisSettings::setting_exists(std::string);
	static std::string TetrisSettings::read_setting_value(std::string);
	static bool TetrisSettings::edit_setting(std::string, std::string);
};
