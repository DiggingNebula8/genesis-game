#include "GameMenu.h"

// Game Menu
GameMenu::GameMenu()
{

}

GameMenu::~GameMenu()
{

}


void GameMenu::Update()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				Quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	ImGui::PopStyleVar();
}

void GameMenu::DemoWindow()
{
	if (ImGuiDemoOpen)
	{ 
		ImGui::ShowDemoWindow(&ImGuiDemoOpen);
	}
}