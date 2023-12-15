/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Timer.h"



Timer::Timer(double max_time) : max_time(max_time), current_time(max_time)
{
    Set(max_time);
}


void Timer::Set(double time_remaining)
{
    max_time = time_remaining;

    Reset();

    flicker = false;

}

void Timer::Reset()
{
    current_time = max_time;
}

void Timer::Update(double dt)
{
    if (current_time > 0)
    {
        current_time -= dt;
        flicker = !flicker;


        if (current_time < 0)
        {
            current_time = 0;
        }
    }

}


double Timer::Remaining()
{
    return current_time;
}


int Timer::RemainingInt()
{
    return static_cast<int>(current_time);
}

int Timer::GetRemainingTime() const
{
    return static_cast<int>(current_time);
}



bool Timer::TickTock()
{
    return flicker;
}

