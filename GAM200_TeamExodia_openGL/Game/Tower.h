#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"

#include <iostream>
#include <fstream>
#include <string>



// Virtual class for the towers
class Tower : public GAM200::GameObject {
public:
    Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Tower; }
    std::string TypeName() override { return "Tower"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    virtual bool CanCollideWith(GameObjectTypes type) override;

    virtual void ResolveCollision(GameObject* other_object) override;

    static int GetCost() { return cost; }

    int GetHP() const { return hp; }
    void SetHP(int value) { hp = value; }
    void Damaged(int damage) { hp -= damage; }
    virtual void Recover() { hp = max_hp; }
    Math::ivec2 GetTilePosition() const { return tile_position; }

    bool IsOn() const;
    bool IsClicked();

    void Tower_Destroy();

    virtual void ShowInfo();
    virtual Tower* Upgrade();

    void check_supplied();
    virtual void supply_ammo() { ammo = max_ammo; }
    static void Enable_Supply_Ammo() { enable_supply = true; }
    static bool Supply_Enabled() { return enable_supply; }

    static void Unable_Supply_Ammo() { enable_supply = false; }

protected:
    bool set_basic_tower = false;
    GAM200::Texture c_down = GAM200::Texture("assets/images/c_down.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_up = GAM200::Texture("assets/images/c_up.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_left = GAM200::Texture("assets/images/c_left.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_right = GAM200::Texture("assets/images/c_right.png", GAM200::Texture::TextureType::RECTANGLE);

    struct Color {
        float r;
        float g;
        float b;
    };
    Color color = { 0 };
    Color charging_color;
    Color attack_color;

    enum   Animations
    {
        Charging,
        Attacking,
    };

    Math::ivec2 size{ 80, 80 };
    Math::ivec2 tile_size{ 80, 80 };

    Math::ivec2 tile_position;

    int direction;
    Math::vec2 bullet_direction;

    static bool enable_supply;

    double attack_count = 0;
    bool attack_ready = false;

    // add parts

    bool is_fired = false;

    // add parts



    ///
    bool four_way[4] = { false,false,false,false };//tower_way_select
    ///
    int hp;

    int upgrade_count = 0;

    int ammo = 0;

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;


    //////// add_parts

    enum class tower_state
    {
        None,
        Fire

    };

    GAM200::Sprite single_tower;
    GAM200::Sprite double_tower;
    GAM200::Sprite triple_tower;
    GAM200::Sprite push_tower;
    GAM200::Sprite wide_tower;

    //////// add_parts

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int max_ammo;
};


// Basic tower
class Basic_Tower : public Tower {
public:
    Basic_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Tower; }
    std::string TypeName() override { return "Basic_Tower"; }

    //add parts
    void Draw(Math::TransformationMatrix camera_matrix) override;
    //add parts

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// Double tower
class Double_Tower : public Tower
{
public:
    Double_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Double_Tower; }
    std::string TypeName() override { return "Double_Tower"; }

    //add parts
    void Draw(Math::TransformationMatrix camera_matrix) override;
    //add parts

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// Triple tower
class Triple_Tower : public Tower
{
public:
    Triple_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Triple_Tower; }
    std::string TypeName() override { return "Triple_Tower"; }

    //add parts
    void Draw(Math::TransformationMatrix camera_matrix) override;
    //add parts

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// Push tower
class Push_Tower : public Tower
{
public:
    Push_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Push_Tower; }
    std::string TypeName() override { return "Push_Tower"; }

    //add parts
    void Draw(Math::TransformationMatrix camera_matrix) override;
    //add parts

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    double real_attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// Wide Tower
class Wide_Tower : public Tower
{
public:
    Wide_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Wide_Tower; }
    std::string TypeName() override { return "Wide_Tower"; }

    //add parts
    void Draw(Math::TransformationMatrix camera_matrix) override;
    //add parts

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    double real_attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// Auto Tower
class Auto_Tower : public Tower
{
public:
    Auto_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Auto_Tower; }
    std::string TypeName() override { return "Auto_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;
    void ResolveCollision(GameObject* other_object) override;

    Tower* Upgrade() override;

    static int GetCost() { return cost; }
    static int GetUpgradeCost() { return upgrade_cost; }
    void ShowInfo() override;
    void supply_ammo() override { ammo = max_ammo; }
    void Recover() { hp = max_hp; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static int upgrade_cost;
    static double attack_delay;
    double real_attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;

    static int max_ammo;
};


// File parsing
class TowerFactory {
public:
    static void InitBasicTowerFromFile(const std::string& filePath = "assets/towers/Basic_Tower.txt");
    static void InitDoubleTowerFromFile(const std::string& filePath = "assets/towers/Double_Tower.txt");
    static void InitTripleTowerFromFile(const std::string& filePath = "assets/towers/Triple_Tower.txt");
    static void InitPushTowerFromFile(const std::string& filePath = "assets/towers/Push_Tower.txt");
    static void InitWideTowerFromFile(const std::string& filePath = "assets/towers/Wide_Tower.txt");
    static void InitAutoTowerFromFile(const std::string& filePath = "assets/towers/Auto_Tower.txt");

private:

};


// Tower Adopter
class Tower_Adopter
{
public:
    static Tower_Adopter& GetInstance()
    {
        static Tower_Adopter instance;
        return instance;
    }

    void Set_Tower(Tower*);
    void Show_Info();
    void Upgrade();
    void Delete();

private:
    Tower_Adopter() = default;

    Tower* current_tower = nullptr;

};
