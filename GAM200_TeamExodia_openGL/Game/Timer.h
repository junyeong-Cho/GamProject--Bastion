/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Timer : public GAM200::Component
{
public:
    Timer(double max_time);

    void Set(double time_remaining);
    void Reset();
    void Update(double dt) override;


    double Remaining();
    int    RemainingInt();

    int GetRemainingTime() const;

    bool TickTock();

private:
    double current_time;
    double max_time;

    bool flicker;
};

