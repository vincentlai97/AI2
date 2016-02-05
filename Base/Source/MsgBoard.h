#pragma once

#include <string>
#include <vector>
#include <array>
#include <map>

class MsgBoard
{
public:
	MsgBoard();
	~MsgBoard();

	std::array<bool, 3> msgboard;
	std::map<int, std::string> msgs;
};

