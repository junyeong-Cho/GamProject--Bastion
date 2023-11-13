/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Portal.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"


#include "../Game/GameObjectTypes.h"


class Portal : public CS230::GameObject 
{
public:
    
    Portal(int to_state, Math::irect boundary);
    std::string TypeName() override { return "Portal"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal; }

    void GoToState();

private:
    int to_state;
};

