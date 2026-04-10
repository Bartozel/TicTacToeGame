#include "Cell.h"

Cell::Cell() :
_index(0)
{
}

void Cell::SetStone(Stone&& stone)
{
	_stone = stone;
}

const std::optional<Stone>& Cell::GetStone() const
{
	return _stone;
}

void Cell::SetIndex(int index)
{
	_index = index;
}

int Cell::GetIndex() const
{
	return _index;
}

bool Cell::HasStone() const
{
	return _stone.has_value();
}
