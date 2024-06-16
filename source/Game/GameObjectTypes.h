/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectTypes.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		10, 2023
*/

#pragma once


enum class GameObjectTypes
{
    // Season 2
    Monster,
    Boss,

    Unit,



    MeleeUnit,
    Sword_1,
    Sword_2,
    Sword_4,
    Sword_8,
    Sword_16,



    RangedUnit,
    Bow_1,
    Bow_2,
    Bow_4,
    Bow_8,
    Bow_16,

    Rambo_4,
    Rambo_8,
    Rambo_16,

    MagicUnit,
    Bomb_1,
    Bomb_2,
    Bomb_4,
    Bomb_8,
    Bomb_16,

    SpearUnit,
    Spear_2,
    Spear_4,
    Spear_8,
    Spear_16,

    TransformUnit,
    Transform_2,
    Transform_4,
    Transform_8,
    Transform_16,

    SniperUnit,
    Sniper_2,
    Sniper_4,
    Sniper_8,
    Sniper_16,

    BuffUnit,
    DmgBuff_4,
    DmgBuff_8,
    DmgBuff_16,
    AtkspdBuff_4,
    AtkspdBuff_8,
    AtkspdBuff_16,
    BuffUnitEnd,

    UnitEnd,

    Button,


    //CS230
    Cat,
    Robot,
    Asteroid,
    Crates,
    Meteor,
    Ship,
    Floor,
    Portal,
    Count,
    Laser,
    Particle,

};

static std::string toString(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::MeleeUnit: return "MeleeUnit";
        case GameObjectTypes::Sword_1: return "Sword_1";
        case GameObjectTypes::Sword_2: return "Sword_2";
        case GameObjectTypes::Sword_4: return "Sword_4";
        case GameObjectTypes::Sword_8: return "Sword_8";
        case GameObjectTypes::Sword_16: return "Sword_16";

        case GameObjectTypes::RangedUnit: return "RangedUnit";
        case GameObjectTypes::Bow_1: return "Bow_1";
        case GameObjectTypes::Bow_2: return "Bow_2";
        case GameObjectTypes::Bow_4: return "Bow_4";
        case GameObjectTypes::Bow_8: return "Bow_8";
        case GameObjectTypes::Bow_16: return "Bow_16";

        case GameObjectTypes::Rambo_4: return "Rambo_4";
        case GameObjectTypes::Rambo_8: return "Rambo_8";
        case GameObjectTypes::Rambo_16: return "Rambo_16";

        case GameObjectTypes::MagicUnit: return "MagicUnit";
        case GameObjectTypes::Bomb_1: return "Bomb_1";
        case GameObjectTypes::Bomb_2: return "Bomb_2";
        case GameObjectTypes::Bomb_4: return "Bomb_4";
        case GameObjectTypes::Bomb_8: return "Bomb_8";
        case GameObjectTypes::Bomb_16: return "Bomb_16";

        case GameObjectTypes::SpearUnit: return "SpearUnit";
        case GameObjectTypes::Spear_2: return "Spear_2";
        case GameObjectTypes::Spear_4: return "Spear_4";
        case GameObjectTypes::Spear_8: return "Spear_8";
        case GameObjectTypes::Spear_16: return "Spear_16";

        case GameObjectTypes::TransformUnit: return "TransformUnit";
        case GameObjectTypes::Transform_2: return "Transform_2";
        case GameObjectTypes::Transform_4: return "Transform_4";
        case GameObjectTypes::Transform_8: return "Transform_8";
        case GameObjectTypes::Transform_16: return "Transform_16";

        case GameObjectTypes::SniperUnit: return "SniperUnit";
        case GameObjectTypes::Sniper_2: return "Sniper_2";
        case GameObjectTypes::Sniper_4: return "Sniper_4";
        case GameObjectTypes::Sniper_8: return "Sniper_8";
        case GameObjectTypes::Sniper_16: return "Sniper_16";

        case GameObjectTypes::BuffUnit: return "BuffUnit";
        case GameObjectTypes::DmgBuff_4: return "DmgBuff_4";
        case GameObjectTypes::DmgBuff_8: return "DmgBuff_8";
        case GameObjectTypes::DmgBuff_16: return "DmgBuff_16";
        case GameObjectTypes::AtkspdBuff_4: return "AtkspdBuff_4";
        case GameObjectTypes::AtkspdBuff_8: return "AtkspdBuff_8";
        case GameObjectTypes::AtkspdBuff_16: return "AtkspdBuff_16";
        case GameObjectTypes::BuffUnitEnd: return "BuffUnitEnd";

        default: return "Unknown";
    }
}

