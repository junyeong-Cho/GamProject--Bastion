/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Wincow.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    December 15, 2023
*/

#include "Engine/Window.h"
#include "Engine/ImGuiHelper.h"
#include "Engine/Engine.h"

#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <filesystem>



namespace
{
    void hint_gl(SDL_GLattr attr, int value)
    {
        if (const auto success = SDL_GL_SetAttribute(attr, value); success != 0)
        {
            std::cerr << "Failed to Set GL Attribute: " << SDL_GetError() << '\n';
        }
    }


    template <typename... Messages> [[noreturn]] void throw_error_message(Messages&&... more_messages)
    {
        std::ostringstream stringOut;
        (stringOut << ... << more_messages);

        throw std::runtime_error{ stringOut.str() };
    }
}

namespace GAM200
{

    Window::Window() : origin_position{ OriginPosition::CENTER } { };


    Window::~Window()
    {

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(ptr_window);
        SDL_Quit();
    }


    void Window::Start(const char* title, int desired_width, int desired_height, OriginPosition position)
    {

        if (title == nullptr || title[0] == '\0')
        {
            throw_error_message("App title shouldn't be empty");
        }

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw_error_message("Failed to init SDK error: ", SDL_GetError());
        }



        hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        hint_gl(SDL_GL_DOUBLEBUFFER, true);
        hint_gl(SDL_GL_STENCIL_SIZE, 8);
        hint_gl(SDL_GL_DEPTH_SIZE, 24);
        hint_gl(SDL_GL_RED_SIZE, 8);
        hint_gl(SDL_GL_GREEN_SIZE, 8);
        hint_gl(SDL_GL_BLUE_SIZE, 8);
        hint_gl(SDL_GL_ALPHA_SIZE, 8);
        hint_gl(SDL_GL_MULTISAMPLEBUFFERS, 1);
        hint_gl(SDL_GL_MULTISAMPLESAMPLES, 4);


        desired_width = std::max(640, std::min(16384, desired_width));
        desired_height = std::max(480, std::min(16384, desired_height));

        origin_position = position;

        switch (origin_position)
        {
        case OriginPosition::LEFT_DOWN:

            glOrtho(0, desired_width, 0, desired_height, -1, 1);
            break;

        case OriginPosition::LEFT_UP:

            glOrtho(0, desired_width, desired_height, 0, -1, 1);
            break;

        case OriginPosition::RIGHT_DOWN:

            glOrtho(desired_width, 0, 0, desired_height, -1, 1);
            break;

        case OriginPosition::RIGHT_UP:

            glOrtho(desired_width, 0, desired_height, 0, -1, 1);
            break;

        case OriginPosition::CENTER:

            glOrtho(-desired_width / 2, desired_width / 2, -desired_height / 2, desired_height / 2, -1, 1);
            break;


        default:
            break;
        }


        ptr_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desired_width, desired_height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
        if (ptr_window == nullptr)
        {
            throw_error_message("Failed to create window: ", SDL_GetError());
        }

        gl_context = SDL_GL_CreateContext(ptr_window);
        if (gl_context == nullptr)
        {
            throw_error_message("Failed to create opengl context: ", SDL_GetError());
        }

        SDL_GL_MakeCurrent(ptr_window, gl_context);

        if (const auto result = glewInit(); GLEW_OK != result)
        {
            throw_error_message("Unable to initialize GLEW - error: ", glewGetErrorString(result));
        }


        constexpr int ADAPTIVE_VSYNC = -1;
        constexpr int VSYNC = 1;
        if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
        {
            SDL_GL_SetSwapInterval(VSYNC);
        }

        ImGuiHelper::Initialize(ptr_window, gl_context);


        int width = 0, height = 0;
        SDL_GL_GetDrawableSize(ptr_window, &width, &height);
        // ptr_program = create_program(width, height);

    }


    void Window::Update()
    {

        //        SDL_Event event{ 0 };

        SDL_GL_SwapWindow(ptr_window);


    }


    Math::ivec2 Window::GetSize()
    {
        int width = 0, height = 0;

        SDL_GL_GetDrawableSize(ptr_window, &width, &height);

        return Math::ivec2{ width, height };
    }

    void Window::Clear(float red, float green, float blue, float alpha)
    {
        red = std::clamp(red, 0.0f, 1.0f);
        green = std::clamp(green, 0.0f, 1.0f);
        blue = std::clamp(blue, 0.0f, 1.0f);
        alpha = std::clamp(alpha, 0.0f, 1.0f);

        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::Clear(unsigned int color)
    {
        float red = ((color >> 24) & 0xFF) / 255.0f;
        float green = ((color >> 16) & 0xFF) / 255.0f;
        float blue = ((color >> 8) & 0xFF) / 255.0f;
        float alpha = (color & 0xFF) / 255.0f;

        red = std::clamp(red, 0.0f, 1.0f);
        green = std::clamp(green, 0.0f, 1.0f);
        blue = std::clamp(blue, 0.0f, 1.0f);
        alpha = std::clamp(alpha, 0.0f, 1.0f);

        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    bool Window::IsDone() const noexcept
    {
        return is_done;
    }


    OriginPosition Window::GetOriginPosition()
    {
        return origin_position;
    }

    SDL_Window* Window::GetSDLWindow() const noexcept
    {
        return ptr_window;
    }

    SDL_GLContext Window::GetGLContext() const noexcept
    {
        return gl_context;
    }

    void Window::ForceResize(int desired_width, int desired_height) const
    {
        SDL_SetWindowSize(ptr_window, desired_width, desired_height);
    }




}
