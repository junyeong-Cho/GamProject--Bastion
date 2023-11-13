/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GamePlayEditor.cpp
Project:    GAM200 Engine
Author:
Created:    November 13, 2023
Updated:    November 13, 2023
*/

#include "GamePlayEditor.h"

#include "Fonts.h"
#include "../Engine/Engine.h"

GamePlayEditor::GamePlayEditor()
{

}

void GamePlayEditor::Load()
{
	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press Esc to go back", 0xFFFFFFFF));
}

void GamePlayEditor::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void GamePlayEditor::Unload()
{
	message.reset();
}

void GamePlayEditor::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);

	message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
}

void GamePlayEditor::ImguiDraw()
{

}

void GamePlayEditor::HandleEvent(SDL_Event& event)
{

}
