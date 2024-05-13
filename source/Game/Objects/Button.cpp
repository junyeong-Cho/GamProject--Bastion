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

#include "Game/Modes/Tutorial.h"

#include "Component/Gold.h"
#include "Component/GameSpeed.h"


#include "Game/States.h"

extern bool tower_summoned;
extern int  startGold;
extern int  monsterLimit;
extern int  diamond;
int         unit_cost = 55;

Button::Button(Math::vec2 position, Math::vec2 size) : GameObject(position), position(position), size(size)
{

}
bool Button::random = false;
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
	Button::random = false;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
}

Store_Hard_Button::Store_Hard_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Hard.spt", (this)));
}
void Store_Hard_Button::func() {
	Button::random = true;
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
}


Store_Item_1::Store_Item_1(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/InitialGoldPlus.spt", (this)));
}
void Store_Item_1::func()
{
    if (diamond < cost)
        return;
    diamond -= cost;

    startGold += 50;
}
void Store_Item_1::Draw(Math::TransformationMatrix camera_matrix)
{
    GameObject::Draw(camera_matrix);
    ShaderDrawing::draw_text("$" +  std::to_string(cost), GetPosition().x + 100, GetPosition().y - 30, 40, 1.0f, 1.0f, 0.0f);
}

Store_Item_2::Store_Item_2(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/MonsterLimitPlus.spt", (this)));
}
void Store_Item_2::func()
{
    if (diamond < cost)
        return;
    diamond -= cost;

    monsterLimit += 5;
}
void Store_Item_2::Draw(Math::TransformationMatrix camera_matrix)
{
    GameObject::Draw(camera_matrix);
    ShaderDrawing::draw_text("$" + std::to_string(cost), GetPosition().x + 100, GetPosition().y - 30, 40, 1.0f, 1.0f, 0.0f);
}


Store_Item_3::Store_Item_3(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/UnitCostMinus.spt", (this)));
}
void Store_Item_3::func()
{
    if (diamond < cost)
        return;
    diamond -= cost;

    --unit_cost;
}
void Store_Item_3::Draw(Math::TransformationMatrix camera_matrix)
{
    GameObject::Draw(camera_matrix);
    ShaderDrawing::draw_text("$" + std::to_string(cost), GetPosition().x + 100, GetPosition().y - 30, 40, 1.0f, 1.0f, 0.0f);
}


Store_Tutorial_Button::Store_Tutorial_Button(Math::vec2 position, Math::vec2 size) : Button(position, size) {
	AddGOComponent(new GAM200::Sprite("assets/buttons/Tutorial_Icon.spt", (this)));
}
void Store_Tutorial_Button::func() {
	Button::random = false;
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

	if (gold->GetCurrentGold() < unit_cost)
		return;

	gold->Spend(unit_cost);
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

	if (gold->GetCurrentGold() < unit_cost)
		return;

	gold->Spend(unit_cost);
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

	if (gold->GetCurrentGold() < unit_cost)
		return;

	gold->Spend(unit_cost);

	new Bomb_1();
	tower_summoned = true;
}

random_tower_Button::random_tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    // AddGOComponent(new GAM200::Sprite("assets/buttons/TestButton.spt", (this)));
}

void random_tower_Button::func()
{
    Gold* gold = Engine::GetGameStateManager().GetGSComponent<Gold>();

    if (gold->GetCurrentGold() < unit_cost)
        return;

    gold->Spend(unit_cost);

    int random_value = rand() % 3;
    switch (random_value)
    {
        case 0:
			new Sword_1();
			break;
        case 1:
			new Bow_1();
			break;
        case 2:
			new Bomb_1();
			break;
	}

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
		speed_1->Draw(GetMatrix() * camera_matrix);
		break;
	case 2:
		speed_2->Draw(GetMatrix() * camera_matrix);
		break;
	case 3:
		speed_3->Draw(GetMatrix() * camera_matrix);
		break;
	case 4:
		speed_4->Draw(GetMatrix() * camera_matrix);
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
		skip_impossible->Draw(GetMatrix() * camera_matrix);
		break;

	case Wave::Rest:
		skip_possible->Draw(GetMatrix() * camera_matrix);
		break;

	case Wave::End:

		break;
	}
}


Tutorial_Next_Step_Button::Tutorial_Next_Step_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Tutorial_Next_Step_Button::func()
{
    Tutorial::NextStep();
}

Tutorial_Prev_Step_Button::Tutorial_Prev_Step_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Tutorial_Prev_Step_Button::func()
{
    Tutorial::PrevStep();
}