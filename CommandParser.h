#pragma once
#include <vector>
#include "Data/KeyValue.h"

class CommandParser
{
public:
	std::string Serialize(std::initializer_list<KeyValue> initializers) const;
	std::vector<KeyValue> Deserialize(const std::string& input) const;

private:
	std::string ExtractString(const std::string& input, size_t& pos) const;
};

