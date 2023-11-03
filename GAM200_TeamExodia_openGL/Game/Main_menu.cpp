/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Main_menu.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    November 2, 2023
*/


#include "Main_menu.h"
#include "Fonts.h"

Main_menu::Main_menu()
{

}

void Main_menu::Load()
{
	main_title = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("CS230 Engint Test", 0xFFFFFFFF);
	UpdateMenuTextColors();
}

void Main_menu::UpdateMenuTextColors()
{
	uint32_t colors[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	colors[counter] = 0x7EFACBFF;

	side_scroller = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Side Scroller", colors[0]);
	Space_shotter = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Space Shotter", colors[1]);
	exit = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Exit", colors[2]);
}

void Main_menu::Update(double dt)
{
	bool shouldUpdateColors = false;

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Down))
	{
		counter = (counter + 1) % 3;
		shouldUpdateColors = true;
	}
	else if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Up))
	{
		counter = (counter - 1 + 3) % 3;
		shouldUpdateColors = true;
	}

	if (shouldUpdateColors)
	{
		UpdateMenuTextColors();
	}

	if (Engine::GetInput().keyDown(GAM200::Input::Keys::Enter))
	{
		switch (counter)
		{
		case 0:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
			break;
		case 1:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
			break;
		case 2:
			Engine::GetGameStateManager().ClearNextGameState();
			break;
		}
	}
}

void Main_menu::Unload()
{
	//Unload Mode1

	//Unload Mode2
}

void Main_menu::Draw()
{
	//Make a title that is in a third color with a nice background color or texture. 
	Engine::GetWindow().Clear(0.0, 0.0, 0.0, 1.0);

	//main_title.Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 400), (Engine::GetWindow().GetSize().y - 400) }) * CS230::ScaleMatrix({2, 2}));
	main_title->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 100) }));
	side_scroller->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 300) }));
	Space_shotter->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 400) }));
	exit->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 500) }));
}

void Main_menu::ImguiDraw()
{
}

void Main_menu::HandleEvent(SDL_Event& event)
{
}
