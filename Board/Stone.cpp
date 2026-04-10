#include "Stone.h"

Stone::Stone(eOuterShape outerShape, eStoneColor stoneColor, eSymbol symbol, eSymbolColor symbolColor):
_id(4, '0')
{
	_innerState(0, 0) = static_cast<bool>(outerShape);
	_innerState(0, 1) = static_cast<bool>(stoneColor);
	_innerState(1, 0) = static_cast<bool>(symbol);
	_innerState(1, 1) = static_cast<bool>(symbolColor);

	_id[0] = _innerState(0, 0) ? '1' : '0';
	_id[1] = _innerState(0, 1) ? '1' : '0';
	_id[2] = _innerState(1, 0) ? '1' : '0';
	_id[3] = _innerState(1, 1) ? '1' : '0';
}

eOuterShape Stone::GetOuterShape() const
{
	return static_cast<eOuterShape>(_innerState(0, 0));
}

eStoneColor Stone::GetStoneColor() const
{
	return static_cast<eStoneColor>(_innerState(0, 1));
}

eSymbol Stone::GetSymbol() const
{
	return static_cast<eSymbol>(_innerState(1, 0));
}

eSymbolColor Stone::GetSymbolColor() const
{
	return static_cast<eSymbolColor>(_innerState(1, 1));
}

const std::string& Stone::GetId() const
{
	return _id;
}

bool Stone::operator()(size_t row, size_t col) const
{
	return _innerState(row, col);
}

