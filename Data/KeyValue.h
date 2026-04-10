#pragma once
#include <string>

struct KeyValue
{

public:
	KeyValue(std::string_view key, std::string_view value);

	std::string_view GetKey() const;
	std::string_view GetValue() const;

private:
	std::string  _key;
	std::string  _value;
};