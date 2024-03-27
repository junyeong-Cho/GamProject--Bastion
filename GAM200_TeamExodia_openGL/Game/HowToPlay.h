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


#pragma once

#include "../Game/States.h"
#include "../Game/Background.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/TextureManager.h"

#include "../Engine/Texture.h"
#include "../Engine/Font.h"

#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"

class HowToPlay : public GAM200::GameState
{
public:
	HowToPlay();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;


	std::string GetName() override { return "HowToPlay"; }

	void UpdateMenuTextColors();

private:

	int page	= 0;
	//int counter = 0;
	int state	= 0;


	GAM200::Texture* FirstPage;
	GAM200::Texture* SecondPage;
	GAM200::Texture* ThirdPage;

	std::unique_ptr<GAM200::Texture> trash;

	std::unique_ptr<GAM200::Texture> next;
	std::unique_ptr<GAM200::Texture> back;


	std::unique_ptr<GAM200::Texture> exit;
	std::unique_ptr<GAM200::Texture> play;


	enum Page
	{
		One,
		Two,
		Three,
		End
	};

	enum State
	{
		Back,
		Next
	};

};