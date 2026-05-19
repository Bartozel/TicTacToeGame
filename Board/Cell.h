#pragma once
#include <optional>
#include <iostream>

#include "Stone.h"

class Cell
{
public:	
	Cell();
	Cell(const Cell&) { std::cout << "COPY ctor\n"; }

	void SetStone(Stone&& stone);
	const std::optional<Stone>& GetStone() const;

	void SetIndex(int index);
	int GetIndex() const;

	bool HasStone() const;

private:
	int _index;
	std::optional<Stone> _stone;
};

