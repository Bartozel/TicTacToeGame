#include "StandardCommunicationWrapper.h"

#include <iostream>

void StandardCommunicationWrapper::Annonce(std::initializer_list<KeyValue> kvList) const
{
	const auto command = _parser.Serialize(kvList);
	std::cout << command << '\n';
}

std::vector<KeyValue> StandardCommunicationWrapper::GetMessage() const
{
	std::string input;
	std::getline(std::cin, input);

	return _parser.Deserialize(input);
}
