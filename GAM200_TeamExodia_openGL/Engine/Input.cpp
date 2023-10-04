/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 5, 2023
Updated:    October 5, 2023
*/


#include "Input.h"
#include "Engine.h"

#include <SDL2/SDL.h>
#include "ImGuiHelper.h"

GAM200::Input::Input()
{
    keys_down.resize(static_cast<int>(Keys::Unknown));
    previous_keys_down.resize(static_cast<int>(Keys::Unknown));
}

void GAM200::Input::Update()
{

    //SDL_PollEvent를 내부에서 호출하며, HandleEvent는 키보드 이벤트만을 처리하게함
    //원래는 instance를 따로 받아오는 식이었으나 너무 느렸음...
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        ImGuiHelper::FeedEvent(event); 
        HandleEvent(event);
    }

    previous_keys_down = keys_down;
}


GAM200::Input::Keys convert_opengl_to_gam200(SDL_Keycode sdl_key)
{
    switch (sdl_key)
    {
    case SDLK_a:
	    return GAM200::Input::Keys::A;
    case SDLK_b:
        return GAM200::Input::Keys::B;
    case SDLK_c:
        return GAM200::Input::Keys::C;
    case SDLK_d:
        return GAM200::Input::Keys::D;
    case SDLK_e:
        return GAM200::Input::Keys::E;
    case SDLK_f:    
        return GAM200::Input::Keys::F;
	case SDLK_g:
		return GAM200::Input::Keys::G;
    case SDLK_h:
	    return GAM200::Input::Keys::H;
    case SDLK_i:
		return GAM200::Input::Keys::I;
	case SDLK_j:
        return GAM200::Input::Keys::J;
    case SDLK_k:
        return GAM200::Input::Keys::K;
    case SDLK_l:
        return GAM200::Input::Keys::L;
	case SDLK_m:
		return GAM200::Input::Keys::M;
	case SDLK_n:
		return GAM200::Input::Keys::N;
	case SDLK_o:
		return GAM200::Input::Keys::O;
	case SDLK_p:
        return GAM200::Input::Keys::P;
	case SDLK_q:
		return GAM200::Input::Keys::Q;
	case SDLK_r:
		return GAM200::Input::Keys::R;
	case SDLK_s:
		return GAM200::Input::Keys::S;
	case SDLK_t:
		return GAM200::Input::Keys::T;
	case SDLK_u:
		return GAM200::Input::Keys::U;
	case SDLK_v:
		return GAM200::Input::Keys::V;
	case SDLK_w:
		return GAM200::Input::Keys::W;
	case SDLK_x:
        return GAM200::Input::Keys::X;
    case SDLK_y:
		return GAM200::Input::Keys::Y;
	case SDLK_z:
        return GAM200::Input::Keys::Z;
    case SDLK_SPACE:
		return GAM200::Input::Keys::Space;
    case SDLK_RETURN:
        return GAM200::Input::Keys::Enter;
    case SDLK_LEFT:
        return GAM200::Input::Keys::Left;
    case SDLK_UP:
        return GAM200::Input::Keys::Up;
	case SDLK_RIGHT:
        return GAM200::Input::Keys::Right;
    case SDLK_DOWN:
        return GAM200::Input::Keys::Down;
    case SDLK_ESCAPE:
		return GAM200::Input::Keys::Escape;
    case SDLK_BACKQUOTE:
        return GAM200::Input::Keys::Tidle;

    }

    return GAM200::Input::Keys::Unknown;
}


void GAM200::Input::SetKeyDown(Keys key, bool value)
{
    keys_down[static_cast<int>(key)] = value;
}


void GAM200::Input::HandleEvent(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        Keys key = convert_opengl_to_gam200(event.key.keysym.sym);

        if (key != Keys::Unknown)
        {
            bool is_pressed = (event.type == SDL_KEYDOWN);

            if (is_pressed && event.key.repeat == 0)  
            {
                Engine::GetLogger().LogDebug("Key Pressed");
            }
            else if (!is_pressed)
            {
                Engine::GetLogger().LogDebug("Key Released");
            }

            SetKeyDown(key, is_pressed);
        }
    }
}


bool GAM200::Input::keyDown(Keys key)
{
    return keys_down[static_cast<int>(key)];
}

bool GAM200::Input::KeyJustPressed(Keys key)
{
    return keys_down[static_cast<int>(key)] == true && previous_keys_down[static_cast<int>(key)] == false;
}

bool GAM200::Input::KeyJustReleased(Keys key)
{
    return keys_down[static_cast<int>(key)] == false && previous_keys_down[static_cast<int>(key)] == true;
}



