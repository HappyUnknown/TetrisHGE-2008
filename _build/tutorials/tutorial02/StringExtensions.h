#include "Hardness.h"

static struct StringExtensions
{
	static std::vector<std::string> StringExtensions::split(std::string source, std::string delimiter);
	static int StringExtensions::int_parse(std::string str);
	static double StringExtensions::double_parse(std::string str);
	static std::string StringExtensions::trim(std::string source, char delimiter);
	static char* StringExtensions::to_char_array(std::string str);
	template<class T>
	static std::string to_string(const T &value) 
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}
};
