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


#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "../Game/GameObjectTypes.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
//#include "Wave.h"


class Button : public GAM200::GameObject
{
public:
    Button(Math::vec2 position, Math::vec2 size);

    GameObjectTypes Type() override { return GameObjectTypes::Button; }
    std::string TypeName() override { return "Button"; }

    void Update(double dt) override;

    virtual bool IsClicked();

    static int difficult;
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

class Store_Easy_Button : public Button {
public:
    Store_Easy_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Normal_Button : public Button {
public:
    Store_Normal_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Hard_Button : public Button {
public:
    Store_Hard_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_InGame_Button : public Button {
public:
    Store_InGame_Button(Math::vec2 position, Math::vec2 size);

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

class GameSpeed_Button : public Button {
public:
    GameSpeed_Button(Math::vec2 position, Math::vec2 size);

	void func() override;
};