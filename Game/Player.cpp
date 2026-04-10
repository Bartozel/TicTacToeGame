#include <memory>

#include "Player.h"

Player::Player(int id, Board& board, std::unique_ptr<IPlayerLogic> logicModule) :
	_id(id),
	_board(board),
	_logic(std::move(logicModule))
{}

Stone Player::SelectStone() const
{
	const auto& stoneId = _logic->PickStoneForSelection(_board);
	return _board.WidrawStone(stoneId);
}

size_t Player::PlaceStone(Stone&& stone) const
{
	size_t cellId = _logic->PickCellForPlacement(_board, stone);
	_board.PlaceStoneOnCell(cellId, std::move(stone));

	return cellId;
}
