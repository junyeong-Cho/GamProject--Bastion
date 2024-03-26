/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Hp_Boost_Gold_ui.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    December	15, 2023
*/

#pragma once

#include "../Engine/GameObject.h" 
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Texture.h"
#include "../Game/GameObjectTypes.h"

#include "../Game/Button.h"

class HBG_Ui : public GAM200::Component {
public:

    HBG_Ui();

    void Update();

    void Draw();

private:
};