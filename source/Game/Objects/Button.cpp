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
int			selected_stage = 0;
int         selected_map   = -1;
int         unit_cost      = 55;
int         stock1         = 10;
int         stock2         = 10;
int         stock3         = 10;


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
    ShaderDrawing::draw_text("$" + std::to_string(cost), GetPosition().x + 32.3603, GetPosition().y - 0.4926, 40, 0.196f, 0.196f, 0.196f);
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
    ShaderDrawing::draw_text("$" + std::to_string(cost), GetPosition().x + 32.3603, GetPosition().y - 0.4926, 40, 0.196f, 0.196f, 0.196f);
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
    ShaderDrawing::draw_text("$" + std::to_string(cost), GetPosition().x + 32.3603, GetPosition().y - 0.4926, 40, 0.196f, 0.196f, 0.196f);
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
	//AddGOComponent(new GAM200::Sprite("assets/buttons/Store_Menu.spt", (this)));
}
void Store_Menu_Button::func() {
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
}


Store_GameStart_Button::Store_GameStart_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}
void Store_GameStart_Button::func() {

    if (selected_stage == 0 && selected_map == 0)
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Tutorial));
    }
    else if (selected_stage == 1 && selected_map >= 1 && selected_map <= 3)
    {
        Button::random = false;
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
	}
    else if (selected_stage == 2 && selected_map >= 4 && selected_map <= 6)
    {
        Button::random = true;
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
    }

}


Base_Item1_Button::Base_Item1_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Base_Item1_Button::func()
{
    if (stock1>0)
        stock1--;

    if (diamond < cost)
        return;
    diamond -= cost;

    startGold += 50;
}

Base_Item2_Button::Base_Item2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Base_Item2_Button::func()
{
    if (stock2 > 0)
        stock2--;

    if (diamond < cost)
        return;
    diamond -= cost;

    monsterLimit += 5;
}

Base_Item3_Button::Base_Item3_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Base_Item3_Button::func()
{
    if (stock3 > 0)
        stock3--;

    if (diamond < cost)
        return;
    diamond -= cost;

    unit_cost -= 2;
}

Selected_Stage0_Button::Selected_Stage0_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Selected_Stage0_Button::func()
{
    selected_stage = 0;
    selected_map   = -1;
}

Selected_Stage1_Button::Selected_Stage1_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Selected_Stage1_Button::func()
{
    selected_stage = 1;
    selected_map   = -1;
}

Selected_Stage2_Button::Selected_Stage2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Selected_Stage2_Button::func()
{
    selected_stage = 2;
    selected_map   = -1;
}

Base_Map0_Button::Base_Map0_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map0_Button::func()
{
    if (selected_stage == 0)
    {
        selected_map = 0;
	}
}

void Base_Map0_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 0)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964/2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map1_Button::Base_Map1_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map1_Button::func()
{
    if (selected_stage == 1)
    {
        selected_map = 1;
	}

}

void Base_Map1_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 1)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map2_Button::Base_Map2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map2_Button::func()
{
    if (selected_stage == 1)
    {
        selected_map = 2;
    }
}

void Base_Map2_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 2)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map3_Button::Base_Map3_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map3_Button::func()
{
    if (selected_stage == 1)
    {
        selected_map = 3;
    }
}

void Base_Map3_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 3)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map4_Button::Base_Map4_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map4_Button::func()
{
    if (selected_stage == 2)
    {
        selected_map = 4;
    }
}

void Base_Map4_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 4)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map5_Button::Base_Map5_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map5_Button::func()
{
    if (selected_stage == 2)
    {
        selected_map = 5;
    }
}

void Base_Map5_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 5)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 *3)));
        GameObject::Draw(camera_matrix * translation);
    }
}

Base_Map6_Button::Base_Map6_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
    AddGOComponent(new GAM200::Sprite("assets/buttons/Selected.spt", (this)));
}

void Base_Map6_Button::func()
{
    if (selected_stage == 2)
    {
        selected_map = 6;
    }
}

void Base_Map6_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (selected_map == 6)
    {
        Math::TranslationMatrix translation(Math::vec2(640, 400 + (39.3964 / 2 * 3)));
        GameObject::Draw(camera_matrix * translation);
    }
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
		speed_1->Draw(GetMatrix());
		break;
	case 2:
		speed_2->Draw(GetMatrix());
		break;
	case 4:
		speed_4->Draw(GetMatrix());
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
		skip_impossible->Draw(GetMatrix());
		break;

	case Wave::Rest:
		skip_possible->Draw(GetMatrix());
		break;

	case Wave::End:

		break;
	}
}

Setting_Button::Setting_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Setting_Button::func()
{
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
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

Wave_Enemy2::Wave_Enemy2(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Wave_Enemy2::func()
{

}

Wave_Enemy3::Wave_Enemy3(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
}

void Wave_Enemy3::func()
{
}

Mute_ONOFF_Button::Mute_ONOFF_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}

void Mute_ONOFF_Button::func()
{
    if (!mute)
    {
    Engine::Instance().GetAudioManager().SetMusicVolume(0.0f);
    mute = true;
    }
    else
    {
    Engine::Instance().GetAudioManager().SetMusicVolume(0.5f);
    mute = false;
    }
}

void Mute_ONOFF_Button::Draw(Math::TransformationMatrix camera_matrix)
{
    if (mute)
    {
        mute_on->Draw(GetMatrix());
    }
    else
    {
        mute_off->Draw(GetMatrix());
    }
}