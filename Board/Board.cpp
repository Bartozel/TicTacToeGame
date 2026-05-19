#include "Board.h"

#include <format>
#include <stdexcept>

Board::Board()
{
	_availableStones.reserve(BOARD_SIZE * BOARD_SIZE);

	InitializeState();
	InitializeStones();
}

std::vector<std::reference_wrapper<const Stone>> Board::GetStonesOnRow(size_t index) const
{
	return GetStones([&](size_t i) { return index; }, [&](size_t i) { return i; });
}

std::vector<std::reference_wrapper<const Stone>> Board::GetStonesOnColumn(size_t index) const
{
	return GetStones([&](size_t i) { return i; }, [&](size_t i) { return index; });
}

std::vector<std::reference_wrapper<const Stone>> Board::GetStonesOnPrimaryDiagonal() const
{
	return GetStones([&](size_t i) { return i; }, [&](size_t i) { return i; });
}

std::vector<std::reference_wrapper<const Stone>> Board::GetStonesOnSecondaryDiagonal() const
{
	return GetStones([&](size_t i) { return i; }, [&](size_t i) { return BOARD_SIZE - 1 - i; });
}

bool Board::HasAvailableStones() const
{
	return !_availableStones.empty();
}

const std::vector<Stone>& Board::AvailableStones() const
{
	return _availableStones;
}

Stone Board::WidrawStone(const std::string& stoneId)
{
	const auto it = std::ranges::find_if(
		_availableStones.begin(),
		_availableStones.end(),
		[&](const Stone& s) { return s.GetId() == stoneId; }
	);

	if (it == _availableStones.end())
		throw std::logic_error(std::format("Stone with id=[{}] is not available.", stoneId));

	auto res = std::move(*it);
	_availableStones.erase(it);

	return res;
}

void Board::PlaceStoneOnCell(int cellIndex, Stone&& stone)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			auto& cell = _state(i, j);
			if (cell.GetIndex() == cellIndex)
			{
				if (cell.HasStone())
					throw std::logic_error(std::format("Cell id=[{}] already contain a stone.", std::to_string(cellIndex)));

				cell.SetStone(std::move(stone));
				return;
			}
		}
	}
}

std::vector<int> Board::GetAvailableCellIds() const
{
	std::vector<int> result;
	result.reserve(BOARD_SIZE * BOARD_SIZE);

	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++)
			if (!_state(i, j).HasStone())
				result.push_back(_state(i, j).GetIndex());

	return result;
}

void Board::InitializeState()
{
	for (size_t i = 0; i < BOARD_SIZE; i++) {
		for (size_t j = 0; j < BOARD_SIZE; j++) {

			_state(i, j).SetIndex((i + 1) * 10 + j + 1);
		}
	}
}

void Board::InitializeStones()
{
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::Black, eSymbol::Square, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::Black, eSymbol::Square, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::Black, eSymbol::Circle, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::Black, eSymbol::Circle, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::White, eSymbol::Square, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::White, eSymbol::Square, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::White, eSymbol::Circle, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Circle, eStoneColor::White, eSymbol::Circle, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::Black, eSymbol::Square, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::Black, eSymbol::Square, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::Black, eSymbol::Circle, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::Black, eSymbol::Circle, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::White, eSymbol::Square, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::White, eSymbol::Square, eSymbolColor::Blue);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::White, eSymbol::Circle, eSymbolColor::Red);
	_availableStones.emplace_back(eOuterShape::Square, eStoneColor::White, eSymbol::Circle, eSymbolColor::Blue);
}

std::vector<std::reference_wrapper<const Stone>> Board::GetStones(
	const std::function<size_t(size_t)>& rowIterator,
	const std::function<size_t(size_t)>& columnIterator
) const
{
	std::vector<std::reference_wrapper<const Stone>> result;
	result.reserve(BOARD_SIZE);

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		const auto& cell = _state(rowIterator(i), columnIterator(i));
		if (cell.HasStone())
		{
			result.emplace_back(cell.GetStone().value());
		}
	}

	return result;
}
