#include "KeyValue.h"

KeyValue::KeyValue(std::string_view key, std::string_view value):
_key(key),
_value(value)
{
}

std::string_view KeyValue::GetKey() const
{
	return _key;
}

std::string_view KeyValue::GetValue() const
{
	return _value;
}
