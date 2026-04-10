#pragma once
#include <vector>

#include "CommandParser.h"
#include "Data/KeyValue.h"

class StandardCommunicationWrapper
{
public:

	void Annonce(std::initializer_list<KeyValue> kvList) const;
	std::vector<KeyValue> GetMessage() const;

private:
	CommandParser _parser;

};

