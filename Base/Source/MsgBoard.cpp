#include "MsgBoard.h"

MsgBoard::MsgBoard()
{
	msgboard.fill(false);

	msgs.insert(std::pair<int, std::string>{ 0, "[ARCHER] to [KNIGHT]: Protect me!" });
	msgs.insert(std::pair<int, std::string>{ 1, "[HEALER] to [KNIGHT]: Protect me!" });
	msgs.insert(std::pair<int, std::string>{ 2, "[KNIGHT] to [HEALER]: I'm hurt!" });
}

MsgBoard::~MsgBoard()
{
}