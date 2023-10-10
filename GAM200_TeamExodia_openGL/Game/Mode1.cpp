/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Player.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		10, 2023
*/



#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"

#include "../Game/Mode1.h"
#include "../Game/States.h"
#include "../Game/Splash.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>

Mode1::Mode1()
{

}


void Mode1::Load()
{
	counter = 0;

}

void Mode1::Update(double dt)
{
	//Engine::GetLogger().LogDebug(std::to_string(counter));
	Engine::GetWindow().Clear(0.2f, 0.1f, 0.4f, 1.0f);


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::R))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::R))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
	}
}

void Mode1::Unload()
{

}

void Mode1::Draw()
{

}

void Mode1::ImguiDraw()
{

}

void Mode1::HandleEvent(SDL_Event& event)
{

}