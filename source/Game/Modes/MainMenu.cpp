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


#include "Engine/Audio.h"

#include "Engine/IfWantShader.h"

#include "Game/Objects/Button.h"
#include "Game/Fonts.h"

#include "MainMenu.h"

#include <backends/imgui_impl_sdl2.h>


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
    if (!Engine::GetAudioManager().IsMusicPlaying(GAM200::AudioID::MainMenu_BGM))
    {
        Engine::GetAudioManager().PlayMusic(GAM200::AudioID::MainMenu_BGM);
    } 
	Engine::GetAudioManager().StopMusic(GAM200::AudioID::Game_BGM);
	// GAM200::SoundEffect::Game_BGM().stopAll();
	
}

void Main_menu::UpdateMenuTextColors()
{
	uint32_t colors[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	colors[counter] = 0x7EFACBFF;

#if IfWantShader


#else
	trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", colors[0]));
	play.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Play", colors[0]));
	howToPlay.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("How to play", colors[1]));
	setting.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Setting", colors[2]));
	exit.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", colors[3]));
#endif

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
        Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_1);
    }
	else if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Up))
	{
		counter = (counter - 1 + 4) % 4;
		shouldUpdateColors = true;
        Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_1);
    }

	if (shouldUpdateColors)
	{
		UpdateMenuTextColors();
	}



	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().ClearNextGameState();
	}



	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		switch (counter)
		{
		case 0:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
            Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_3);
            break;
		case 1:

			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::HowToPlay));
            Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_3);		
			break;
		case 2:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Setting));
            Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_3);		
			break;
		case 3:
			Engine::GetGameStateManager().ClearNextGameState();
            Engine::GetAudioManager().PlaySound(GAM200::AudioID::Button_3);
            break;
		}
	}

}

void Main_menu::Unload()
{
	//Unload Mode1

	//Unload Mode2
	GetGSComponent<GAM200::GameObjectManager>()->Unload();

}

void Main_menu::Draw()
{
	Engine::GetWindow().Clear(0.2f, 0.4f, 0.7f, 1.0f);
	mainmenu_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0 ,0 }));


#if !IfWantShader
	play->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 100) }));
	howToPlay->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 160) }));
	setting->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 220) }));
	exit->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 280) }));
#else
	Math::vec2 color = counter == 0 ? Math::vec2{ 255,0 } : Math::vec2{ 0,0 };
    ShaderDrawing::ShaderDraw::setFont("assets/font/Eina01-Bold.ttf");
	ShaderDrawing::draw_text("Play", Engine::GetWindow().GetSize().x - 180 ,       Engine::GetWindow().GetSize().y / 2 - 150, 50, color.x, color.y, 0);
	color = counter == 1 ? Math::vec2{ 255,0 } : Math::vec2{ 0,0 };
	ShaderDrawing::draw_text("How to play", Engine::GetWindow().GetSize().x - 180, Engine::GetWindow().GetSize().y / 2 - 210, 50, color.x, color.y, 0);
	color = counter == 2 ? Math::vec2{ 255,0 } : Math::vec2{ 0,0 };

	ShaderDrawing::draw_text("Setting", Engine::GetWindow().GetSize().x - 180, Engine::GetWindow().GetSize().y / 2 - 270, 50, color.x, color.y, 0);
	color = counter == 3 ? Math::vec2{ 255,0 } : Math::vec2{ 0,0 };
	ShaderDrawing::draw_text("Exit", Engine::GetWindow().GetSize().x - 180,		 Engine::GetWindow().GetSize().y / 2 - 330, 50, color.x, color.y, 0);

#endif
}

void Main_menu::ImguiDraw()
{

}

void Main_menu::HandleEvent(SDL_Event& event)
{

}