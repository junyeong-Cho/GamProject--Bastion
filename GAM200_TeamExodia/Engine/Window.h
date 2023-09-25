/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    March 22, 2023
*/

#pragma once
#include <string>
#include <doodle/window.hpp>
#include "Vec2.h"



void on_window_resized(int, int);

namespace CS230
{
    class Window
    {
    public:
        void Start(std::string title);
        void Update();
        Math::ivec2 GetSize();
        void Clear(unsigned int color);

    private:
        friend void ::on_window_resized(int, int);

        static constexpr unsigned int default_background = UINT_MAX;


        Math::ivec2 window_size;
        const int default_width = 800;
        const int default_height = 600;
    };
}
