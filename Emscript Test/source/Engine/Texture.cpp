/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 10, 2023
*/

#define ifWantShader = true

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#endif


namespace GAM200
{

#if     !defined(__EMSCRIPTEN__) 
#pragma region Constructor & Destructer

    //direct drawing image constructor
#ifdef ifWantShader
    Texture::Texture(const std::filesystem::path& file_path)
    {
        shaderImage = Drawing::Image{ file_path.string().c_str() };
    }
#else
    Texture::Texture(const std::filesystem::path& file_path)
    {
        image = LoadImageFromFile(file_path);


        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        imageSize.x = imageWidth;
        imageSize.y = imageHeight;

        stbi_image_free(image);
        image = nullptr;

    }

#endif


    //font,text drawing image constructor
    Texture::Texture(const std::filesystem::path& file_path, Math::ivec2 text_size)
    {

        image = LoadImageFromFile(file_path);


        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_size.x, text_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);


        imageSize.x = text_size.x;
        imageSize.y = -text_size.y;

        stbi_image_free(image);
        image = nullptr;


    }

    //sprite constructor
    Texture::Texture(const std::filesystem::path& file_path, TextureType texturetype)
        : texturetype(texturetype)
    {
        image = LoadImageFromFile(file_path);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);


        imageSize.x = imageWidth;
        imageSize.y = imageHeight;

        stbi_image_free(image);
        image = nullptr;
    }

    //destructer
    Texture::~Texture()
    {
        if (textureID != 0)
        {
            glDeleteTextures(1, &textureID);
            textureID = 0;
        }
    }

#pragma endregion

    unsigned char* Texture::LoadImageFromFile(const std::filesystem::path& filePath)
    {
        if (!std::filesystem::exists(filePath))
        {
            std::cerr << "ERROR : No " << filePath << ". \n";
            throw std::runtime_error("File not found: " + filePath.string());
        }

        int width, height, channel;
        unsigned char* img = stbi_load(filePath.string().c_str(), &width, &height, &channel, 4);

        if (!img)
        {
            std::cerr << "ERROR: Failed to load image: " << filePath << ". \n";
            throw std::runtime_error("Failed to load image: " + filePath.string());
        }

        imageWidth = width;
        imageHeight = height;

        return img;
    }



#pragma region Drawing & Mapping
#ifdef ifWantShader
    void Texture::Draw(Math::TransformationMatrix display_matrix)
    {
        Drawing::push();
        Drawing::applyMatrix
        (
            display_matrix[0][0],
            display_matrix[0][1],
            display_matrix[0][2],
            display_matrix[1][0],
            display_matrix[1][1],
            display_matrix[1][2]
        );

        Drawing::draw_image(shaderImage, 0, 0, shaderImage.GetWidth(), shaderImage.GetHeight());
        Drawing::pop();
    }

    void Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size) 
    {
        Drawing::push();
        Drawing::applyMatrix(display_matrix[0][0], display_matrix[0][1], display_matrix[0][2], display_matrix[1][0], display_matrix[1][1], display_matrix[1][2]);
        Drawing::draw_image(shaderImage, 0, 0, texel_position.x, texel_position.y, static_cast<double>(frame_size.x), static_cast<double>(frame_size.y));

        Drawing::pop();
    } 
#else

    void Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Math::vec2 topLeft = Math::vec2(0, 0);
        Math::vec2 topRight = Math::vec2(frame_size.x, 0);
        Math::vec2 bottomLeft = Math::vec2(0, frame_size.y);
        Math::vec2 bottomRight = Math::vec2(frame_size.x, frame_size.y);

        Math::vec2 transformedTopLeft = display_matrix * topLeft;
        Math::vec2 transformedTopRight = display_matrix * topRight;
        Math::vec2 transformedBottomLeft = display_matrix * bottomLeft;
        Math::vec2 transformedBottomRight = display_matrix * bottomRight;

        DrawRect(transformedTopLeft, transformedTopRight, transformedBottomLeft, transformedBottomRight, texel_position, frame_size);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture::Draw(Math::TransformationMatrix display_matrix)
    {

        Draw(display_matrix, { 0, 0 }, imageSize);
    }
