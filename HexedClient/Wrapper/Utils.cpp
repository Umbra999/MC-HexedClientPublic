#include "Utils.hpp"
#include <vector>

std::string Utils::RandomString(const int len)
{
    static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string Utils::time_to_string(const char* format, tm* time)
{
    std::vector<char> buf(100, '\0');
    buf.resize(std::strftime(buf.data(), buf.size(), format, time));
    return std::string(buf.begin(), buf.end());
}