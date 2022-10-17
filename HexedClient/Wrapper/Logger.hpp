#pragma once
#pragma warning(disable : 4996)

#include <string>
#include <iostream>
#include <windows.h>

struct Logger
{
	static void Log(std::string msg)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 3);

		time_t currentTime;
		struct tm* localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;

		msg = "[" + std::to_string(Hour) + ":" + std::to_string(Min) + "]" + " [Hexed] " + msg + "\n";
		std::cout << msg;
	}

	static void LogWarning(std::string msg)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 14);

		time_t currentTime;
		struct tm* localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;

		msg = "[" + std::to_string(Hour) + ":" + std::to_string(Min) + "]" + " [Hexed] " + msg + "\n";
		std::cout << msg;
	}

	static void LogError(std::string msg)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 4);

		time_t currentTime;
		struct tm* localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;

		msg = "[" + std::to_string(Hour) + ":" + std::to_string(Min) + "]" + " [Hexed] " + msg + "\n";
		std::cout << msg;
	}

	static void LogDebug(std::string msg)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 8);

		time_t currentTime;
		struct tm* localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;

		msg = "[" + std::to_string(Hour) + ":" + std::to_string(Min) + "]" + " [Hexed] " + msg + "\n";
		std::cout << msg;
	}
};

