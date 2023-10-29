#include <GLHandle.h>

namespace GAM200 
{
    class FrameBuffer 
    {
    public:
        FrameBuffer(int width, int height);
        ~FrameBuffer();

        void Bind();
        void Unbind();

        GLuint GetTexture() const { return textureID; }

    private:
        GLuint fboID;
        GLuint textureID;
    };
}

GAM200::FrameBuffer::FrameBuffer(int width, int height)
{
    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GAM200::FrameBuffer::~FrameBuffer()
{
    glDeleteTextures(1, &textureID);
    glDeleteFramebuffers(1, &fboID);
}

void GAM200::FrameBuffer::Bind() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void GAM200::FrameBuffer::Unbind() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
