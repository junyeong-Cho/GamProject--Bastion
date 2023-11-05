/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Main_menu.h
Project:    GAM200 Engine
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

class Main_menu : public GAM200::GameState
{
public:
	Main_menu();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;


	std::string GetName() override { return "Main_menu"; }

	void UpdateMenuTextColors();

private:
	Background background;

	std::unique_ptr<GAM200::Texture> main_title;
	std::unique_ptr<GAM200::Texture> side_scroller;
	std::unique_ptr<GAM200::Texture> Space_shotter;
	std::unique_ptr<GAM200::Texture> exit;

	int counter = 0;

};