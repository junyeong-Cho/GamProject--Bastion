#include "Image2D.h"

#include <GL/glew.h>
#include <iostream>
#include <string>

ShaderDrawing::Image::Image(const char* filename)
{
    stbi_set_flip_vertically_on_load(true);
    /// i_set_flip
    image = stbi_load(filename, &iwidth, &iheight, &ichannels, 4);
    if (!image)
    {
        std::cerr << "Failed to load image: " << filename << std::endl;
    }

#if !defined(__EMSCRIPTEN__)
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glTextureStorage2D(textureID, 1, GL_RGBA8, iwidth, iheight);
    glTextureSubImage2D(textureID, 0, 0, 0, iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, image);
#else
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidth, iheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
#endif

    stbi_image_free(image);
}

void ShaderDrawing::Image::DeleteTexture()
{
    glDeleteTextures(1, &textureID);
}
