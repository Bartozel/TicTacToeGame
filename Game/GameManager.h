#pragma once
#include <functional>
#include <string>

#include "Player.h"
#include "Data/Setting.h"
#include "Board/Board.h"

class StandardCommunicationWrapper;

class GameManager
{
public:
	GameManager();

	void Start(const Setting& setting);
	void Stop();

private:
	bool CanFindSequence(const Board& board);
	bool CheckRows(const Board& board);
	bool CheckColumns(const Board& board);
	bool CheckDiagonals(const Board& board);
	bool CheckStones(const std::function<std::vector<std::reference_wrapper<const Stone>>(int)>& delegate);
	bool CheckProperties(const std::vector<std::reference_wrapper<const Stone>>& stones);
	std::string_view GetGameStatus(bool winnerFound, bool hasStonesToPlay, bool botSelects);

	std::string _stoneId;
	int _cellId;
};

