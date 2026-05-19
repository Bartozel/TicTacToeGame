#pragma once
#include <string>
#include <iostream>

#include "Data/SquareMatrix.h"
#include "Enum/eStoneColor.h"
#include "Enum/eSymbol.h"
#include "Enum/eSymbolColor.h"
#include "Enum/eOuterShape.h"

constexpr std::size_t STONE_SIZE = 2;

class Stone
{
public:
	Stone(eOuterShape outerShape, eStoneColor stoneColor, eSymbol symbol, eSymbolColor symbolColor);
	Stone(const Stone&) { std::cout << "COPY ctor\n"; }

	eOuterShape GetOuterShape() const;
	eStoneColor GetStoneColor() const;
	eSymbol GetSymbol() const;
	eSymbolColor GetSymbolColor() const;

	const std::string& GetId() const;

	bool operator()(size_t row , size_t col) const;

private:
	SquareMatrix<bool, STONE_SIZE> _innerState;

	std::string _id;
};

