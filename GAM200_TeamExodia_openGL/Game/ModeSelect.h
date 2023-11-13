/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ModeSelect.h
Project:    GAM200 Engine
Author:
Created:    November 13, 2023
Updated:    November 13, 2023
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


class ModeSelect : public GAM200::GameState
{
public:
	ModeSelect();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;


	std::string GetName() override { return "ModeSelect"; }

	void UpdateMenuTextColors();



private:
	std::unique_ptr<GAM200::Texture> message;


	std::unique_ptr<GAM200::Texture> mode1;
	std::unique_ptr<GAM200::Texture> mode2;
	std::unique_ptr<GAM200::Texture> mode3;

	int counter = 0;


};