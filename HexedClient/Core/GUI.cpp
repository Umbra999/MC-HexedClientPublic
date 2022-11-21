#include "GUI.hpp"
#include <vector>
#include <gl/GL.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include "Settings.hpp"
#include "../Wrapper/Logger.hpp"
#include "../Wrapper/ClientConsole.hpp"
#include "../Core/Modules/NameSpoofer.hpp"

#pragma comment(lib, "opengl32.lib")

WNDPROC originalWNDPROC;

bool GUI::IsInitialized = false;
bool GUI::Enabled = false;

void GUI::Create()
{
	HWND minecraftWindow = FindWindowA("LWJGL", nullptr);

	originalWNDPROC = (WNDPROC)SetWindowLongPtrW(minecraftWindow, GWLP_WNDPROC, (LONG_PTR)patchedWNDPROC);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(minecraftWindow);
	ImGui_ImplOpenGL3_Init();

	auto& style = ImGui::GetStyle();
	style.FrameRounding = 4.0f;
	style.WindowBorderSize = 2.0f;
	style.PopupBorderSize = 0.0f;
	style.GrabRounding = 4.0f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.73f, 0.75f, 0.74f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.09f, 0.87f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.34f, 0, 0.6f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.34f, 0, 0.6f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.54f, 0, 0.9f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.34f, 0, 0.6f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.34f, 0, 0.6f, 0.67f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.34f, 0, 0.6f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.34f, 0, 0.6f, 0.67f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.34f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0, 0.6f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0, 0.9f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.34f, 0, 0.6f, 0.65f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.54f, 0, 0.9f, 0.65f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.34f, 0, 0.6f, 0.50f);
	colors[ImGuiCol_Header] = ImVec4(0.34f, 0, 0.6f, 0.54f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.54f, 0, 0.9f, 0.65f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.34f, 0, 0.6f, 0.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.34f, 0, 0.6f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0, 0.9f, 0.54f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.34f, 0, 0.6f, 0.54f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.34f, 0, 0.6f, 0.54f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0, 0.9f, 0.66f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.34f, 0, 0.6f, 0.66f);
	colors[ImGuiCol_Tab] = ImVec4(0.34f, 0, 0.6f, 0.54f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0, 0.9f, 0.66f);
	colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0, 0.6f, 0.66f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.34f, 0, 0.6f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.54f, 0, 0.9f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.34f, 0, 0.6f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.54f, 0, 0.9f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    IsInitialized = true;
	Enabled = true;
}

void GUI::Delete()
{
	HWND minecraftWindow = FindWindowA("LWJGL", nullptr);
    Enabled = false;
    IsInitialized = false;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
	SetWindowLongPtrW(minecraftWindow, GWLP_WNDPROC, (LONG_PTR)originalWNDPROC);
}

