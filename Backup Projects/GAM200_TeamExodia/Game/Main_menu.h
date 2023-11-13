/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Main_menu.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
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

class Main_menu : public CS230::GameState
{
public:
	Main_menu();
	
	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;



	std::string GetName() override { return "Main_menu"; }
	
	void UpdateMenuTextColors();

private:
	Background background;

	CS230::Texture main_title;
	CS230::Texture side_scroller;
	CS230::Texture Space_shotter;
	CS230::Texture exit;                

	int counter = 0;

};