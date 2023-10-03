#pragma once
#include <string>
#include <SDL2/SDL.h>

#include "../Engine/OriginPosition.h"
#include "../Engine/Vec2.h"
  

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

        void Clear(unsigned int color);

        void Clear(float red, float green, float blue, float alpha);

        bool IsDone() const noexcept;

        OriginPosition GetOriginPosition();


    private:
        friend void ::on_window_resized(int, int);

        SDL_Window* ptr_window   = nullptr;
        SDL_GLContext gl_context = nullptr;
        

        Math::ivec2 window_size;
        
        OriginPosition origin_position;


        const int default_width = 800;
        const int default_height = 600;


        bool is_done = false;

    };
}
