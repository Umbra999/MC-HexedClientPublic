#pragma once

class Handler
{
private:
	static int CurrentTick;

public:
	static void OnTick();
	static void DoKeyBinds();
};