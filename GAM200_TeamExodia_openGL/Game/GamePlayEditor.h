/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GamePlayEditor.h
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


class GamePlayEditor : public GAM200::GameState
{
public:
	GamePlayEditor();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;


	std::string GetName() override { return "GamePlayEditor"; }


private:
	std::unique_ptr<GAM200::Texture> message;

};