void GUI::RenderMain()
{
	ImGui::Begin("H E X E D");

	if (ImGui::CollapsingHeader("MOVEMENT"))
	{
		ImGui::Checkbox("Auto Sprint", &Settings::AutoSprint);
	}

	if (ImGui::CollapsingHeader("COMBAT"))
	{
		ImGui::Checkbox("Autoclicker", &Settings::Autoclicker);
		if (Settings::Autoclicker)
		{
			ImGui::SliderInt("CPS", &Settings::AutoclickerCount, 1, 20);
		}

		ImGui::Checkbox("No Hit Delay", &Settings::NoHitDelay);

		ImGui::Checkbox("No Build Delay", &Settings::NoBuildDelay);

		ImGui::Checkbox("Hitbox Extender", &Settings::HitBoxExtender);
		if (Settings::HitBoxExtender)
		{
			ImGui::SliderFloat("Width", &Settings::HitBoxWidth, 0, 3);
			ImGui::SliderFloat("Height", &Settings::HitBoxHeight, 0, 3);
		}
	}

	if (ImGui::CollapsingHeader("ESP"))
	{
		ImGui::Checkbox("Player", &Settings::PlayerESP);
		ImGui::Checkbox("Chest", &Settings::ChestESP);
	}

	if (ImGui::CollapsingHeader("PROTECTION"))
	{
		ImGui::Checkbox("Anti Bot", &Settings::AntiBot);
		if (Settings::AntiBot)
		{
			ImGui::Checkbox("Name Flag", &Settings::AntiBotNameFlag);
			ImGui::Checkbox("Ping Flag", &Settings::AntiBotPingFlag);
			ImGui::Checkbox("Risky Ping Flag", &Settings::AntiBotRiskyPingFlag);
			ImGui::Checkbox("UUID Flag", &Settings::AntiBotUUIDFlag);
		}
	}

	if (ImGui::CollapsingHeader("VISUAL"))
	{
		ImGui::Checkbox("Frame Spoof", &Settings::FrameSpoof);
		if (Settings::FrameSpoof)
		{
			ImGui::SliderInt("Frames", &Settings::FrameSpoofValue, -1337, 1337);
		}

		ImGui::Checkbox("Ping Spoof", &Settings::PingSpoof);
		if (Settings::PingSpoof)
		{
			ImGui::SliderInt("Latency", &Settings::PingSpoofValue, -1337, 1337);
		}

		ImGui::Checkbox("No Fire", &Settings::NoFire);
	}

	if (ImGui::CollapsingHeader("HYPIXEL"))
	{
		ImGui::Checkbox("Murder Expose", &Settings::MurderExpose);
	}

	if (ImGui::CollapsingHeader("MISC"))
	{
		if (ImGui::Checkbox("Name Spoof", &Settings::NameSpoof)) NameSpoofer::Toggle();
		if (Settings::NameSpoof)
		{
			ImGui::Text(Settings::NameSpoofValue.c_str());
		}

		if (ImGui::Button("Uninject")) Settings::ShouldUninject = true;
	}

	ImGui::End();
}

void GUI::RenderConsole()
{
	ImGui::SetNextWindowSize(ImVec2(400, 300));
	ImGui::SetNextWindowBgAlpha(0.25f);
	bool* debug_open = (bool*)0;
	if (ImGui::Begin("Debug", debug_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::BeginChild("scrollable", ImVec2(-FLT_MIN, FLT_MIN), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

		std::vector<std::string> logs = ClientConsole::GetLogs();

		int size = logs.size();
		for (int i = size - 1; i >= 0; i--)
		{
			ImGui::TextWrapped(logs[i].c_str());
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

void GUI::RenderInfo()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.25f);
	bool* info_open = (bool*)0;
	ImGui::Begin("Info", info_open, window_flags);
	ImGui::Text(("FPS: " + std::to_string(Settings::DebugFPS) + " Ping: " + std::to_string(Settings::DebugPing)).c_str());

	ImGui::End();
}

void GUI::RenderESP()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(Settings::DebugWidth, Settings::DebugHeight));
	ImGui::Begin("ESP", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

	auto pDrawList = ImGui::GetWindowDrawList();

	if (Settings::PlayerESP)
	{
		/*pDrawList->AddRect(ImVec2(10, 10), ImVec2(100, 100), ImColor(255, 0, 0));
		pDrawList->AddText(ImVec2(10, 10), ImColor(255, 0, 0), "test");*/
	}

	if (Settings::ChestESP)
	{

	}

	ImGui::End();
}

void GUI::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Enabled)
	{
		RenderMain();
		RenderInfo();
		RenderConsole();
	}

	RenderESP();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::OnSwapBuffers(HDC hdc)
{
    if (!IsInitialized)
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glViewport(0, 0, viewport[2], viewport[3]);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);

        Create();
    }
	else if (Settings::CanRenderMenu) Render();
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GUI::patchedWNDPROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!IsInitialized) return CallWindowProcA(originalWNDPROC, hWnd, msg, wParam, lParam);

	if (msg == WM_KEYDOWN && wParam == VK_F12) Enabled = !Enabled;

	if (Enabled && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;

	return CallWindowProcA(originalWNDPROC, hWnd, msg, wParam, lParam);
}