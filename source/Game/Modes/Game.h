/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Game.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    November 2, 2023
Updated:    November 2, 2023
*/

#pragma once

#include "Engine/IfWantShader.h"

#include "Game/States.h"

#include "Engine/GameObjectManager.h"
#include "Engine/TextureManager.h"

#include "Engine/Texture.h"
#include "Engine/Font.h"

#include "Engine/GameState.h"
#include "Engine/Sprite.h"

#include "Game/Objects/Button.h"
class GameSpeed_Button;
class Skip_Button;
class RangedUnit;
class Wave;

class Game : public GAM200::GameState
{
public:
	Game();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;

	std::string GetName() override { return "Game"; }


#if IfWantShader
	//GAM200::Texture tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
	GAM200::Texture win = GAM200::Texture("assets/win.png");
	GAM200::Texture lose = GAM200::Texture("assets/lose.png");
	GAM200::Texture wave1 = GAM200::Texture("assets/Background/wave1.png");
	GAM200::Texture wave2 = GAM200::Texture("assets/Background/wave2.png");
	//GAM200::Texture ui       = GAM200::Texture("assets/Background/ingame_ui.png");
#else
	GAM200::Texture tower_ui_no_random = GAM200::Texture("assets/buttons/tower_ui.png", GAM200::Texture::TextureType::RECTANGLE);
	GAM200::Texture tower_ui_random = GAM200::Texture("assets/buttons/tower_ui_random.png", GAM200::Texture::TextureType::RECTANGLE);
	GAM200::Texture win = GAM200::Texture("assets/win.png", GAM200::Texture::TextureType::RECTANGLE);
	GAM200::Texture lose = GAM200::Texture("assets/lose.png", GAM200::Texture::TextureType::RECTANGLE);
#endif

private:

#if IfWantShader

#else
	std::unique_ptr<GAM200::Texture> trash;

	std::unique_ptr<GAM200::Texture> currentwave;
	std::unique_ptr<GAM200::Texture> time;
	std::unique_ptr<GAM200::Texture> gold;
	std::unique_ptr<GAM200::Texture> speed;
	std::unique_ptr<GAM200::Texture> monsters;
#endif

	enum InGameStates
	{
		InProgress,
		Boss,
		Win,
		Lose
	} in_game_state = InProgress;



	double count = 0.0;
};