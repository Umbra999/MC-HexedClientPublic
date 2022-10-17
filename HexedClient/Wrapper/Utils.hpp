#pragma once
#include <string>
#include <iostream>

class Utils
{
public:
    static std::string RandomString(const int);
    static std::string time_to_string(const char*, tm*);
};