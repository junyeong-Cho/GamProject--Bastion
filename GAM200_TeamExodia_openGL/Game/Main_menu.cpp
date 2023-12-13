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

#include "../Engine/Audio.h"


#include "Main_menu.h"
#include "Fonts.h"
#include <imgui_impl_sdl.h>


Main_menu::Main_menu()
{

}

void Main_menu::Load()
{
	//main_title.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("GAM200 Team Exodia", 0xFFFFFFFF));
	UpdateMenuTextColors();

	AddGSComponent(new GAM200::MusicEffect());

	//GetGSComponent<GAM200::MusicEffect>()->LoadFile("assets/Sounds/Theme/example_music.ogg");

	GAM200::SoundEffect::MainMenu_BGM().loopplay();
}

void Main_menu::UpdateMenuTextColors()
{
	uint32_t colors[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	colors[counter] = 0x7EFACBFF;

	//start.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Start", colors[0]));
	//gamePlay_Editor.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Game play editor", colors[1]));
	//howToPlay.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("How to play", colors[2]));
    //exit.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", colors[3]));
	
}

void Main_menu::Update(double dt)
{
	GetGSComponent<GAM200::MusicEffect>()->Play(0);


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

	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		switch (counter)
		{
		case 0:
			//GetGSComponent<GAM200::MusicEffect>()->Stop();
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
			break;
		case 1:
			//GetGSComponent<GAM200::MusicEffect>()->Stop();
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

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().ClearNextGameState();
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
	//Engine::GetWindow().Clear(0.0, 0.0, 0.0, 1.0);

	//Engine::GetWindow().Clear(0x000000FF);

	//main_title.Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 400), (Engine::GetWindow().GetSize().y - 400) }) * CS230::ScaleMatrix({2, 2}));
	//main_title->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 50) }));
	//start->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 150) }));
	//gamePlay_Editor->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 250) }));
	//howToPlay->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 350) }));
	//exit->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 450) }));

	switch (counter)
	{
	case 0:
		play.Draw(0, 0, 1280, 720);
		break;
	case 1:
		editor.Draw(0, 0, 1280, 720);
		break;
	case 2:
		howtoplay.Draw(0, 0, 1280, 720);
		break;
	case 3:
		exit.Draw(0, 0, 1280, 720);
		break;
	}


}

void Main_menu::ImguiDraw()
{
		//ImGui::Begin("Music Info");
		//{
		//	float musicVolume = (GetGSComponent<GAM200::SoundEffect>()->GetBGMVolume());

		//	if (ImGui::SliderFloat("Max Volume", &musicVolume, 0.0f, 50.0f, "%.0f"))
		//	{
		//		GetGSComponent<GAM200::SoundEffect>()->SeBGMVolume(musicVolume);
		//	}
		//}
		//ImGui::End();
}

void Main_menu::HandleEvent(SDL_Event& event)
{
}
