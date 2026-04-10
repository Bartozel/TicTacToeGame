#pragma once
#include <random>
#include <string>
#include "IPlayerLogic.h"

class RandomLogic : public IPlayerLogic
{
public:
	RandomLogic();

	std::string PickStoneForSelection(const Board& vector) override;
	int PickCellForPlacement(const Board& board, const Stone& stone) override;

private:
	int GetRandomIndex(size_t vectorSize) const;

	std::random_device _rd;
	mutable std::mt19937 _engine;
};

