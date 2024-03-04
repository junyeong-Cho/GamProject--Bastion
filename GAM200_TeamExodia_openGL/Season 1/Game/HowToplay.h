/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  HowToPlay.h
Project:    GAM200_TeamExodia_openGL
Author:     Taeho Kim
Created:    October		10, 2023
Updated:    December	15, 2023
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

	GAM200::Texture how1 = GAM200::Texture("assets/images/ui/how_to_play/how1.png", GAM200::Texture::TextureType::RECTANGLE);

	GAM200::Texture how2 = GAM200::Texture("assets/images/ui/how_to_play/how2.png", GAM200::Texture::TextureType::RECTANGLE);

	GAM200::Texture how3 = GAM200::Texture("assets/images/ui/how_to_play/how3.png", GAM200::Texture::TextureType::RECTANGLE);

	GAM200::Texture how4 = GAM200::Texture("assets/images/ui/how_to_play/how4.png", GAM200::Texture::TextureType::RECTANGLE);

	GAM200::Texture key_tuto = GAM200::Texture("assets/images/ui/how_to_play/key_tuto.png", GAM200::Texture::TextureType::RECTANGLE);

	int page_num = 0;

private:
	std::unique_ptr<GAM200::Texture> message;

};