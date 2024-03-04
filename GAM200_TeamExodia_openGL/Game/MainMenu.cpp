/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Main_menu.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October		10, 2023
Updated:    March		 4, 2023
*/

#include "../Engine/Audio.h"
#include "../Engine/Engine.h"


#include "MainMenu.h"
#include "Fonts.h"
#include <imgui_impl_sdl.h>


Main_menu::Main_menu()
{

}

void Main_menu::Load()
{
	main_title.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("They are season 2", 0xFFFFFFFF));
}

void Main_menu::UpdateMenuTextColors()
{
	uint32_t colors[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	colors[counter]    = 0x7EFACBFF;
}

void Main_menu::Update(double dt)
{


	bool shouldUpdateColors = false;

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Down))
	{
		counter = (counter + 1) % 4;
		shouldUpdateColors = true;
	}
	else if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Up))
	{
		counter = (counter - 1 + 4) % 4;
		shouldUpdateColors = true;
	}

	if (shouldUpdateColors)
	{
		UpdateMenuTextColors();
	}



	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().ClearNextGameState();
	}

	//State change
	/*
	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		GAM200::SoundEffect::Select_MainMenu().play();

		switch (counter)
		{
		case 0:
			//GetGSComponent<GAM200::MusicEffect>()->Stop();
			GAM200::SoundEffect::MainMenu_BGM().stopAll();
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
			break;
		case 1:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::GamePlayEditior));
			break;
		case 2:
			//GetGSComponent<GAM200::MusicEffect>()->Stop();
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::HowToPlay));
			break;
		case 3:
			Engine::GetGameStateManager().ClearNextGameState();
			break;
		}
	}	
	*/

}

void Main_menu::Unload()
{
	//Unload Mode1

	//Unload Mode2
}

void Main_menu::Draw()
{
	Engine::GetWindow().Clear(0.2, 0.4, 0.7, 1.0);

	main_title->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 50) }));

	
}

void Main_menu::ImguiDraw()
{

}

void Main_menu::HandleEvent(SDL_Event& event)
{

}
