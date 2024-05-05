
#include "Image2D.h"

#include <iostream>
#include <GL/glew.h>


Drawing::Image::Image(const char* filename)
{
    stbi_set_flip_vertically_on_load(true);
    ///i_set_flip
    image = stbi_load(filename, &iwidth, &iheight, &ichannels, STBI_rgb_alpha);
    if (!image)
    {
        std::cerr << "Failed to load image: " << "abc.png" << std::endl;
    }
    else 
    {
        std::cout << iwidth << "," << iheight << std::endl;
    }
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glTextureStorage2D(textureID, 1, GL_RGBA8, iwidth, iheight);
    glTextureSubImage2D(textureID, 0, 0, 0, iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

}

void Drawing::Image::DeleteTexture()
{
    glDeleteTextures(1, &textureID);
}