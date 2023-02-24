#include "DealFiles.h"
std::string DealFiles::get_definite_filename()
{
	return "D:\TESTFILE.TXT";
}
bool DealFiles::recreate_file(std::string filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::fstream::out);
	bool opened = file.is_open();
	file.close();
	return opened;
}
 bool DealFiles::write_lines(std::string filename,std::vector<std::string> lines)
	{
		std::ofstream inStream;
		inStream.open(filename.c_str(), std::fstream::out);
		if(DealFiles::file_exists(filename))
		{
			DealFiles::recreate_file(filename);
			for(int i=0;i<lines.size();i++)
				append_line(filename, lines[i]);
			return true;
		}
		return false;
	}
 bool DealFiles::append_text(std::string filename, std::string line)
	{
		std::ofstream inStream;
		inStream.open(filename.c_str(), std::fstream::out | std::fstream::app);
		if(inStream.is_open())
		{
			inStream << line.c_str();
			inStream.close();
		}
		return true;
	}
 bool DealFiles::append_line(std::string filename, std::string line)
	{
		std::ofstream inStream;
		inStream.open(filename.c_str(), std::fstream::out | std::fstream::app);
		if(inStream.is_open())
		{
			inStream << line.c_str()<<"\n";
			inStream.close();
		}
		return true;
	}
 std::vector<std::string> DealFiles::read_lines(std::string filename)
	{
		std::vector<std::string> lines;
		std::fstream outStream(filename.c_str(), std::fstream::in);
		if(outStream.is_open())
		{
			std::string buffer;
			while(getline(outStream, buffer))	//read data from file object and put it into string.
				lines.push_back(buffer); //print the data of the string
			outStream.close(); //close the file object.
		}
		return lines;
	}
 bool DealFiles::file_exists(std::string filename)
	{
	  std::ifstream f(filename.c_str());
	  return f.good();
	}