/*
 * Junyeong Cho
 * GAM200
 * Fall 2023
 * Original Author: Rudy Castan
 */

#pragma once

#include "not_null.h"

struct        SDL_Window;
typedef void* SDL_GLContext;
union         SDL_Event;

namespace ImGuiHelper
{
    void Initialize(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context);
    void FeedEvent(const SDL_Event& event);
    void Begin();
    void End(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context);
    void Shutdown();
}
