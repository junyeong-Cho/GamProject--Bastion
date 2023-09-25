/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"

#include "../Game/GameObjectTypes.h"


class Floor : public CS230::GameObject 
{
public:
    Floor(Math::irect boundary);
    std::string TypeName() override { return "Floor"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Floor; }
};
