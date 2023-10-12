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
#include "../Engine/ShowCollision.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"

#include "../Game/Mode1.h"
#include "../Game/States.h"
#include "../Game/Splash.h"
#include "../Game/Tile.h"
#include "../Game/Player.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>

Mode1::Mode1() : player_ptr()
{

}


void Mode1::Load()
{
	counter = 0;

	AddGSComponent(new GAM200::GameObjectManager());
	AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));

	Tile* starting_tile = new Tile(Math::irect{ { 0, 0 }, { 100, 100 } });

	player_ptr = new Player({ 100, 100 }, (starting_tile));
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);

	GetGSComponent<GAM200::GameObjectManager>()->Add(starting_tile);
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 100, 0 }, { 100, 100 } }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 200, 0 }, { 200, 100 } }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 300, 0 }, { 300, 100 } }));

	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });
	//GetGSComponent<GAM200::Camera>()->SetLimit({ {0, 0},{GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize()} });

	#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
	#endif


}

void Mode1::Update(double dt)
{
	//Engine::GetLogger().LogDebug(std::to_string(counter));
	//Engine::GetWindow().Clear(0.2f, 0.1f, 0.4f, 1.0f);
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);


	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<Timer>()->Update(dt);
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);

	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();




	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
	}
}

void Mode1::Unload()
{
	player_ptr = nullptr;
	//GetGSComponent<Background>()->Unload();
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Mode1::Draw()
{
	//Engine::GetWindow().Clear(0x000000FF);

	Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();

	//GetGSComponent<Background>()->Draw(*GetGSComponent<GAM200::Camera>());

	//timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 5 }));
	//score.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 80 }));

	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
}

void Mode1::ImguiDraw()
{

}

void Mode1::HandleEvent(SDL_Event& event)
{

}