#include <stdexcept>

#include "GameManager.h"
#include "Player.h"
#include "RandomLogic.h"
#include "UserLogic.h"
#include "StandardCommunicationWrapper.h"
#include "CommunicationTopics.h"
#include "Enum/eStartPlayer.h"

GameManager::GameManager():
	_stoneId(),
	_cellId(-1)
{
}

void GameManager::Start(const Setting& setting)
{
	Board board;
	StandardCommunicationWrapper comm;

	Player userPlayer(1, board, std::make_unique<UserLogic>());
	Player botPlayer(2, board, std::make_unique<RandomLogic>());

	bool botSelects = setting.GetStartPlayer() == eStartPlayer::Bot;
	bool winnerFound, hasStonesToPlay;

	while (true)
	{
		if (botSelects)
		{
			auto response = botPlayer.SelectStone();
			_stoneId = std::string(response.GetId());
			comm.Annonce({ KeyValue(RESPONSE_CHOSEN_STONE, _stoneId) });

			_cellId = userPlayer.PlaceStone(std::move(response));
		}
		else
		{
			auto response = userPlayer.SelectStone();

			_stoneId = std::string(response.GetId());
			_cellId = botPlayer.PlaceStone(std::move(response));
			comm.Annonce(
				{
					KeyValue(REQUEST_STONE_ID, _stoneId),
					KeyValue(REQUEST_CELL_ID, std::to_string(_cellId))
				});
		}

		winnerFound = CanFindSequence(board);
		hasStonesToPlay = board.HasAvailableStones();

		if (!winnerFound && hasStonesToPlay)
		{
			comm.Annonce({ KeyValue(RESPONSE_STATUS, RESPONSE_STATUS_VALUE_PLAYING) });
			botSelects = !botSelects;
		}
		else
		{
			break;
		}
	}

	auto gameStatus = GetGameStatus(winnerFound, hasStonesToPlay, botSelects);
	comm.Annonce({ KeyValue(RESPONSE_STATUS, gameStatus) });
}

bool GameManager::CanFindSequence(const Board& board)
{
	if (CheckRows(board))
	{
		return  true;
	}

	if (CheckColumns(board))
	{
		return true;
	}

	if (CheckDiagonals(board))
	{
		return true;
	}

	return false;
}

bool GameManager::CheckRows(const Board& board)
{
	return CheckStones([&board](int index)
		{
			return board.GetStonesOnRow(index);
		});
}

bool GameManager::CheckColumns(const Board& board)
{
	return CheckStones([&board](int index)
		{
			return board.GetStonesOnColumn(index);
		});
}

bool GameManager::CheckDiagonals(const Board& board)
{
	const auto& stones = board.GetStonesOnPrimaryDiagonal();
	if (stones.size() == BOARD_SIZE && CheckProperties(stones))
		return true;

	const auto& stones_2 = board.GetStonesOnSecondaryDiagonal();
	if (stones_2.size() == BOARD_SIZE && CheckProperties(stones_2))
		return true;

	return false;
}

bool GameManager::CheckStones(const std::function<std::vector<std::reference_wrapper<const Stone>>(int)>& delegate)
{
	bool res = false;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		const auto& stones = delegate(i);
		if (stones.size() != BOARD_SIZE) continue;

		if (CheckProperties(stones))
		{
			res = true;
			break;
		}
	}

	return res;
}

bool GameManager::CheckProperties(const std::vector<std::reference_wrapper<const Stone>>& stones)
{
	for (size_t i = 0; i < STONE_SIZE; i++)
	{
		for (size_t j = 0; j < STONE_SIZE; j++)
		{
			bool res = true;
			bool propertyValue = stones[0].get()(i, j);

			for (const auto& stone : stones)
			{
				if (stone.get()(i, j) != propertyValue)
				{
					res = false;
					break;
				}
			}

			if (res) return true;
		}
	}

	return false;
}

std::string_view GameManager::GetGameStatus(bool winnerFound, bool hasStonesToPlay, bool botSelects)
{
	if (winnerFound && botSelects)
	{
		return RESPONSE_STATUS_VALUE_PLAYER;
	}
	else if (winnerFound && !botSelects)
	{
		return RESPONSE_STATUS_VALUE_COMPUTER;
	}
	else if (!hasStonesToPlay)
	{
		return RESPONSE_STATUS_VALUE_NO;
	}
	else
	{
		throw std::logic_error("Invalid game state");
	}
}
