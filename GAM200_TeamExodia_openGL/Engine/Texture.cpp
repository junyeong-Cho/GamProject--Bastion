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


#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



namespace GAM200 
{

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

    Texture::Texture(GLuint textureColorBuffer)
    {
        textureID = textureColorBuffer;
    }



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

    Texture::~Texture() 
    {
        if (image) 
        {
            stbi_image_free(image);
            image = nullptr;
        }
    }


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


    void Texture::Draw(int x, int y, int width, int height)
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


        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        DrawCircle(x, y, radius, points);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // 행렬 변환을 위한 코드 추가 (OpenGL은 행렬 스택을 사용)
        glPushMatrix();
        glMultMatrixf((GLfloat*) & display_matrix[0][0]);
        // 실제 텍스쳐 그리기
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(texel_position.x, texel_position.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(texel_position.x + frame_size.x, texel_position.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(texel_position.x + frame_size.x, texel_position.y + frame_size.y);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(texel_position.x, texel_position.y + frame_size.y);
        glEnd();
        // 행렬 스택 복원
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Draw(Math::TransformationMatrix display_matrix)
    {
        Draw(display_matrix, { 0, 0 }, imageSize);
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
   
        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

        float normalizeX       = Math::NormalizeX(x, GetwindowWidth);
        float normalizeY       = Math::NormalizeY(y, GetwindowHeight);
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


    unsigned int Texture::GetPixel(Math::ivec2 texel)
    {

        glBindTexture(GL_TEXTURE_2D, textureID);
        
        unsigned char pixelData[4];
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        int invertedY = imageSize.y - texel.y - 1;

        glReadPixels(texel.x, invertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);

        return 
            (static_cast<int>(pixelData[0]) << 24) |  //Red
            (static_cast<int>(pixelData[1]) << 16) |  //Green
            (static_cast<int>(pixelData[2]) << 8)  |  //Blue
            (static_cast<int>(pixelData[3]));		  //Alpha

    }


    Math::ivec2 Texture::GetSize()
    {
        int width, height;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glBindTexture(GL_TEXTURE_2D, 0);
        return { width, height };
    }

}  