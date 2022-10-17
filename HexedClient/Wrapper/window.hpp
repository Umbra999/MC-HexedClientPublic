#pragma once
#include <windows.h>
#include <string>
#include <algorithm>

class window_t
{
public:
	window_t():
		hwnd_(0)
	{
	}

	window_t(HWND hwnd):
		hwnd_(hwnd)
	{
	}

	bool is_visible() const
	{
		return ::IsWindowVisible(hwnd_);
	}

	HWND native_handle() const
	{
		return hwnd_;
	}

	operator HWND() const
	{
		return hwnd_;
	}

	bool is_enabled() const
	{
		return IsWindowEnabled(hwnd_);
	}

	std::string get_text() const
	{
		int32_t text_len = GetWindowTextLengthA(hwnd_) + 1;
		std::string buffer(text_len , 0);
		GetWindowText(hwnd_, buffer.data(), text_len);
		return buffer;
	}

	void set_text(const std::string& text)
	{
		SetWindowTextA(hwnd_, text.c_str());
		RECT wnd_rect = get_client_rect();
		HDC hdc = GetDC(hwnd_);
		DrawText(hdc, text.c_str(), text.length(), &wnd_rect, DT_CALCRECT);
		ReleaseDC(hwnd_, hdc);
		resize(&wnd_rect);
	}

	void set_font(HFONT font)
	{
		SendMessage(hwnd_, WM_SETFONT, (WPARAM)font, 0);
	}

	RECT get_wnd_rect() const
	{
		RECT out;
		GetWindowRect(hwnd_, &out);
		return out;
	}

	RECT get_client_rect() const
	{
		RECT out;
		GetClientRect(hwnd_, &out);
		return out;
	}

	void resize(LPRECT rc)
	{
		SetWindowPos(hwnd_, 0, rc->left, rc->top, rc->right, rc->bottom, SWP_NOMOVE);
	}

	window_t get_owner() const
	{
		return GetWindow(hwnd_, GW_OWNER);
	}

	void app_command(uint32_t command)
	{
		SendMessage(hwnd_, WM_APPCOMMAND, 0, command * 65536);
	}

	void update()
	{
		UpdateWindow(hwnd_);
	}

	void invalidate()
	{
		InvalidateRect(hwnd_, 0, TRUE);
	}

	bool is_window()
	{
		return IsWindow(hwnd_);
	}

	void redraw()
	{
		RedrawWindow(hwnd_, 0, 0, RDW_UPDATENOW);
	}

	window_t get_parent() const
	{
		return GetParent(hwnd_);
	}
private:
	HWND hwnd_;
};