#endif

    //new version of texture mapping code
    void Texture::DrawRect(Math::vec2 topLeft, Math::vec2 topRight, Math::vec2 bottomLeft, Math::vec2 bottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size)
    {
        Engine::Instance().push();

        int windowWidth = Engine::GetWindow().GetSize().x;
        int windowHeight = Engine::GetWindow().GetSize().y;


        float textureWidth = static_cast<float>(GetSize().x);
        float textureHeight = static_cast<float>(GetSize().y);

        float tx1 = texel_position.x / textureWidth;
        float ty1 = texel_position.y / textureHeight;
        float tx2 = (texel_position.x + frame_size.x) / textureWidth;
        float ty2 = (texel_position.y + frame_size.y) / textureHeight;


        float nx1 = Math::NormalizeX(topLeft.x, windowWidth);
        float ny1 = Math::NormalizeY(topLeft.y, windowHeight);

        float nx2 = Math::NormalizeX(topRight.x, windowWidth);
        float ny2 = Math::NormalizeY(topRight.y, windowHeight);

        float nx3 = Math::NormalizeX(bottomRight.x, windowWidth);
        float ny3 = Math::NormalizeY(bottomRight.y, windowHeight);

        float nx4 = Math::NormalizeX(bottomLeft.x, windowWidth);
        float ny4 = Math::NormalizeY(bottomLeft.y, windowHeight);



        glBegin(GL_QUADS);

        glTexCoord2f(tx1, ty2); glVertex2f(nx1, ny1);
        glTexCoord2f(tx2, ty2); glVertex2f(nx2, ny2);
        glTexCoord2f(tx2, ty1); glVertex2f(nx3, ny3);
        glTexCoord2f(tx1, ty1); glVertex2f(nx4, ny4);

        glEnd();

        Engine::Instance().pop();
    }


    //old version of texture mapping code
    /*
    void Texture::DrawRect(Math::vec2 screenTopLeft, Math::vec2 screenBottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size)
    {

        Engine::Instance().push();

        int windowWidth = Engine::GetWindow().GetSize().x;
        int windowHeight = Engine::GetWindow().GetSize().y;

        float nx1 = Math::NormalizeX(screenTopLeft.x, windowWidth);
        float ny1 = Math::NormalizeY(screenTopLeft.y, windowHeight);
        float nx2 = Math::NormalizeX(screenBottomRight.x, windowWidth);
        float ny2 = Math::NormalizeY(screenBottomRight.y, windowHeight);

        float textureWidth = static_cast<float>(GetSize().x);
        float textureHeight = static_cast<float>(GetSize().y);

        float tx1 = texel_position.x / textureWidth;
        float ty1 = texel_position.y / textureHeight;
        float tx2 = (texel_position.x + frame_size.x) / textureWidth;
        float ty2 = (texel_position.y + frame_size.y) / textureHeight;

        glBegin(GL_QUADS);

        glTexCoord2f(tx1, ty2); glVertex2f(nx1, ny1);
        glTexCoord2f(tx2, ty2); glVertex2f(nx2, ny1);
        glTexCoord2f(tx2, ty1); glVertex2f(nx2, ny2);
        glTexCoord2f(tx1, ty1); glVertex2f(nx1, ny2);

        glEnd();

        Engine::Instance().pop();
    }
    */

#pragma endregion



    unsigned int Texture::GetPixel(Math::ivec2 texel)
    {


        //    int index = texel.y * GetSize().x + texel.x;


        glBindTexture(GL_TEXTURE_2D, textureID);

        unsigned char* localBuffer = new unsigned char[GetSize().x * GetSize().y * 4]; // assuming RGBA format
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

        unsigned int pixelData = *(unsigned int*)(localBuffer + (texel.y * GetSize().x + texel.x) * 4);

        delete[] localBuffer; 

        glBindTexture(GL_TEXTURE_2D, 0);

        return pixelData;
    }


    Math::ivec2 Texture::GetSize()
    {
        return{ imageSize.x, imageSize.y };
    }



