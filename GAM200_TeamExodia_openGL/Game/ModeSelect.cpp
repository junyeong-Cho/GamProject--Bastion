/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ModeSelect.cpp
Project:    GAM200 Engine
Author:
Created:    November 13, 2023
Updated:    November 13, 2023
*/


#include "ModeSelect.h"

#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/Audio.h"

ModeSelect::ModeSelect()
{

}

int ModeSelect::counter = 0;

void ModeSelect::Load()
{
	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Please select the mode!", 0xFFFFFFFF));
	UpdateMenuTextColors();
}



void ModeSelect::UpdateMenuTextColors()
{
	uint32_t colors[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	colors[counter] = 0x7EFACBFF;

	mode1.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("mode1", colors[0]));
	mode2.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("mode2", colors[1]));
	mode3.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("mode3", colors[2]));
	
}



void ModeSelect::Update(double dt)
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


	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
	}


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void ModeSelect::Unload()
{
	message.reset();
	mode1.reset();
	mode2.reset();
	mode3.reset();
}

void ModeSelect::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);

	message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 250), (Engine::GetWindow().GetSize().y - 50) }));
	  mode1->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 100), (Engine::GetWindow().GetSize().y - 200) }));
	  mode2->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 100), (Engine::GetWindow().GetSize().y - 300) }));
	  mode3->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 100), (Engine::GetWindow().GetSize().y - 400) }));
}

void ModeSelect::ImguiDraw()
{

}

void ModeSelect::HandleEvent(SDL_Event& event)
{

}

