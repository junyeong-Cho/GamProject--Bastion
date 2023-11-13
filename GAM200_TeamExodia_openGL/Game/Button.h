#pragma once


#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"


class Button : public GAM200::GameObject
{
public:
    Button(Math::vec2 position, Math::vec2 size);

    GameObjectTypes Type() override { return GameObjectTypes::Button; }
    std::string TypeName() override { return "Button"; }

    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;


protected:
    virtual void func(Math::ivec2);

private:
    Math::vec2 position;
    Math::vec2 size;

    Math::vec2 mouse_position;
    Math::ivec2 mouse_tile_position;
    Math::ivec2 tile_size;

    bool is_on = false;
};


class Wave_Start_Button : public Button
{
public:
    Wave_Start_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Basic_Tower_Button : public Button
{
public:
    Basic_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Double_Tower_Button : public Button
{
public:
    Double_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Triple_Tower_Button :public Button
{
public:
    Triple_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Delete_Tower_Button :public Button
{
public:
    Delete_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Pass_Tile_Button : public Button
{
public:
    Pass_Tile_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Block_Tile_Button :public Button
{
public:
    Block_Tile_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};






/*
class Basic_Monster_Button : public Button
{
public:
    Basic_Monster_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};

class Fast_Monster_Button : public Button
{
public:
    Fast_Monster_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};

class Slow_Monster_Button :public Button
{
public:
    Slow_Monster_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};

*/