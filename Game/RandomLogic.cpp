#include "RandomLogic.h"

RandomLogic::RandomLogic() :
	_rd(),
	_engine(_rd())
{
}

std::string RandomLogic::PickStoneForSelection(const Board& board)
{
	size_t count = board.AvailableStones().size();
	return board.AvailableStones()[GetRandomIndex(count)].GetId();
}

int RandomLogic::PickCellForPlacement(const Board& board, const Stone& stone)
{
	auto availableCells = board.GetAvailableCellIds();
	size_t count = availableCells.size();

	return availableCells[GetRandomIndex(count)];
}

int RandomLogic::GetRandomIndex(size_t vectorSize) const
{
	int max = static_cast<int>(vectorSize - 1);

	std::uniform_int_distribution<int> dist(0, max);
	return dist(_engine);
}