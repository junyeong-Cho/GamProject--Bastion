/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Button.h
Project:    GAM200 Engine
Author:     Hyeonjoon Nam
Created:    November 2, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "Game/GameObjectTypes.h"

#include "Engine/GameStateManager.h"
#include "Engine/Vec2.h"
#include "Engine/GameObject.h"
#include "Engine/Texture.h"
//#include "Wave.h"


class Button : public GAM200::GameObject
{
public:
    Button(Math::vec2 position, Math::vec2 size);

    GameObjectTypes Type() override { return GameObjectTypes::Button; }
    std::string TypeName() override { return "Button"; }

    void Update(double dt) override;

    virtual bool IsClicked();

    static bool random;
    int map_number;

   


protected:
    virtual void func();
private:

    Math::vec2 position;
    Math::vec2 size;

    Math::vec2 mouse_position;

    bool is_on = false;

};


///////

class tower1_Button : public Button
{
public:
    tower1_Button(Math::vec2 position, Math::vec2 size);

    void func();
};

class tower2_Button : public Button
{
public:
    tower2_Button(Math::vec2 position, Math::vec2 size);

    void func();
};

class tower3_Button : public Button
{
public:
    tower3_Button(Math::vec2 position, Math::vec2 size);

    void func();
};

class random_tower_Button : public Button
{
public:
    random_tower_Button(Math::vec2 position, Math::vec2 size);

    void func();
};

class Store_Easy_Button : public Button {
public:
    Store_Easy_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Hard_Button : public Button {
public:
    Store_Hard_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Item_1 : public Button
{
public:
    Store_Item_1(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 20;
};

class Store_Item_2 : public Button
{
public:
    Store_Item_2(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 30;
};

class Store_Item_3 : public Button
{
public:
    Store_Item_3(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 30;
};

class Store_Tutorial_Button : public Button {
public:
    Store_Tutorial_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Gold_Button : public Button {
public:
    Store_Gold_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};


class Store_Menu_Button : public Button {
public:
    Store_Menu_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_GameStart_Button : public Button {
public:
    Store_GameStart_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Base_Item1_Button : public Button
{
public:
    Base_Item1_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 20;
};

class Base_Item2_Button : public Button
{
public:
    Base_Item2_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 30;
};

class Base_Item3_Button : public Button
{
public:
    Base_Item3_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    int cost = 30;
};

class Selected_Stage0_Button : public Button
{
public:
    Selected_Stage0_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Selected_Stage1_Button : public Button
{
public:
    Selected_Stage1_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Selected_Stage2_Button : public Button
{
public:
    Selected_Stage2_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Base_Map0_Button : public Button
{
public:
    Base_Map0_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;
private:
};

class Base_Map1_Button : public Button
{
public:
    Base_Map1_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;
private:
};

class Base_Map2_Button : public Button
{
public:
    Base_Map2_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
};

class Base_Map3_Button : public Button
{
public:
    Base_Map3_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
};

class Base_Map4_Button : public Button
{
public:
    Base_Map4_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
};

class Base_Map5_Button : public Button
{
public:
    Base_Map5_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
};

class Base_Map6_Button : public Button
{
public:
    Base_Map6_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
};


/////////////////////////////////////
class GameSpeed_Button : public Button {
public:
    GameSpeed_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    GAM200::Texture* speed_1 = Engine::Instance().GetTextureManager().Load("assets/buttons/speed1.png");
    GAM200::Texture* speed_2 = Engine::Instance().GetTextureManager().Load("assets/buttons/speed2.png");
    //GAM200::Texture* speed_3 = Engine::Instance().GetTextureManager().Load("assets/buttons/speed3.png");
    GAM200::Texture* speed_4 = Engine::Instance().GetTextureManager().Load("assets/buttons/speed4.png");
};

class Skip_Button : public Button
{
public:
    Skip_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    GAM200::Texture* skip_possible = Engine::Instance().GetTextureManager().Load("assets/buttons/skip_button.png");
    GAM200::Texture* skip_impossible = Engine::Instance().GetTextureManager().Load("assets/buttons/none_skip.png");
};

class Setting_Button : public Button
{
public:
    Setting_Button(Math::vec2 position, Math::vec2 size);

    void func() override;

private:
};

class Tutorial_Next_Step_Button : public Button
{
public:
    Tutorial_Next_Step_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Tutorial_Prev_Step_Button : public Button
{
public:
    Tutorial_Prev_Step_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Wave_Enemy2 : public Button
{
public:
    Wave_Enemy2(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Wave_Enemy3 : public Button
{
public:
    Wave_Enemy3(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Mute_ONOFF_Button : public Button
{
public:
    Mute_ONOFF_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    GAM200::Texture* mute_on   = Engine::Instance().GetTextureManager().Load("assets/buttons/mute_on.png");
    GAM200::Texture* mute_off  = Engine::Instance().GetTextureManager().Load("assets/buttons/mute_off.png");
    bool             mute      = false;
};

class Sound_reset_Button : public Button
{
public:
    Sound_reset_Button(Math::vec2 position, Math::vec2 size);

    void func() override;

private:
};