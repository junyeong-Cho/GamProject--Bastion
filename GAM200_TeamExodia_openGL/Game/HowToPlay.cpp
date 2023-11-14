/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  HowToPlay.cpp
Project:    GAM200 Engine
Author:
Created:    November 13, 2023
Updated:    November 13, 2023
*/


#include "HowToplay.h"

#include "Fonts.h"
#include "../Engine/Engine.h"

HowToPlay::HowToPlay()
{

}

void HowToPlay::Load()
{
	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press Esc to go back", 0xFFFFFFFF));
}

void HowToPlay::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		page_num = 0;

		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void HowToPlay::Unload()
{
	message.reset();
}

void HowToPlay::Draw()
{


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Enter) || Engine::GetInput().MouseJustReleased(GAM200::Input::MouseButtons::LEFT))
	{
		if (page_num <= 5)
			page_num += 1;
	}

	switch (page_num)
	{
	case 1:
		key_tuto.Draw(0, 0, 1280, 720);
		break;
	case 2:
		how1.Draw(0, 0, 1280, 720);
		break;

	case 3:
		how2.Draw(0, 0, 1280, 720);
		break;

	case 4:
		how3.Draw(0, 0, 1280, 720);
		break;
	case 5:
		Engine::GetWindow().Clear(0x000000FF);

		message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
	
		break;
	}
}

void HowToPlay::ImguiDraw()
{

}

void HowToPlay::HandleEvent(SDL_Event& event)
{

}
