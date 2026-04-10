#pragma once
#include <string>
#include "Board/Board.h"
#include "Board/Stone.h"

class IPlayerLogic
{
public:
	virtual ~IPlayerLogic() = default;
	virtual std::string PickStoneForSelection(const Board& vector) = 0;
	virtual int PickCellForPlacement(const Board& board, const Stone& stone) = 0;
};