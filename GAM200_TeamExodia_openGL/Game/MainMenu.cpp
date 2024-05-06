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
#include "../Engine/Audio.h"

#include "../Game/Button.h"

#include "MainMenu.h"
#include "Fonts.h"
#include <imgui_impl_sdl.h>

GAM200::SoundEffect* Button1 = Engine::GetSFXManager().Load("assets/Sounds/SoundEffect/Button1.wav");
GAM200::SoundEffect* Button3 = Engine::GetSFXManager().Load("assets/Sounds/SoundEffect/Button3.wav");
GAM200::SoundEffect* audioPtr = Engine::GetSFXManager().Load("assets/Sounds/Theme/Maintheme_Reference.wav");


Main_menu::Main_menu()
{

}

void Main_menu::Load()
{
	//Example code - PLS DELETE THIS AFTER IMPLEMENTING YOUR OWN CODE!!!!!!
	AddGSComponent(new GAM200::GameObjectManager());


	mainmenu_background = Engine::Instance().GetTextureManager().Load("assets/Background/mainmenu_background.png");
	UpdateMenuTextColors();


	//BGM
	audioPtr->Play();

}

void Main_menu::UpdateMenuTextColors()
{
	uint32_t colors[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	colors[counter]    = 0x7EFACBFF;

	trash.reset	   (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", colors[0]));
	play.reset	   (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Play",		 colors[0]));
	howToPlay.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("How to play", colors[1]));
	setting.reset  (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Setting",	 colors[2]));
	exit.reset	   (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit",	     colors[3]));
}

void Main_menu::Update(double dt)
{
	//Example code - PLS DELETE THIS AFTER IMPLEMENTING YOUR OWN CODE!!!!!!
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);


	bool shouldUpdateColors = false;

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Down))
	{
		counter = (counter + 1) % 4;
		shouldUpdateColors = true;
		Button1->Play();
	}
	else if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Up))
	{
		counter = (counter - 1 + 4) % 4;
		shouldUpdateColors = true;
		Button1->Play();
	}

	if (shouldUpdateColors)
	{
		UpdateMenuTextColors();
	}



	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().ClearNextGameState();
	}

	//if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Enter))
	//{
	//	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
	//}


	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		switch (counter)
		{
		case 0:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
			Button3->Play();
			break;
		case 1:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::HowToPlay));
			Button3->Play();
			break;
		case 2:
			//Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Setting));
			break;
		case 3:
			Engine::GetGameStateManager().ClearNextGameState();
			Button3->Play();
			break;
		}
	}	

}

void Main_menu::Unload()
{
	//Unload Mode1
	audioPtr->Stop();

	//Unload Mode2


}

void Main_menu::Draw()
{
	Engine::GetWindow().Clear(0.2f, 0.4f, 0.7f, 1.0f);
	mainmenu_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0 ,0 }));
	//Example code - PLS DELETE THIS AFTER IMPLEMENTING YOUR OWN CODE!!!!!!
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

	trash	 ->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	play	 ->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x/2   + 220, (Engine::GetWindow().GetSize().y / 2 - 100)}));
	howToPlay->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 160) }));
	setting  ->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 220) }));
	exit     ->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 280) }));
}

void Main_menu::ImguiDraw()
{

}

void Main_menu::HandleEvent(SDL_Event& event)
{

}