#pragma once
#include "IPlayerLogic.h"
#include "Board/Board.h"
#include "StandardCommunicationWrapper.h"

class UserLogic : public IPlayerLogic
{
public:
	std::string PickStoneForSelection(const Board& vector) override;
	int PickCellForPlacement(const Board& board, const Stone& stone) override;

private :
	StandardCommunicationWrapper _comm;

};

