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



GAM200::Font::Font(const std::filesystem::path& file_name)
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
    Math::ivec2 text_size = MeasureText(text);


    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    GLuint textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_size.x, text_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Engine::GetLogger().LogError("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


    Math::TransformationMatrix matrix;
    for (char c : text)
    {
        DrawChar(matrix, c);
    }

    // Framebuffer를 바인딩 해제하고 삭제.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDeleteFramebuffers(1, &framebuffer);

    // 텍스쳐 객체를 생성하고 반환.
    Texture* newTexture = new Texture(textureColorbuffer);

    return newTexture;
}

