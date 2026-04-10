#pragma once
#include <optional>

#include "Stone.h"

class Cell
{
public:	
	Cell();

	void SetStone(Stone&& stone);
	const std::optional<Stone>& GetStone() const;

	void SetIndex(int index);
	int GetIndex() const;

	bool HasStone() const;

private:
	int _index;
	std::optional<Stone> _stone;
};

