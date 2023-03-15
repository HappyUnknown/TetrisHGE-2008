#include "TetrisSession.h"

	std::string TetrisSession::get_session_path()
	{
		return "session.txt";
	}
	void TetrisSession::recreate_session_file()
	{
		DealFiles::recreate_file(get_session_path());
	}
	bool TetrisSession::session_file_exists()
	{
		std::ifstream outStream(get_session_path().c_str());
		return outStream.good();
	}
	std::string TetrisSession::guarantee_get_session_path()
	{
		if(!session_file_exists())
			recreate_session_file();
		return get_session_path();
	}
	void TetrisSession::append_figure(TetrominoBase* figure)
	{
	  std::string delimiter = StringExtensions::to_string(splitter);
	  std::ofstream outfile(guarantee_get_session_path().c_str(), std::ios_base::app | std::ios_base::out);
	  for (int i = 0; i < figure->batch.squares.size(); i++)
		outfile << figure->batch.squares[i].pos.i << delimiter << figure->batch.squares[i].pos.j << delimiter << (int)figure->figureType << delimiter << (int)figure->batch.squares[i].landed << delimiter << (int)TetrominoColors::detect_color(figure->batch.squares[i].graphics.v[0].col) << delimiter << "white_square.png" << std::endl;
	  outfile << "\n";
	  outfile.close();
	}
	void TetrisSession::append_figures(std::vector<TetrominoBase*> figures)
	{
		for(int i=0;i<figures.size();i++)
			append_figure(figures[i]);
	}
	void TetrisSession::write_figures(std::vector<TetrominoBase*> figures)
	{
		recreate_session_file();
		append_figures(figures);
	}
	std::vector<std::string> TetrisSession::read_figure_lines()
	{
		return DealFiles::read_lines(guarantee_get_session_path());
	}
	void TetrisSession::reset_session()
	{
		DealFiles::recreate_file(guarantee_get_session_path());
	}
	std::string TetrisSession::extract_figures(HGE*hge, std::vector<TetrominoBase*>&figures)
	{
		figures.clear(); //this array is a buffer, so it must be cleared anyway
		std::string response = "NO_RESPONSE"; //variable to check for function response, as it cannot be checked within the function
		std::vector<std::string> lines = read_figure_lines(); //buffering figures lines to read them next
		TetrominoBase* current = NULL; //TetrominoBase line-parse 
		for (int i = 0; i < lines.size(); i++)
		{
			//if any of lines buffered is non-empty kind
			if (lines[i] != "")
			{
				//split this non-empty line
				std::vector<std::string> posVector = StringExtensions::split(lines[i], StringExtensions::to_string(splitter));
				std::string strI = posVector[0];
				std::string strJ = posVector[1];
				std::string strType = posVector[2];
				std::string strLanded = posVector[3];
				std::string strColor = posVector[4];
				std::string imgPath = posVector[5];

				//parsing requires tetrominocolors struct to be defined
				int i = StringExtensions::int_parse(strI);
				int j = StringExtensions::int_parse(strJ);
				TetrominoTypes type = (TetrominoTypes)StringExtensions::int_parse(strType);
				bool landed = StringExtensions::int_parse(strLanded)==0 ? false : true;
				hgeU32 color = TetrominoColors::get_color_by_id((TetrominoColors::Colors)StringExtensions::int_parse(strColor));
				
				if(current==NULL)
				{
					switch(type)
					{
					case TetrominoTypes::I:
						current = new TetrominoI(i, j);
						break;
					case TetrominoTypes::J:
						current = new TetrominoJ(i, j);
						break;
					case TetrominoTypes::L:
						current = new TetrominoL(i, j);
						break;
					case TetrominoTypes::O:
						current = new TetrominoO(i, j);
						break;
					case TetrominoTypes::S:
						current = new TetrominoS(i, j);
						break;
					case TetrominoTypes::T:
						current = new TetrominoT(i, j);
						break;
					case TetrominoTypes::Z:
						current = new TetrominoZ(i, j);
						break;
					case TetrominoTypes::tetrominoUFO:
					default:
						current = new TetrominoO(i, j);
						break;
					}
					current->batch.squares.clear();//because it already goes with defaults
				}
				GameSquare gs;
				gs.pos = Position(i,j);
				gs.landed = landed;
				gs.graphics = *HGEQuadFactory::init_visual_square(hge, GameConstants::get_texture_path(), color);
				current->batch.squares.push_back(gs);
			}
			else
			{
			  if (current != NULL)//to prevent emptyline push_back-ing
			  {
				figures.push_back(current);
				current = NULL;
			  }
			}
		}
		return response;
	}
