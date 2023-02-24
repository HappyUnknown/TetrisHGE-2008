#include "DealFiles.h"
static struct TetrisSettings
{
	static const char splitter = '~';
	static std::string TetrisSettings::get_settings_path();
	static std::vector<std::string> TetrisSettings::read_settings();
	static void TetrisSettings::add_setting(std::string key, std::string value);
	static int TetrisSettings::setting_row_index(std::string key);
	static bool TetrisSettings::setting_exists(std::string key);
	static std::string TetrisSettings::read_setting_value(std::string key);
	static bool TetrisSettings::edit_setting(std::string key, std::string newValue);
};
