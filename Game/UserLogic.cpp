#include <stdexcept>

#include "UserLogic.h"
#include "CommunicationTopics.h"

std::string UserLogic::PickStoneForSelection(const Board& vector) 
{
	auto request = _comm.GetMessage();

	if (
		request.empty() ||
		request.size() > 1
		)		
		throw std::runtime_error("Invalid request");
	
	const auto& kv = request[0];
	const auto& key = kv.GetKey();

	if (key != RESPONSE_CHOSEN_STONE)
		throw std::logic_error("Invalid response type");

	return std::string(kv.GetValue());
}

int UserLogic::PickCellForPlacement(const Board& board, const Stone& stone)
{
	auto request = _comm.GetMessage();

	if (request.size() != 2)
		throw std::runtime_error("Invalid request");

	std::string_view stoneId, cellId;

	for (const auto& kv : request)
	{
		const auto& key = kv.GetKey();
		if (key == REQUEST_STONE_ID)
		{
			stoneId = kv.GetValue();
		}
		else if (key == REQUEST_CELL_ID)
		{
			cellId = kv.GetValue();
		}
		else
		{
			throw std::logic_error("Invalid response type");
		}
	}

	if (stoneId != stone.GetId())
		throw std::logic_error("Invalid stone id");

	try
	{
		return std::stoi(cellId.data());
	}
	catch (const std::exception&)
	{
		throw std::logic_error("Invalid cell id, couldn't convert");
	}
}
