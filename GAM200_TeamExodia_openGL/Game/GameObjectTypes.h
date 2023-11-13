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

#pragma once

enum class GameObjectTypes
{
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


    //Exodia
    
    // Button
    Button,
    // Player
    Player,
    // Monsters
    Monster,
    Basic_Monster,
    Fast_Monster,
    Slow_Monster,
    Weak_Monster,
    // Tiles
    Tile,
    Pass__Tile,
    Block_Tile,
    // Towers
    Tower,
    Basic_Tower,
    Double_Tower,
    Triple_Tower,
    // Bullets
    Bullet,
};