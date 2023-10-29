/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 30, 2023
Updated:    October 30, 2023
*/



#include "Texture.h"
#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace GAM200 
{
    Texture::Texture(const std::filesystem::path& file_path) 
    {
        int width, height, channel;
        unsigned char* img = stbi_load(file_path.string().c_str(), &width, &height, &channel, 4);

        if (!img) 
        {
            std::cerr << "ERROR: Failed to load image: " << file_path << ". \n";
            throw std::runtime_error("Failed to load image: " + file_path.string());
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        imageSize.x = width;
        imageSize.y = height;

        stbi_image_free(img);
    }

    Texture::Texture(GLuint texID)
    {
        textureID = texID;
    }

    unsigned int Texture::GetPixel(Math::ivec2 texel)
    {
        if (texel.x < 0 || texel.x >= imageSize.x || texel.y < 0 || texel.y >= imageSize.y) 
        {
            std::cerr << "ERROR: Texel out of range: (" << texel.x << ", " << texel.y << ")\n";
            return 0;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);


        // 4바이트 RGBA 형식의 픽셀 데이터를 저장할 버퍼
        unsigned char pixelData[4];
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 1바이트 정렬


        // Y축 반전 - OpenGL은 왼쪽아래가 원점이므로
        int invertedY = imageSize.y - texel.y - 1;

        glReadPixels(texel.x, invertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);

        return (static_cast<int>(pixelData[0]) << 24) | // Red
            (static_cast<int>(pixelData[1]) << 16) |    // Green
            (static_cast<int>(pixelData[2]) << 8) |     // Blue
            (static_cast<int>(pixelData[3]));           // Alpha
    }



    void Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size) 
    {
        glPushMatrix();

        // 행렬 적용
        glMultMatrixf((GLfloat*)display_matrix.ToGLfloatArray());

        // 텍스쳐를 사용하여 그리기
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(texel_position.x, texel_position.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(texel_position.x + frame_size.x, texel_position.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(texel_position.x + frame_size.x, texel_position.y + frame_size.y);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(texel_position.x, texel_position.y + frame_size.y);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }

    void Texture::Draw(Math::TransformationMatrix display_matrix) 
    {
        Draw(display_matrix, Math::ivec2(0, 0), imageSize);
    }

    Math::ivec2 Texture::GetSize() 
    {
        return imageSize;
    }
}
