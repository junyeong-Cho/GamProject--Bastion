/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    December 15, 2023
*/

#pragma once

#include <string>
#include <SDL.h>

#include "Engine/OriginPosition.h"
#include "Engine/Vec2.h"
#include "Engine/owner.h"  

#include "IProgram.h"

void on_window_resized(int, int);

namespace GAM200
{
    class Window
    {
    public:
        Window();
        ~Window();



        void Start(const char* title, int desired_width, int desired_height, OriginPosition position);
        void Update();

        Math::ivec2 GetSize();

        //void Clear(unsigned int color);

        void Clear(float red, float green, float blue, float alpha);

        void Clear(unsigned int color);

        bool IsDone() const noexcept;

        OriginPosition GetOriginPosition();

        //make get ptr_widow
        SDL_Window* GetSDLWindow() const noexcept;

        SDL_GLContext GetGLContext() const noexcept;

        void ForceResize(int desired_width, int desired_height) const;


    private:
        friend void ::on_window_resized(int, int);


        util::owner<IProgram*>     ptr_program = nullptr;
        SDL_Window* ptr_window = nullptr;
        SDL_GLContext               gl_context = nullptr;


        Math::ivec2 window_size;

        OriginPosition origin_position;


        const int default_width = 800;
        const int default_height = 600;

        int local_desired_width = 0;
        int local_desired_height = 0;


        bool is_done = false;


    };
}
