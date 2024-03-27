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

#include "../Engine/GameObjectManager.h"

#include "Button.h"
#include "../Component/Map.h"

#include "../Engine/DrawShape.h"
#include "../Component/Wave.h"

#include "../Game/Unit.h"
#include "../Game/Monster.h"
#include "../Game/MeleeUnit.h"
#include "../Game/RangedUnit.h"
#include "../Game/MagicUnit.h"

#include "../Component/Gold.h"


#include "../Game/States.h"

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

Store_InGame_Button::Store_InGame_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_InGame.spt", (this)));
}

void Store_InGame_Button::func() {
	Button::difficult = 4;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
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
	AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower1_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);
	new Sword_1();
}


tower2_Button::tower2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower2_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);
	new Bow_1();
}

tower3_Button::tower3_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void tower3_Button::func()
{
	Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

	if (gold->GetCurrentGold() < 55)
		return;

	gold->Spend(55);

	new Bomb_1();
}