static const char* toStringPath(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::MeleeUnit: return "MeleeUnit";
        case GameObjectTypes::Sword_1: return "assets/buttons/sword.png";
        case GameObjectTypes::Sword_2: return "assets/buttons/sword.png";
        case GameObjectTypes::Sword_4: return "assets/buttons/sword.png";
        case GameObjectTypes::Sword_8: return "assets/buttons/sword.png";
        case GameObjectTypes::Sword_16: return "assets/buttons/sword.png";

        case GameObjectTypes::RangedUnit: return "RangedUnit";
        case GameObjectTypes::Bow_1: return "assets/buttons/bow.png";
        case GameObjectTypes::Bow_2: return "assets/buttons/bow.png";
        case GameObjectTypes::Bow_4: return "assets/buttons/bow.png";
        case GameObjectTypes::Bow_8: return "assets/buttons/bow.png";
        case GameObjectTypes::Bow_16: return "assets/buttons/bow.png";

        case GameObjectTypes::Rambo_4: return "assets/buttons/rapid.png";
        case GameObjectTypes::Rambo_8: return "assets/buttons/rapid.png";
        case GameObjectTypes::Rambo_16: return "assets/buttons/rapid.png";

        case GameObjectTypes::MagicUnit: return "MagicUnit";
        case GameObjectTypes::Bomb_1: return "assets/buttons/Bomb.png";
        case GameObjectTypes::Bomb_2: return "assets/buttons/Bomb.png";
        case GameObjectTypes::Bomb_4: return "assets/buttons/Bomb.png";
        case GameObjectTypes::Bomb_8: return "assets/buttons/Bomb.png";
        case GameObjectTypes::Bomb_16: return "assets/buttons/Bomb.png";

        case GameObjectTypes::SpearUnit: return "SpearUnit";
        case GameObjectTypes::Spear_2: return "assets/buttons/spear.png";
        case GameObjectTypes::Spear_4: return "assets/buttons/spear.png";
        case GameObjectTypes::Spear_8: return "assets/buttons/spear.png";
        case GameObjectTypes::Spear_16: return "assets/buttons/spear.png";

        case GameObjectTypes::TransformUnit: return "SpearUnit";
        case GameObjectTypes::Transform_2: return "assets/buttons/Transform.png";
        case GameObjectTypes::Transform_4: return "assets/buttons/Transform.png";
        case GameObjectTypes::Transform_8: return "assets/buttons/Transform.png";
        case GameObjectTypes::Transform_16: return "assets/buttons/Transform.png";

        case GameObjectTypes::SniperUnit: return "SniperUnit";
        case GameObjectTypes::Sniper_2: return "assets/buttons/sniper.png";
        case GameObjectTypes::Sniper_4: return "assets/buttons/sniper.png";
        case GameObjectTypes::Sniper_8: return "assets/buttons/sniper.png";
        case GameObjectTypes::Sniper_16: return "assets/buttons/sniper.png";

        case GameObjectTypes::BuffUnit: return "BuffUnit";
        case GameObjectTypes::DmgBuff_4: return "assets/buttons/AtkBuff.png";
        case GameObjectTypes::DmgBuff_8: return "assets/buttons/AtkBuff.png";
        case GameObjectTypes::DmgBuff_16: return "assets/buttons/AtkBuff.png";
        case GameObjectTypes::AtkspdBuff_4: return "assets/buttons/SpdBuff.png";
        case GameObjectTypes::AtkspdBuff_8: return "assets/buttons/SpdBuff.png";
        case GameObjectTypes::AtkspdBuff_16: return "assets/buttons/SpdBuff.png";
        case GameObjectTypes::BuffUnitEnd: return "BuffUnitEnd";

        default: return "Unknown";
    }
}