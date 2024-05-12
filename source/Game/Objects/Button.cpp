/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Button.cpp
Project:    GAM200 Engine
Author:     Hyeonjoon Nam
Created:    November 2, 2023
Updated:    December 15, 2023
*/

#include "Engine/GameObjectManager.h"

#include "Button.h"
#include "Component/Map.h"

#include "Engine/DrawShape.h"
#include "Component/Wave.h"

#include "Game/Objects/Units/Unit.h"
#include "Game/Objects/Units/MeleeUnit.h"
#include "Game/Objects/Units/RangedUnit.h"
#include "Game/Objects/Units/MagicUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Component/Gold.h"
#include "Component/GameSpeed.h"


#include "Game/States.h"

extern bool tower_summoned;

Button::Button(Math::vec2 position, Math::vec2 size) : GameObject(position), position(position), size(size)
{

}

int Button::difficult = 0;

void Button::Update(double dt)
{
	GameObject::Update(dt);
	if (IsClicked())
	{
		func();
	}
}

void Button::func()
{

}

bool Button::IsClicked()
{
	mouse_position = Engine::GetInput().GetMousePosition();

	is_on = mouse_position.x >= position.x && mouse_position.x <= position.x + size.x && mouse_position.y >= position.y && mouse_position.y <= position.y + size.y;

	if (!is_on) {
		return false;
	}

	if (Engine::GetInput().MouseJustReleased(GAM200::Input::MouseButtons::LEFT) && is_on)
	{
		return true;
	}

	return false;
}

Store_Easy_Button::Store_Easy_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Easy.spt", (this)));
}

void Store_Easy_Button::func() {
	Button::difficult = 1;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
}

Store_Normal_Button::Store_Normal_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Normal.spt", (this)));
}

void Store_Normal_Button::func() {
	Button::difficult = 2;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
}
Store_Hard_Button::Store_Hard_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Hard.spt", (this)));
}

void Store_Hard_Button::func() {
	Button::difficult = 3;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
}

Store_Tutorial_Button::Store_Tutorial_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Tutorial_Icon.spt", (this)));
}

void Store_Tutorial_Button::func() {
	Button::difficult = 4;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Tutorial));
}

Store_Gold_Button::Store_Gold_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Gold.spt", (this)));
}
void Store_Gold_Button::func() {


}


Store_Menu_Button::Store_Menu_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Menu.spt", (this)));
}
void Store_Menu_Button::func() {
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
}

Store_GameStart_Button::Store_GameStart_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {

}

void Store_GameStart_Button::func() {
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
}



///////////

tower1_Button::tower1_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower1_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);
	new Sword_1();
	tower_summoned = true;
}


tower2_Button::tower2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower2_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);
	new Bow_1();
	tower_summoned = true;
}

tower3_Button::tower3_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower3_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);

	new Bomb_1();
	tower_summoned = true;
}


GameSpeed_Button::GameSpeed_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void GameSpeed_Button::func()
{
	Engine::GetGameStateManager().GetGSComponent<GameSpeed>()->NextSpeed();
}

void GameSpeed_Button::Draw(Math::TransformationMatrix camera_matrix)
{
	int speed = static_cast<int>(Engine::GetGameStateManager().GetGSComponent<GameSpeed>()->GetSpeed());

	switch (speed)
	{
	case 1:
		speed_1->Draw(camera_matrix * GetMatrix());
		break;
	case 2:
		speed_2->Draw(camera_matrix * GetMatrix());
		break;
	case 3:
		speed_3->Draw(camera_matrix * GetMatrix());
		break;
	case 4:
		speed_4->Draw(camera_matrix * GetMatrix());
		break;
	}
}

Skip_Button::Skip_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Skip_Button::func()
{
	Engine::GetGameStateManager().GetGSComponent<Wave>()->Skip();
}

void Skip_Button::Draw(Math::TransformationMatrix camera_matrix)
{
	switch (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState())
	{
	case Wave::Battle:
		skip_impossible->Draw(camera_matrix * GetMatrix());
		break;

	case Wave::Rest:
		skip_possible->Draw(camera_matrix * GetMatrix());
		break;

	case Wave::End:

		break;
	}
}