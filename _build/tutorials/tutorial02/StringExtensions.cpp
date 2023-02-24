#include "StringExtensions.h"
std::vector<std::string> StringExtensions::split(std::string source, std::string delimiter)
	{
	  std::vector<std::string> res;
	  int delimIndex;
	  do
	  {
		delimIndex = source.find(delimiter);
		if (delimIndex >= 0)
		{
		  res.push_back(source.substr(0, delimIndex));
		  source = source.substr(delimIndex + 1);
		}
		else res.push_back(source);
	  } while (delimIndex >= 0);
	  return res;
	}
	int StringExtensions::int_parse(std::string str)
	{
		int num = 0;
		try
		{
			std::stringstream s_str( str );
			s_str >> num;
		}
		catch(...){}
		return num;
	}
	double StringExtensions::double_parse(std::string str)
	{
		double num = 0.0;
		try
		{
			std::stringstream s_str( str );
			s_str >> num;
		}
		catch(...){}
		return num;
	}
	std::string StringExtensions::trim(std::string source, char delimiter)
	{
		int firstIndex = source.find_first_not_of(delimiter);
		int lastIndex = source.find_last_not_of(delimiter);
		if(firstIndex==std::string::npos||lastIndex==std::string::npos)
			return source;
		else if(firstIndex==lastIndex)//and both are distiguishable
			return StringExtensions::to_string(source[firstIndex]);
		return source.substr(firstIndex, lastIndex+1);
	}
	char* StringExtensions::to_char_array(std::string str)
	{
		char *arrStr = new char[str.size() + 1];
		strcpy(arrStr, str.c_str());
		return arrStr;
	}
