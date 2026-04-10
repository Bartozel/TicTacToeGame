#pragma once
#include <memory>

#include "Board/Board.h"
#include "IPlayerLogic.h"

class Player
{
public:
	Player(int id, Board& board, std::unique_ptr<IPlayerLogic> logicModule);
	Stone SelectStone() const;
	size_t PlaceStone(Stone&& stone) const;

private:
	int _id;
	Board& _board;
	std::unique_ptr<IPlayerLogic> _logic;
};
