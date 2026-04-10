#pragma once
#include <functional>
#include <vector>
#include "Cell.h"
#include "Data/Matrix.h"
	
constexpr size_t BOARD_SIZE = 4;

class Board
{
public: 
	Board();

	std::vector<std::reference_wrapper<const Stone>> GetStonesOnRow(size_t index) const;
	std::vector<std::reference_wrapper<const Stone>> GetStonesOnColumn(size_t index) const;
	std::vector<std::reference_wrapper<const Stone>> GetStonesOnPrimaryDiagonal() const;
	std::vector<std::reference_wrapper<const Stone>> GetStonesOnSecondaryDiagonal() const;

	bool HasAvailableStones() const;
	const std::vector<Stone>& AvailableStones() const;
	Stone WidrawStone(const std::string& stoneId);
	void PlaceStoneOnCell(int cell_id, Stone&& stoneId);
	std::vector<int> GetAvailableCellIds() const;
	
private:
	SquareMatrix<Cell, BOARD_SIZE> _state;
	std::vector<Stone> _availableStones;

	void InitializeState();
	void InitializeStones();
	std::vector<std::reference_wrapper<const Stone>> GetStones(
		std::function<size_t(size_t)> rowIterator,
		std::function<size_t(size_t)> columnIterator
	) const;

};