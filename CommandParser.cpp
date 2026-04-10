#include "CommandParser.h"
#include <sstream>

std::string CommandParser::Serialize(std::initializer_list<KeyValue> initializers) const
{
    std::ostringstream oss;
    oss << "{";

    auto it = initializers.begin();
    while (it != initializers.end())
    {
        oss << "\"" << it->GetKey() << "\":\"" << it->GetValue() << "\"";

        if (++it != initializers.end())
            oss << ", ";
    }

    oss << "}";
    return oss.str();
}

std::vector<KeyValue> CommandParser::Deserialize(const std::string& input) const
{
    std::vector<KeyValue> result;
    size_t pos = 0;

    pos = input.find('{', pos);
    if (pos == std::string::npos)
        return result;

    pos++;

    while (pos < input.size())
    {
        while (pos < input.size() && (std::isspace(static_cast<unsigned char>(input[pos])) || input[pos] == ','))
            pos++;

        if (pos >= input.size() || input[pos] == '}')
            break;

        std::string key = ExtractString(input, pos);
        if (key.empty())
            break;

        while (pos < input.size() && (std::isspace(static_cast<unsigned char>(input[pos])) || input[pos] == ':'))
            pos++;

        std::string value = ExtractString(input, pos);

        result.emplace_back(key, value);
    }

    return result;
}

std::string CommandParser::ExtractString(const std::string& input, size_t& pos) const
{
    pos = input.find('"', pos);
    if (pos == std::string::npos)
        return {};

    pos++;
    std::ostringstream oss;

    while (pos < input.size() && input[pos] != '"')
    {
        if (input[pos] == '\\' && pos + 1 < input.size())
        {
            pos++;
            switch (input[pos])
            {
            case '"':  oss << '"';  break;
            case '\\': oss << '\\'; break;
            case 'n':  oss << '\n'; break;
            case 'r':  oss << '\r'; break;
            case 't':  oss << '\t'; break;
            default:   oss << input[pos]; break;
            }
        }
        else
        {
            oss << input[pos];
        }
        pos++;
    }

    pos++;
    return oss.str();
}
