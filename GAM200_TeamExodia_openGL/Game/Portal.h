/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Portal.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/


#pragma once

#include "../Engine/GameObjectManager.h"


#include "../Game/GameObjectTypes.h"

#include "../Engine/Rect.h"


class Portal : public GAM200::GameObject
{
public:

    Portal(int to_state, Math::irect boundary);
    std::string TypeName() override { return "Portal"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal; }

    void GoToState();

private:
    int to_state;
};

