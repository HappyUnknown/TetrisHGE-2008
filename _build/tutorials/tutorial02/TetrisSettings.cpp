#include "TetrisSettings.h"

	std::string TetrisSettings::get_settings_path()
	{
		return "settings.txt";
	}
	std::vector<std::string> TetrisSettings::read_settings()
	{
		return DealFiles::read_lines(get_settings_path());
	}
	void TetrisSettings::add_setting(std::string key, std::string value)
	{
		if(!DealFiles::file_exists(get_settings_path())) DealFiles::recreate_file(get_settings_path());
		DealFiles::append_line(get_settings_path(),key+StringExtensions::to_string(splitter)+value);
	}
	int TetrisSettings::setting_row_index(std::string key)
	{
		std::vector<std::string>lines = read_settings();
		for(int i=0;i<lines.size();i++)
		{
			std::vector<std::string>sublines = StringExtensions::split(lines[i], StringExtensions::to_string(splitter));
			if(sublines[0]==key)
				return i;
		}
		return -1;
	}
	bool TetrisSettings::setting_exists(std::string key)
	{
		return setting_row_index(key)!=-1;
	}
	std::string TetrisSettings::read_setting_value(std::string key)
	{
		std::vector<std::string>lines = read_settings();
		if(setting_exists(key))
		{
			int lineIndex = setting_row_index(key);		
			std::string delim = StringExtensions::to_string(TetrisSettings::splitter);
			std::string line = lines[lineIndex];
			std::vector<std::string>lineParts = StringExtensions::split(line, delim);
			if(lineParts.size() >= 2) return lineParts[1];
		}
		return "NO_VALUE";
	}
	bool TetrisSettings::edit_setting(std::string key, std::string newValue)
	{
		if(setting_exists(key))
		{
			int settingIndex = setting_row_index(key);
			std::vector<std::string> lines = read_settings();
			lines[settingIndex] = key+splitter+newValue;
			DealFiles::write_lines(get_settings_path(), lines);
			return true;
		}	
		return false;
	}
