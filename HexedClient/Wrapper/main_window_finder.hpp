#pragma once
#include <cstdint>
#include <windows.h>
#include "window.hpp"

class main_window_finder_t
{
public:
	main_window_finder_t():
		best_handle_(0),
		process_id_(0)
	{
	}

	window_t find_main_window(uint32_t process_id)
	{
		best_handle_ = 0;
		process_id_ = process_id;

		EnumWindows(enum_windows_thunk, (LPARAM)this);

		return best_handle_;
	}

private:
	static BOOL CALLBACK enum_windows_thunk(HWND hwnd, LPARAM lParam)
	{
		main_window_finder_t* wnd_finder((main_window_finder_t*)lParam);
		return wnd_finder->enum_windows(hwnd);
	}
	bool enum_windows(window_t window)
	{
		DWORD pid;
		GetWindowThreadProcessId(window, &pid);

		if (pid != process_id_ || !is_main_window(window))
		{
			return true;
		}

		best_handle_ = window;
		return false;
	}

	bool is_main_window(window_t window)
	{
		if (!window.get_owner() && window.is_visible())
		{
			return true;
		}
		return false;
	}

	window_t best_handle_;
	uint32_t process_id_;
};
