#pragma once


#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"


class Button : public GAM200::GameObject
{
public:
    Button(Math::vec2 position, Math::vec2 size);

    GameObjectTypes Type() override { return GameObjectTypes::Button; }
    std::string TypeName() override { return "Button"; }

    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

    bool tower_type[7] = { false,false,false, false,false,false,false };//basic doble triple delete change_tp change_tb wave

protected:
    virtual void func(Math::ivec2);

private:
    
    GAM200::Texture next_wave = GAM200::Texture("assets/images/ui/tower_deploy_win/nw.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture next_wave_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/nw_2.png", GAM200::Texture::TextureType::RECTANGLE);
   
    GAM200::Texture basic = GAM200::Texture("assets/images/ui/tower_deploy_win/b.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture basic_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/b_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture double_tower = GAM200::Texture("assets/images/ui/tower_deploy_win/d.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture double_tower_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/d_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture triple = GAM200::Texture("assets/images/ui/tower_deploy_win/t.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture triple_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/t_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture change_t_P = GAM200::Texture("assets/images/ui/tower_deploy_win/c1.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture change_t_P_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/c1_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture change_t_b = GAM200::Texture("assets/images/ui/tower_deploy_win/c2.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture change_t_b_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/c2_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture delete_tower = GAM200::Texture("assets/images/ui/tower_deploy_win/delete.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture delete_tower_selected = GAM200::Texture("assets/images/ui/tower_deploy_win/delete_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture side = GAM200::Texture("assets/images/ui/tower_deploy_win/sb.png", GAM200::Texture::TextureType::RECTANGLE);












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


class Push_Tower_Button : public Button
{
public:
    Push_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Wide_Tower_Button : public Button
{
public:
    Wide_Tower_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Upgrade_Button : public Button
{
public:
    Upgrade_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Delete_Button : public Button
{
public:
    Delete_Button(Math::vec2 position, Math::vec2 size);

    void func(Math::ivec2) override;
};


class Choice_1_Button : public Button
{
public:
    Choice_1_Button(Math::vec2 position, Math::vec2 size);

    void Draw(Math::TransformationMatrix camera_matrix) override;
    void func(Math::ivec2) override;
};


class Choice_2_Button : public Button
{
public:
    Choice_2_Button(Math::vec2 position, Math::vec2 size);

    void Draw(Math::TransformationMatrix camera_matrix) override;
    void func(Math::ivec2) override;
};


class Choice_3_Button : public Button
{
public:
    Choice_3_Button(Math::vec2 position, Math::vec2 size);

    void Draw(Math::TransformationMatrix camera_matrix) override;
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