/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Win.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    December 15, 2023
*/

#include "Win.h"

#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/Audio.h"

Win::Win()
{

}

void Win::Load()
{
	GAM200::SoundEffect::GameClear().play();

	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Win! Press Esc to go back", 0xFFFFFFFF));
}

void Win::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
	}
}

void Win::Unload()
{
	message.reset();
}

void Win::Draw()
{
	//Engine::GetWindow().Clear(0x000000FF);
	//message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
	victory.Draw(0, 0, 1280, 720);
}

void Win::ImguiDraw()
{

}

void Win::HandleEvent(SDL_Event& event)
{

}
