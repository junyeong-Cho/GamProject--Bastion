/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/


#pragma once

#include <doodle/drawing.hpp>
#include <string>


#include "Texture.h"
#include "Vec2.h"
#include "Rect.h"
#include "Rect.h"


namespace CS230
{
    class Font
    {
    public:
        Font(const std::filesystem::path& file_name);
        Texture PrintToTexture(std::string text, unsigned int color);

    private:
        void FindCharRects();

        Math::irect& GetCharRect(char c);
        Math::ivec2 MeasureText(std::string text);

        void DrawChar(Math::TransformationMatrix& matrix, char c);



        Texture texture;
        static constexpr int num_chars = 'z' - ' ' + 1;


        //글자의 위치와 크기를 담고 그리는 역할을 한다.
        Math::irect char_rects[num_chars];
    };
}