#pragma region Drawing & Mapping for Direct Drawing 

    void Texture::Draw(int x, int y, int width, int height)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        //float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);


        switch (texturetype)
        {
        case GAM200::Texture::TextureType::RECTANGLE:
            DrawRect(x, y, x + width, y + height);

            break;

        case GAM200::Texture::TextureType::TRIANGLE:
            DrawTriangle(x, y, x + width, y, x + width / 2, y + height);

            break;
        case GAM200::Texture::TextureType::CIRCLE:
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture::Draw(int x, int y, float radius, int points)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);


        //float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        DrawCircle(x, y, radius, points);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture::DrawRect(int x1, int y1, int x2, int y2)
    {
        int GetwindowWidth = Engine::GetWindow().GetSize().x;
        int GetwindowHeight = Engine::GetWindow().GetSize().y;

        float aspectRatio = 1;


        float nx1 = Math::NormalizeX(x1, GetwindowWidth);
        float ny1 = Math::NormalizeY(y1, GetwindowHeight);
        float nx2 = Math::NormalizeX(x2, GetwindowWidth);
        float ny2 = Math::NormalizeY(y2, GetwindowHeight);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 1.0f); glVertex2f(nx1 * aspectRatio, ny1); // Bottom-left vertex
        glTexCoord2f(1.0f, 1.0f); glVertex2f(nx2 * aspectRatio, ny1); // Bottom-right vertex
        glTexCoord2f(1.0f, 0.0f); glVertex2f(nx2 * aspectRatio, ny2); // Top-right vertex
        glTexCoord2f(0.0f, 0.0f); glVertex2f(nx1 * aspectRatio, ny2); // Top-left vertex

        glEnd();
    }


    void Texture::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        int GetwindowWidth = Engine::GetWindow().GetSize().x;
        int GetwindowHeight = Engine::GetWindow().GetSize().y;

        float nx1 = Math::NormalizeX(x1, GetwindowWidth);
        float ny1 = Math::NormalizeY(y1, GetwindowHeight);
        float nx2 = Math::NormalizeX(x2, GetwindowWidth);
        float ny2 = Math::NormalizeY(y2, GetwindowHeight);
        float nx3 = Math::NormalizeX(x3, GetwindowWidth);
        float ny3 = Math::NormalizeY(y3, GetwindowHeight);


        glBegin(GL_TRIANGLES);

        //Texture coordinates and Vertex coordinates
        glTexCoord2f(0.0f, 1.0f); glVertex2f(nx1, ny1);

        glTexCoord2f(1.0f, 1.0f); glVertex2f(nx2, ny2);

        glTexCoord2f(0.5f, 0.0f); glVertex2f(nx3, ny3);


        glEnd();

    }


    void Texture::DrawCircle(int x, int y, float radius, int points)
    {

        int GetwindowWidth = Engine::GetWindow().GetSize().x;
        int GetwindowHeight = Engine::GetWindow().GetSize().y;

        //float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        float normalizeX = Math::NormalizeX(x, GetwindowWidth);
        float normalizeY = Math::NormalizeY(y, GetwindowHeight);
        float normalizeRadiusX = radius / (float)GetwindowWidth * 2.0f;
        float normalizeRadiusY = radius / (float)GetwindowHeight * 2.0f;

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 0.5f); glVertex2f(normalizeX, normalizeY);

        for (int i = 0; i <= points; i++)
        {
            float angle = i * 2.0f * 3.14159f / (float)points;
            float cosA = cosf(angle);
            float sinA = sinf(angle);

            glTexCoord2f(0.5f * cosA + 0.5f, 1.0f - (0.5f * sinA + 0.5f));
            glVertex2f
            (
                normalizeX + (normalizeRadiusX * cosA),
                normalizeY + (normalizeRadiusY * sinA)
            );
        }
        glEnd();


    }

#pragma endregion
#else


#endif

}