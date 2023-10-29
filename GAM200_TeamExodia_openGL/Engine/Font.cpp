/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#include "Font.h"

#include "Engine.h"
#include "Logger.h"
#include "FrameBufferManager.h"


GAM200::Font::Font(const std::filesystem::path& file_name) : texture(file_name)
{
    const unsigned int white = 0xFFFFFFFF;

    unsigned int color = texture.GetPixel({ 0, 0 });

    if (color != white)
    {
        Engine::GetLogger().LogError("Font " + file_name.string() + " could not be loaded");

        return;
    }
    else
    {
        FindCharRects();
    }
}


void GAM200::Font::FindCharRects()
{
    unsigned int check_color = texture.GetPixel({ 0, 0 });
    unsigned int next_color;

    int height = texture.GetSize().y;

    int x = 1;
    for (int index = 0; index < num_chars; index++)
    {
        int width = 0;

        do
        {
            width++;
            next_color = texture.GetPixel({ x + width, 0 });
        } while (check_color == next_color);

        check_color = next_color;

        char_rects[index].point2 = { x + width - 1, 1 };
        char_rects[index].point1 = { x, char_rects[index].point2.y + height - 1 };
        x += width;
    }
}


Math::irect& GAM200::Font::GetCharRect(char c)
{
    if (c >= ' ' && c <= 'z')
    {
        return char_rects[c - ' '];
    }
    else
    {
        Engine::GetLogger().LogError("Char '" + std::to_string(c) + "' not found");
        return char_rects[0];
    }
}


void GAM200::Font::DrawChar(Math::TransformationMatrix& matrix, char c)
{
    Math::irect& display_rect = GetCharRect(c);

    Math::ivec2 top_left = { display_rect.point1.x, display_rect.point2.y };

    if (c != ' ')
    {
        texture.Draw(matrix, top_left, display_rect.Size());
    }

    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}


Math::ivec2 GAM200::Font::MeasureText(std::string text)
{
    Math::ivec2 size = { 0, 0 };
    Math::TransformationMatrix matrix;
    for (char c : text)
    {
        Math::irect& display_rect = GetCharRect(c);
        size.x += display_rect.Size().x;
        size.y = std::max(size.y, display_rect.Size().y);
    }
    return size;
}


GAM200::Texture GAM200::Font::PrintToTexture(std::string text, unsigned int color)
{
    Math::ivec2 text_size = MeasureText(text);

    FrameBuffer fbo(text_size.x, text_size.y);
    fbo.Bind();

    Math::TransformationMatrix matrix;
    glColor4ub((color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

    for (char c : text) {
        DrawChar(matrix, c);
    }

    fbo.Unbind();
    glColor4ub(255, 255, 255, 255);  // 기본 색상으로 복원

    return GAM200::Texture(fbo.GetTexture());
}
