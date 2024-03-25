/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  HowToPlay.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    November 2, 2023
*/

#include "HowToPlay.h"
#include "Fonts.h"



HowToPlay::HowToPlay()
{

}

void HowToPlay::Load()
{
	UpdateMenuTextColors();
}

void HowToPlay::UpdateMenuTextColors()
{
	uint32_t colors[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
	colors[state] = 0x7EFACBFF;

	back.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Back", colors[0]));
	next.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Next", colors[1]));
	
	//exit.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", colors[0]));
	play.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Play", colors[1]));
	
}


void HowToPlay::Update(double dt)
{
	bool shouldUpdateColors = false;


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Down))
	{
		state = (state + 1) % 2;
		shouldUpdateColors = true;
	}
	else if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Up))
	{
		state = (state + 1) % 2;
		shouldUpdateColors = true;
	}


	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
		if (state == State::Back)
		{
			if (page == Page::One)
			{
				Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
			}
			page -= 1;
		}
		else if (state == State::Next)
		{
			if (page == Page::End)
			{
				//Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Play));
			}
			page += 1;
		}
	}


	if (shouldUpdateColors)
	{
		UpdateMenuTextColors();
	}
}

void HowToPlay::Unload()
{
	state = 0;
	page = 0;
}

void HowToPlay::Draw()
{
	Engine::GetWindow().Clear(0.2f, 0.4f, 0.7f, 1.0f);

	back->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 220) }));


	if (page == Page::End)
	{
		//exit->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 220) }));
		play->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 280) }));
	}
	else
	{
		next->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 280) }));
	}

}

void HowToPlay::ImguiDraw()
{

}

void HowToPlay::HandleEvent(SDL_Event& event)
{

}
