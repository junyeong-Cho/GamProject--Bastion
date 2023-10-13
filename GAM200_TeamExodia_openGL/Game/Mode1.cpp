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
#include "../Engine/Collision.h"

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

	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 100,   0 }, { 100, 100 } }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 200,   0 }, { 100, 100 } }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 300, 100 }, { 100, 100 } }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Tile(Math::irect{ { 400, 100 }, { 100, 100 } }));

	player_ptr = new Player({ 0, 0 });
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);
	
	
	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });
	//GetGSComponent<GAM200::Camera>()->SetLimit({ {0, 0},{GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize()} });

	#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
	#endif


}

void Mode1::Update(double dt)
{
	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

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
	ImGui::Begin("Program Info");
	{
		ImGui::Text("FPS: %f", "55.5");
		ImGui::Text("Frame Time: %f", "55.5");
		ImGui::Text("Counter: %f", counter);
		ImGui::Text("Player position: %.3f, %.3f", player_ptr->GetPosition().x, player_ptr->GetPosition().y);
		ImGui::Text("Camera position: %.3f, %.3f", GetGSComponent<GAM200::Camera>()->GetPosition().x, GetGSComponent<GAM200::Camera>()->GetPosition().y);

	}
	ImGui::End();


	ImGui::Begin("Mouse Location");
	{
		ImGui::Text("Mouse Position X : %.2f", Engine::Instance().GetMouse().GetMousePosition().x);
		ImGui::Text("Mouse Position Y : %.2f", Engine::Instance().GetMouse().GetMousePosition().y);
	}

	ImGui::End();
}

void Mode1::HandleEvent(SDL_Event& event)
{

}