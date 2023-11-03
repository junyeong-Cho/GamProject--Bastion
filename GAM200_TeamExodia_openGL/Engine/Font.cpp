/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Font.h"
#include "Logger.h"
#include "Engine.h"



#include "../Engine/Texture.h"



GAM200::Font::Font(const std::filesystem::path& file_name) : file_names(file_name)
{
    const unsigned int white = 0xFFFFFFFF;

    texture = new Texture(file_name);

    unsigned int color = texture->GetPixel({ 0, 0 });

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
    unsigned int check_color = texture->GetPixel({ 0, 0 });
    unsigned int next_color;

    int height = texture->GetSize().y;

    int x = 1;
    for (int index = 0; index < num_chars; index++)
    {
        int width = 0;

        do
        {
            width++;
            next_color = texture->GetPixel({ x + width, 0 });
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
        texture->Draw(matrix, top_left, display_rect.Size());
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



GAM200::Texture* GAM200::Font::PrintToTexture(std::string text, unsigned int color)
{
    Engine::Instance().push();

    Math::ivec2 text_size = MeasureText(text);


    float R = ((color >> 24) & 0xFF) / 255.0f; 
    float G = ((color >> 16) & 0xFF) / 255.0f; 
    float B = ((color >> 8) & 0xFF)  / 255.0f;  
    float A = (color & 0xFF)         / 255.0f;         


    glColor4f(R, G, B, A);


    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    Texture* newTexture = new Texture(file_names, text_size);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newTexture->getTextureID(), 0);


    Math::TransformationMatrix matrix;
    for (char c : text)
    {
        DrawChar(matrix, c);
    }


    glBindFramebuffer(GL_FRAMEBUFFER, 0);  // FBO 바인드 해제
    glDeleteFramebuffers(1, &fbo);         // FBO 삭제

    return newTexture;

    Engine::Instance().pop();
}

