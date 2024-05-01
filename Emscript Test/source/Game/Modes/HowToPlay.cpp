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
#include "Game/Fonts.h"



HowToPlay::HowToPlay() : FirstPage(), SecondPage(), ThirdPage(), FourthPage()
{

}

void HowToPlay::Load()
{
	UpdateMenuTextColors();

	FirstPage = Engine::Instance().GetTextureManager().Load("assets/HowToPlay/Click_to_summon.png");
	FirstPage->texturetype = GAM200::Texture::TextureType::RECTANGLE;

	SecondPage = Engine::Instance().GetTextureManager().Load("assets/HowToPlay/Drag_to_move.png");
	SecondPage->texturetype = GAM200::Texture::TextureType::RECTANGLE;

	ThirdPage = Engine::Instance().GetTextureManager().Load("assets/HowToPlay/Merge_to_upgrade.png");
	ThirdPage->texturetype = GAM200::Texture::TextureType::RECTANGLE;

	FourthPage = Engine::Instance().GetTextureManager().Load("assets/HowToPlay/Lose_Condition.png");
	FourthPage->texturetype = GAM200::Texture::TextureType::RECTANGLE;

}

void HowToPlay::UpdateMenuTextColors()
{
	uint32_t colors[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
	colors[state] = 0x7EFACBFF;

	trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(",", colors[0]));
	back.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Back", colors[0]));
	next.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next", colors[1]));

	//exit.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", colors[0]));
	play.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Play", colors[1]));

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
			if (page == Page::Four)
			{
				Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
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

	trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	back->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 + 220, (Engine::GetWindow().GetSize().y / 2 - 220) }));

	switch (page)
	{
	case Page::One:
		FirstPage->Draw(0, 20, 1280, 800);
		break;

	case Page::Two:
		SecondPage->Draw(0, 0, 1280, 800);
		break;

	case Page::Three:
		ThirdPage->Draw(0, 0, 1280, 800);
		break;

	case Page::Four:
		FourthPage->Draw(0, 0, 1280, 800);
		break;
	}



	if (page == Page::Four)
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