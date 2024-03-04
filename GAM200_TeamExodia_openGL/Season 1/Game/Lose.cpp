/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Lose.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    December	15, 2023
*/

#include "Lose.h"

#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/Audio.h"

Lose::Lose()
{

}

void Lose::Load()
{
	GAM200::SoundEffect::GameOver().play();

	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Lose... Press Esc to go back", 0xFFFFFFFF));
}

void Lose::Update(double dt)
{


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
	}
}

void Lose::Unload()
{
	message.reset();
}

void Lose::Draw()
{
	defeat.Draw(0, 0, 1280, 720);
	//Engine::GetWindow().Clear(0x000000FF);

	//message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
}

void Lose::ImguiDraw()
{

}

void Lose::HandleEvent(SDL_Event& event)
{

}
