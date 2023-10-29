/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 10, 2023
*/


#include "TextureWithShape.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



namespace GAM200 
{

    TextureWithShape::TextureWithShape(const std::filesystem::path& file_path, TextureType texturetype)
		: texturetype(texturetype)
    {
        image = LoadImageFromFile(file_path);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(image);  
        image = nullptr;
    }

    TextureWithShape::~TextureWithShape()
    {
        if (image) 
        {
            stbi_image_free(image);
            image = nullptr;
        }
    }


    unsigned char* TextureWithShape::LoadImageFromFile(const std::filesystem::path& filePath)
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


    void TextureWithShape::Draw(int x, int y, int width, int height)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        /*
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f * aspectRatio, -0.5f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f * aspectRatio, -0.5f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f * aspectRatio, 0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f * aspectRatio, 0.5f);
        glEnd();
        */
        //DrawRect(x, y, x + width, y + height);
        
        switch (texturetype)
        {
        case GAM200::TextureWithShape::TextureType::RECTANGLE:
            DrawRect(x, y, x + width, y + height);

            break;

        case GAM200::TextureWithShape::TextureType::TRIANGLE:
            DrawTriangle(x, y, x + width, y, x + width / 2, y + height);

            break;
        case GAM200::TextureWithShape::TextureType::CIRCLE:
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }



    void TextureWithShape::Draw(int x, int y, float radius, int points)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);


        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        DrawCircle(x, y, radius, points);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void TextureWithShape::DrawRect(int x1, int y1, int x2, int y2)
    {
        float aspectRatio = 1;


        float nx1 = Math::NormalizeX(x1, windowWidth);
        float ny1 = Math::NormalizeY(y1, windowHeight);
        float nx2 = Math::NormalizeX(x2, windowWidth);
        float ny2 = Math::NormalizeY(y2, windowHeight);

        glBegin(GL_QUADS);    

        glTexCoord2f(0.0f, 1.0f); glVertex2f(nx1 * aspectRatio, ny1); // Bottom-left vertex
        glTexCoord2f(1.0f, 1.0f); glVertex2f(nx2 * aspectRatio, ny1); // Bottom-right vertex
        glTexCoord2f(1.0f, 0.0f); glVertex2f(nx2 * aspectRatio, ny2); // Top-right vertex
        glTexCoord2f(0.0f, 0.0f); glVertex2f(nx1 * aspectRatio, ny2); // Top-left vertex

        glEnd();              
    }


    void TextureWithShape::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        float nx1 = Math::NormalizeX(x1, windowWidth);
        float ny1 = Math::NormalizeY(y1, windowHeight);
        float nx2 = Math::NormalizeX(x2, windowWidth);
        float ny2 = Math::NormalizeY(y2, windowHeight);
        float nx3 = Math::NormalizeX(x3, windowWidth);
        float ny3 = Math::NormalizeY(y3, windowHeight);

    
        glBegin(GL_TRIANGLES);  

        //Texture coordinates and Vertex coordinates
        glTexCoord2f(0.0f, 1.0f); glVertex2f(nx1, ny1);

        glTexCoord2f(1.0f, 1.0f); glVertex2f(nx2, ny2);

        glTexCoord2f(0.5f, 0.0f); glVertex2f(nx3, ny3);


        glEnd();  

    }

    void TextureWithShape::DrawCircle(int x, int y, float radius, int points)
    {
   
        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        float normalizeX       = Math::NormalizeX(x, windowWidth);
        float normalizeY       = Math::NormalizeY(y, windowHeight);
        float normalizeRadiusX = radius / (float)windowWidth * 2.0f;
        float normalizeRadiusY = radius / (float)windowHeight * 2.0f;

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

}  