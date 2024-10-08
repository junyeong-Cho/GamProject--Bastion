/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.h
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#pragma once

#include "Engine/Component.h"

namespace GAM200 {
    class ShowCollision : public GAM200::Component
    {
    public:
        ShowCollision();
        void Update(double dt) override;
        bool Enabled();

    private:
        bool enabled;
    };
}