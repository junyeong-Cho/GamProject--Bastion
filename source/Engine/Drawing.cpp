#include "Drawing.h"
#include <SDL_vulkan.h>

#include <array>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <ft2build.h>

#include FT_FREETYPE_H

#include <fstream>
#include <iostream>


ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::vertexShaderBox       = { "assets/shaders/box.vert", std::filesystem::last_write_time("assets/shaders/box.vert") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::fragmentShaderBox     = { "assets/shaders/box.frag", std::filesystem::last_write_time("assets/shaders/box.frag") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::vertexShaderCircle    = { "assets/shaders/circle.vert", std::filesystem::last_write_time("assets/shaders/circle.vert") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::fragmentShaderCircle  = { "assets/shaders/circle.frag", std::filesystem::last_write_time("assets/shaders/circle.frag") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::vertexShaderTexture   = { "assets/shaders/texture.vert", std::filesystem::last_write_time("assets/shaders/texture.vert") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::fragmentShaderTexture = { "assets/shaders/texture.frag", std::filesystem::last_write_time("assets/shaders/texture.frag") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::vertexShaderFont      = { "assets/shaders/font.vert", std::filesystem::last_write_time("assets/shaders/font.vert") };
ShaderDrawing::ShaderDraw::ShaderFile ShaderDrawing::ShaderDraw::fragmentShaderFont    = { "assets/shaders/font.frag", std::filesystem::last_write_time("assets/shaders/font.frag") };

std::string loadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderDrawing::ShaderDraw::checkAndReloadShaders()
{
    auto reloadShader = [](ShaderFile& vertexShaderFile, ShaderFile& fragmentShaderFile, GLModel& model)
    {
        auto currentVertexWriteTime   = std::filesystem::last_write_time(vertexShaderFile.path);
        auto currentFragmentWriteTime = std::filesystem::last_write_time(fragmentShaderFile.path);

        if (currentVertexWriteTime != vertexShaderFile.lastWriteTime || currentFragmentWriteTime != fragmentShaderFile.lastWriteTime)
        {
            vertexShaderFile.lastWriteTime   = currentVertexWriteTime;
            fragmentShaderFile.lastWriteTime = currentFragmentWriteTime;

            model.reloadShaders(vertexShaderFile.path, fragmentShaderFile.path);

            Engine::GetLogger().LogDebug(vertexShaderFile.path + " and " + fragmentShaderFile.path + " reloaded.");
        }
    };

    reloadShader(vertexShaderBox, fragmentShaderBox, box);
    reloadShader(vertexShaderCircle, fragmentShaderCircle, circle);
    reloadShader(vertexShaderTexture, fragmentShaderTexture, textureBox);
    reloadShader(vertexShaderFont, fragmentShaderFont, fontBox);
}

void ShaderDrawing::ShaderDraw::GLModel::reloadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::string vertexShaderSource   = loadShaderSource(vertexShaderPath);
    std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);
    GLuint      vertexShader         = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint      fragmentShader       = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    GLuint newProgram = createShaderProgram(vertexShader, fragmentShader);
    if (newProgram)
    {
        glDeleteProgram(shdr_pgm);
        shdr_pgm = newProgram;
    }
}

void ShaderDrawing::ShaderDraw::updateShaders()
{
    checkAndReloadShaders();
}

ShaderDrawing::ShaderDraw::GLModel ShaderDrawing::ShaderDraw::box;
ShaderDrawing::ShaderDraw::GLModel ShaderDrawing::ShaderDraw::circle;
ShaderDrawing::ShaderDraw::GLModel ShaderDrawing::ShaderDraw::textureBox;
ShaderDrawing::ShaderDraw::GLModel ShaderDrawing::ShaderDraw::fontBox;
glm::vec4                          ShaderDrawing::ShaderDraw::color{ 1.0f, 1.0f, 1.0f, 1.0f };
glm::vec4                          ShaderDrawing::ShaderDraw::previous_color;

glm::vec4 ShaderDrawing::ShaderDraw::outlineColor{ 0.f, 0.f, 0.f, 1.0f };
glm::vec4 ShaderDrawing::ShaderDraw::previous_Outlinecolor;

GLfloat   ShaderDrawing::ShaderDraw::ar;
glm::mat3 ShaderDrawing::ShaderDraw::camwin_to_ndc_xform;
glm::mat3 ShaderDrawing::ShaderDraw::world_to_ndc_xform;
glm::mat3 ShaderDrawing::ShaderDraw::view_xform[2];
glm::mat3 ShaderDrawing::ShaderDraw::reset_view_xform[2];
glm::mat3 ShaderDrawing::ShaderDraw::privous_view_xform[2];
glm::mat3 ShaderDrawing::ShaderDraw::apply_Matrix{ 1.f };
glm::mat3 ShaderDrawing::ShaderDraw::previous_Matrix;

//std::map<char, ShaderDrawing::ShaderDraw::Character> ShaderDrawing::ShaderDraw::Characters;

bool ShaderDrawing::ShaderDraw::isfill          = true;
bool ShaderDrawing::ShaderDraw::previous_isfill = true;

unsigned int ShaderDrawing::ShaderDraw::current_image_mode       = 0;
unsigned int ShaderDrawing::ShaderDraw::current_rectangle_mode   = 0;
unsigned int ShaderDrawing::ShaderDraw::previous_image_mode      = 0;
unsigned int ShaderDrawing::ShaderDraw::previous_rectangle_mode  = 0;
unsigned int ShaderDrawing::ShaderDraw::current_coordinate_mode  = 0;
unsigned int ShaderDrawing::ShaderDraw::previous_coordinate_mode = 0;

std::map<std::string, ShaderDrawing::ShaderDraw::Font> ShaderDrawing::ShaderDraw::Fonts;
std::string                                            ShaderDrawing::ShaderDraw::currentFont = "";

void ShaderDrawing::ShaderDraw::initFont()
{
    initFont("assets/font/Maplestory_Light.ttf");
    initFont("assets/font/Eina01-Bold.ttf");
    initFont("assets/font/Eina01-SemiBold.ttf");
}


void ShaderDrawing::ShaderDraw::initFont(const std::string& fontPath)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }



    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font " << fontPath << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 40);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font newFont;
    newFont.face = face;

    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph " << c << std::endl;
            continue;
        }

        GLuint texture;
        glCreateTextures(GL_TEXTURE_2D, 1, &texture);
        glTextureStorage2D(texture, 1, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
        glTextureSubImage2D(texture, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        Character character = { texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                static_cast<unsigned int>(face->glyph->advance.x) };
        newFont.Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    Fonts[fontPath] = newFont;

    if (currentFont.empty())
    {
        currentFont = fontPath;
    }

    FT_Done_FreeType(ft);

    GLuint vao;
    glCreateVertexArrays(1, &vao);

    GLuint buffer;
    glCreateBuffers(1, &buffer);

    glNamedBufferStorage(buffer, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayVertexBuffer(vao, 0, buffer, 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);

    ShaderDraw::fontBox.vaoid[0] = vao;
    ShaderDraw::fontBox.vboid[0] = buffer;

    std::string vertexShaderSource   = readShaderFile("assets/shaders/font.vert");
    std::string fragmentShaderSource = readShaderFile("assets/shaders/font.frag");
    GLuint      vertexShader         = fontBox.compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint      fragmentShader       = fontBox.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    fontBox.shdr_pgm = fontBox.createShaderProgram(vertexShader, fragmentShader);
}

void ShaderDrawing::ShaderDraw::setFont(const std::string& fontPath)
{
    if (Fonts.find(fontPath) != Fonts.end())
    {
        currentFont = fontPath;
    }
    else
    {
        std::cout << "Font not loaded: " << fontPath << std::endl;
    }
}

std::string ShaderDrawing::ShaderDraw::readShaderFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderDrawing::ShaderDraw::setBoxModel()
{
    std::vector<glm::vec2> pos_vtx = {
        { 0.5f, -0.5f},
        { 0.5f,  0.5f},
        {-0.5f,  0.5f},
        {-0.5f, -0.5f}
    };

    GLuint VBO;
    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, sizeof(glm::vec2) * pos_vtx.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(VBO, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());

    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);

    std::vector<GLushort> idx_vtx = { 0, 1, 2, 2, 3, 0 };
    GLuint                EBO;
    glCreateBuffers(1, &EBO);
    glNamedBufferStorage(EBO, sizeof(GLushort) * idx_vtx.size(), idx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(VAO, EBO);
    glBindVertexArray(0);

    std::string vertexShaderSource   = loadShaderSource("assets/shaders/box.vert");
    std::string fragmentShaderSource = loadShaderSource("assets/shaders/box.frag");
    GLuint      vertexShader         = box.compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint      fragmentShader       = box.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    box.shdr_pgm = box.createShaderProgram(vertexShader, fragmentShader);

    box.draw_cnt       = 6;
    box.primitive_cnt  = 4;
    box.vaoid[0]       = VAO;
    box.primitive_type = GL_TRIANGLES;

    std::vector<glm::vec2> pos_vtx2 = {
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f}
    };

    GLuint VBO1;
    glCreateBuffers(1, &VBO1);
    glNamedBufferStorage(VBO1, sizeof(glm::vec2) * pos_vtx2.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(VBO1, 0, sizeof(glm::vec2) * pos_vtx2.size(), pos_vtx2.data());

    GLuint VAO1;
    glCreateVertexArrays(1, &VAO1);
    glEnableVertexArrayAttrib(VAO1, 0);
    glVertexArrayVertexBuffer(VAO1, 0, VBO1, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(VAO1, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO1, 0, 0);
    glVertexArrayElementBuffer(VAO1, EBO);
    glBindVertexArray(0);

    box.vaoid[1] = VAO1;
}

void ShaderDrawing::ShaderDraw::setCircleModel()
{
    const int              count    = 30 + 1;
    std::vector<glm::vec2> cpos_vtx = {
        {0, 0}
    };

    float offset = 360.0f / 30.0f;
    for (int i = 1; i < count; i++)
    {
        float  degree  = i * offset;
        double radians = degree * 3.14159 / 180.0;
        cpos_vtx.push_back({ cos(radians), sin(radians) });
    }

    GLuint cVBO;
    glCreateBuffers(1, &cVBO);
    glNamedBufferStorage(cVBO, sizeof(glm::vec2) * cpos_vtx.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(cVBO, 0, sizeof(glm::vec2) * cpos_vtx.size(), cpos_vtx.data());

    GLuint cVAO;
    glCreateVertexArrays(1, &cVAO);
    glEnableVertexArrayAttrib(cVAO, 0);
    glVertexArrayVertexBuffer(cVAO, 0, cVBO, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(cVAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(cVAO, 0, 0);

    std::vector<GLushort> cidx_vtx;
    for (GLushort i = 0; i < count; i++)
    {
        cidx_vtx.push_back(i);
    }
    cidx_vtx.push_back(1);
    cidx_vtx.push_back(1);

    GLuint cebo_hdl;
    glCreateBuffers(1, &cebo_hdl);
    glNamedBufferStorage(cebo_hdl, sizeof(GLushort) * cidx_vtx.size(), cidx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(cVAO, cebo_hdl);
    glBindVertexArray(0);

    std::string vertexShaderSource   = loadShaderSource("assets/shaders/circle.vert");
    std::string fragmentShaderSource = loadShaderSource("assets/shaders/circle.frag");
    GLuint      vertexShader         = circle.compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint      fragmentShader       = circle.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    circle.shdr_pgm = circle.createShaderProgram(vertexShader, fragmentShader);

    circle.primitive_type = GL_TRIANGLE_FAN;
    circle.primitive_cnt  = 30;
    circle.vaoid[0]       = cVAO;
    circle.draw_cnt       = static_cast<GLuint>(cidx_vtx.size());
}

void ShaderDrawing::ShaderDraw::setTextureModel()
{
    std::vector<glm::vec2> tpos_vtx = {
        {-.5f,  .5f},
        { .5f,  .5f},
        {-.5f, -.5f},
        { .5f, -.5f}
    };
    std::vector<glm::vec2> tpos_tex = {
        {0.f, 1.f},
        {1.f, 1.f},
        {0.f, 0.f},
        {1.f, 0.f}
    };

    GLuint tVBO;
    glCreateBuffers(1, &tVBO);
    glNamedBufferStorage(tVBO, sizeof(glm::vec2) * tpos_vtx.size() + sizeof(glm::vec2) * tpos_tex.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(tVBO, 0, sizeof(glm::vec2) * tpos_vtx.size(), tpos_vtx.data());
    glNamedBufferSubData(tVBO, sizeof(glm::vec2) * tpos_vtx.size(), sizeof(glm::vec2) * tpos_tex.size(), tpos_tex.data());

    GLuint tVAO;
    glCreateVertexArrays(1, &tVAO);
    glEnableVertexArrayAttrib(tVAO, 0);
    glVertexArrayVertexBuffer(tVAO, 0, tVBO, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(tVAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(tVAO, 0, 0);

    glEnableVertexArrayAttrib(tVAO, 1);
    glVertexArrayVertexBuffer(tVAO, 1, tVBO, sizeof(glm::vec2) * tpos_vtx.size(), sizeof(glm::vec2));
    glVertexArrayAttribFormat(tVAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(tVAO, 1, 1);

    std::array<GLushort, 4> tidx_vtx = { 0, 2, 1, 3 };

    GLuint tEBO;
    glCreateBuffers(1, &tEBO);
    glNamedBufferStorage(tEBO, sizeof(GLushort) * tidx_vtx.size(), tidx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(tVAO, tEBO);
    glBindVertexArray(0);

    std::string vertexShaderSource   = loadShaderSource("assets/shaders/texture.vert");
    std::string fragmentShaderSource = loadShaderSource("assets/shaders/texture.frag");
    GLuint      vertexShader         = textureBox.compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    GLuint      fragmentShader       = textureBox.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    textureBox.shdr_pgm = textureBox.createShaderProgram(vertexShader, fragmentShader);

    textureBox.primitive_type = GL_TRIANGLE_STRIP;
    textureBox.primitive_cnt  = 4;
    textureBox.draw_cnt       = static_cast<GLuint>(tidx_vtx.size());
    textureBox.vaoid[0]       = tVAO;

    std::vector<glm::vec2> tpos_vtx2 = {
        {.0f, 1.f},
        {1.f, 1.f},
        {.0f, .0f},
        {1.f, .0f}
    };

    GLuint tVBO2;
    glCreateBuffers(1, &tVBO2);
    glNamedBufferStorage(tVBO2, sizeof(glm::vec2) * tpos_vtx2.size() + sizeof(glm::vec2) * tpos_tex.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(tVBO2, 0, sizeof(glm::vec2) * tpos_vtx2.size(), tpos_vtx2.data());
    glNamedBufferSubData(tVBO2, sizeof(glm::vec2) * tpos_vtx2.size(), sizeof(glm::vec2) * tpos_tex.size(), tpos_tex.data());

    GLuint tVAO2;
    glCreateVertexArrays(1, &tVAO2);
    glEnableVertexArrayAttrib(tVAO2, 0);
    glVertexArrayVertexBuffer(tVAO2, 0, tVBO2, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(tVAO2, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(tVAO2, 0, 0);

    glEnableVertexArrayAttrib(tVAO2, 1);
    glVertexArrayVertexBuffer(tVAO2, 1, tVBO2, sizeof(glm::vec2) * tpos_vtx2.size(), sizeof(glm::vec2));
    glVertexArrayAttribFormat(tVAO2, 1, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(tVAO2, 1, 1);
    textureBox.vaoid[1] = tVAO2;
    glVertexArrayElementBuffer(tVAO2, tEBO);
    glBindVertexArray(0);

    textureBox.vboid[0] = tVBO;
    textureBox.vboid[1] = tVBO2;
}

void ShaderDrawing::ShaderDraw::init(SDL_Window* pWindow)
{
    setBoxModel();
    setCircleModel();
    setTextureModel();

    GLsizei fb_width, fb_height;
    SDL_Vulkan_GetDrawableSize(pWindow, &fb_width, &fb_height);
    ar = static_cast<GLfloat>(fb_width) / fb_height;

    view_xform[0]                   = glm::mat3{ 1.f };
    ShaderDraw::view_xform[0][2][0] = 0.0f;
    ShaderDraw::view_xform[0][2][1] = 0.0f;
    reset_view_xform[0]             = view_xform[0];

    view_xform[1]       = glm::mat3{ 1.f };
    view_xform[1][2][0] = static_cast<float>(-fb_width / 2);
    view_xform[1][2][1] = static_cast<float>(-fb_height / 2);
    reset_view_xform[1] = view_xform[1];

    camwin_to_ndc_xform       = glm::mat3{ 1.f };
    camwin_to_ndc_xform[0][0] = 2 / static_cast<float>(ar * fb_height);
    camwin_to_ndc_xform[1][1] = 2 / static_cast<float>(fb_height);

    world_to_ndc_xform = camwin_to_ndc_xform * view_xform[ShaderDraw::current_coordinate_mode];
}

GLuint ShaderDrawing::ShaderDraw::GLModel::compileShader(unsigned int shaderType, const char* sourceCode)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, log.data());
        std::cerr << "Shader compile error:\n" << log.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint ShaderDrawing::ShaderDraw::GLModel::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            std::vector<char> errorLog(logLength + 1);
            glGetProgramInfoLog(program, logLength, NULL, &errorLog[0]);
            std::cerr << "Shader program linking failed: " << &errorLog[0] << std::endl;
        }
        else
        {
            std::cerr << "Shader program linking failed with no error log." << std::endl;
        }
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

void ShaderDrawing::draw_box(float x, float y, float width, float height)
{
    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(width);
    scaleMat[1][1] = static_cast<float>(height);
    glm::mat3 rotateMat{ 1.f };
    rotateMat[0][0] = cos(.0f);
    rotateMat[1][0] = -sin(.0f);
    rotateMat[0][1] = sin(.0f);
    rotateMat[1][1] = cos(.0f);
    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (transApplyMatrix * translateMat * ShaderDraw::apply_Matrix * scaleMat);

    glUseProgram(ShaderDraw::box.shdr_pgm);
    glBindVertexArray(ShaderDraw::box.vaoid[ShaderDraw::current_rectangle_mode]);
    GLint uniform_var_loc1 = glGetUniformLocation(ShaderDraw::box.shdr_pgm, "uModelToNDC");
    if (uniform_var_loc1 >= 0)
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    GLint uniformOutlinedColor = glGetUniformLocation(ShaderDraw::box.shdr_pgm, "color");
    if (uniformOutlinedColor >= 0)
    {
        glUniform4f(uniformOutlinedColor, ShaderDraw::outlineColor.x, ShaderDraw::outlineColor.y, ShaderDraw::outlineColor.z, ShaderDraw::outlineColor.w);
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    glLineWidth(1.5f);
    glDrawElements(GL_LINE_LOOP, ShaderDraw::box.draw_cnt, GL_UNSIGNED_SHORT, NULL);

    if (ShaderDraw::isfill == true)
    {
        GLint uniformColor = glGetUniformLocation(ShaderDraw::box.shdr_pgm, "color");
        if (uniformColor >= 0)
        {
            glUniform4f(uniformColor, ShaderDraw::color.x, ShaderDraw::color.y, ShaderDraw::color.z, ShaderDraw::color.w);
        }
        else
        {
            std::cout << "Uniform variable doesn't exist!!!\n";
            std::exit(EXIT_FAILURE);
        }
        glLineWidth(1.0f);
        glDrawElements(ShaderDraw::box.primitive_cnt, ShaderDraw::box.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    }
    glBindVertexArray(0);
    glUseProgram(0);
}

void ShaderDrawing::draw_circle(int x, int y, int width, int height)
{
    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(width);
    scaleMat[1][1] = static_cast<float>(height);
    glm::mat3 rotateMat{ 1.f };
    rotateMat[0][0] = cos(.0f);
    rotateMat[1][0] = -sin(.0f);
    rotateMat[0][1] = sin(.0f);
    rotateMat[1][1] = cos(.0f);
    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (transApplyMatrix * translateMat * ShaderDraw::apply_Matrix * scaleMat);

    glUseProgram(ShaderDraw::circle.shdr_pgm);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(ShaderDraw::circle.vaoid[0]);
    GLint uniform_var_loc1 = glGetUniformLocation(ShaderDraw::circle.shdr_pgm, "uModelToNDC");
    if (uniform_var_loc1 >= 0)
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLint uniformOutlinedColor = glGetUniformLocation(ShaderDraw::box.shdr_pgm, "color");
    if (uniformOutlinedColor >= 0)
    {
        glUniform4f(uniformOutlinedColor, ShaderDraw::outlineColor.x, ShaderDraw::outlineColor.y, ShaderDraw::outlineColor.z, ShaderDraw::outlineColor.w);
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    glLineWidth(1.5f);
    glDrawElements(GL_LINE_STRIP_ADJACENCY, ShaderDraw::circle.draw_cnt, GL_UNSIGNED_SHORT, NULL);

    if (ShaderDraw::isfill == true)
    {
        GLint uniformColor = glGetUniformLocation(ShaderDraw::circle.shdr_pgm, "color");
        if (uniformColor >= 0)
        {
            glUniform4f(uniformColor, ShaderDraw::color.x, ShaderDraw::color.y, ShaderDraw::color.z, ShaderDraw::color.w);
        }
        else
        {
            std::cout << "Uniform variable doesn't exist!!!\n";
            std::exit(EXIT_FAILURE);
        }
        glLineWidth(1.0f);
        glDrawElements(ShaderDraw::circle.primitive_type, ShaderDraw::circle.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    }
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void ShaderDrawing::draw_image(Image& image, int x, int y, int width, int height)
{
    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(width);
    scaleMat[1][1] = static_cast<float>(height);

    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (transApplyMatrix * translateMat * ShaderDraw::apply_Matrix * scaleMat);

    glUseProgram(ShaderDraw::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);

    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(ShaderDraw::textureBox.vaoid[ShaderDraw::current_image_mode]);
    GLint uniform_var_loc1 = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uModelToNDC");

    if (uniform_var_loc1 >= 0)
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLuint tex_loc = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0)
    {
        glUniform1i(tex_loc, 1);
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    glDrawElements(ShaderDraw::textureBox.primitive_type, ShaderDraw::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void ShaderDrawing::draw_image_freely(Image& image, int x, int y, int width, int height)
{
    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(width) / image.GetWidth();
    scaleMat[1][1] = static_cast<float>(height) / image.GetHeight();

    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (transApplyMatrix * translateMat * ShaderDraw::apply_Matrix * scaleMat);

    glUseProgram(ShaderDraw::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);

    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(ShaderDraw::textureBox.vaoid[ShaderDraw::current_image_mode]);
    GLint uniform_var_loc1 = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uModelToNDC");

    if (uniform_var_loc1 >= 0)
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cerr << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLuint tex_loc = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0)
    {
        glUniform1i(tex_loc, 1);
    }
    else
    {
        std::cerr << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    glDrawElements(ShaderDraw::textureBox.primitive_type, ShaderDraw::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glUseProgram(0);
}

void ShaderDrawing::push()
{
    ShaderDraw::privous_view_xform[ShaderDraw::current_coordinate_mode] = ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode];
    ShaderDraw::previous_color                                          = ShaderDraw::color;
    ShaderDraw::previous_Outlinecolor                                   = ShaderDraw::outlineColor;
    ShaderDraw::previous_Matrix                                         = ShaderDraw::apply_Matrix;
    ShaderDraw::previous_image_mode                                     = ShaderDraw::current_image_mode;
    ShaderDraw::previous_rectangle_mode                                 = ShaderDraw::current_rectangle_mode;
    ShaderDraw::previous_coordinate_mode                                = ShaderDraw::current_coordinate_mode;
    ShaderDraw::previous_isfill                                         = ShaderDraw::isfill;
}

void ShaderDrawing::pop()
{
    ShaderDraw::current_coordinate_mode                         = ShaderDraw::previous_coordinate_mode;
    ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode] = ShaderDraw::privous_view_xform[ShaderDraw::current_coordinate_mode];
    ShaderDraw::color                                           = ShaderDraw::previous_color;
    ShaderDraw::outlineColor                                    = ShaderDraw::previous_Outlinecolor;
    ShaderDraw::apply_Matrix                                    = ShaderDraw::previous_Matrix;
    ShaderDraw::current_image_mode                              = ShaderDraw::previous_image_mode;
    ShaderDraw::current_rectangle_mode                          = ShaderDraw::previous_rectangle_mode;
    ShaderDraw::isfill                                          = ShaderDraw::previous_isfill;
    ShaderDraw::world_to_ndc_xform                              = ShaderDraw::camwin_to_ndc_xform * ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode];
}

void ShaderDrawing::translateView(float x, float y)
{
    glm::mat3 translate{ 1.f };
    translate[2][0] = x;
    translate[2][1] = y;
    ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode] *= translate;
    ShaderDraw::world_to_ndc_xform = ShaderDraw::camwin_to_ndc_xform * ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode];
}

void ShaderDrawing::set_color(int red, int green, int blue, int alpha)
{
    ShaderDraw::color = glm::vec4{ red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f };
}

void ShaderDrawing::applyMatrix(float a, float b, float c, float d, float e, float f)
{
    ShaderDraw::apply_Matrix[0][0] = a;
    ShaderDraw::apply_Matrix[1][0] = b;
    ShaderDraw::apply_Matrix[2][0] = c;
    ShaderDraw::apply_Matrix[0][1] = d;
    ShaderDraw::apply_Matrix[1][1] = e;
    ShaderDraw::apply_Matrix[2][1] = f;

    ShaderDraw::apply_Matrix[2][2] = 1;
}

void ShaderDrawing::set_rectangle_mode(DrawOriginMode mode)
{
    ShaderDraw::current_rectangle_mode = static_cast<unsigned int>(mode);
}

void ShaderDrawing::set_image_mode(DrawOriginMode mode)
{
    ShaderDraw::current_image_mode = static_cast<unsigned int>(mode);
}

void ShaderDrawing::set_coordinate_mode(CoordinateSystem mode)
{
    ShaderDraw::current_coordinate_mode = static_cast<unsigned int>(mode);
    ShaderDraw::world_to_ndc_xform      = ShaderDraw::camwin_to_ndc_xform * ShaderDraw::view_xform[ShaderDraw::current_coordinate_mode];
}

void ShaderDrawing::draw_image(ShaderDrawing::Image& image, int x, int y, int texelX, int texelY, int texelWidth, int texelHeight)
{
    std::vector<glm::vec2> tpos_vtx;
    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY)) / static_cast<float>(image.GetHeight()) });

    tpos_vtx.push_back(
        glm::vec2{ (static_cast<float>(texelX + texelWidth) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY)) / static_cast<float>(image.GetHeight()) });
    tpos_vtx.push_back(
        glm::vec2{ (static_cast<float>(texelX) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY - texelHeight)) / static_cast<float>(image.GetHeight()) });
    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX + texelWidth) / static_cast<float>(image.GetWidth())),
                                  static_cast<float>((image.GetHeight() - texelY - texelHeight)) / static_cast<float>(image.GetHeight()) });

    glNamedBufferSubData(ShaderDraw::textureBox.vboid[ShaderDraw::current_image_mode], sizeof(glm::vec2) * 4, sizeof(glm::vec2) * tpos_vtx.size(), tpos_vtx.data());

    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(texelWidth);
    scaleMat[1][1] = static_cast<float>(texelHeight);

    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (transApplyMatrix * translateMat * ShaderDraw::apply_Matrix * scaleMat);

    glUseProgram(ShaderDraw::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(ShaderDraw::textureBox.vaoid[ShaderDraw::current_image_mode]);
    GLint uniform_var_loc1 = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uModelToNDC");
    if (uniform_var_loc1 >= 0)
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLuint tex_loc = glGetUniformLocation(ShaderDraw::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0)
    {
        glUniform1i(tex_loc, 1);
    }
    else
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    glDrawElements(ShaderDraw::textureBox.primitive_type, ShaderDraw::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);
    std::vector<glm::vec2> tpos_tex;
    tpos_tex.push_back({ 0.f, 1.f });
    tpos_tex.push_back({ 1.f, 1.f });
    tpos_tex.push_back({ 0.f, 0.f });
    tpos_tex.push_back({ 1.f, 0.f });
    glNamedBufferSubData(ShaderDraw::textureBox.vboid[ShaderDraw::current_image_mode], sizeof(glm::vec2) * 4, sizeof(glm::vec2) * tpos_tex.size(), tpos_tex.data());
}

void ShaderDrawing::set_fill(bool set)
{
    ShaderDrawing::ShaderDraw::isfill = set;
}

void ShaderDrawing::set_line_color(int red, int green, int blue, int alpha)
{
    ShaderDraw::outlineColor = glm::vec4{ red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f };
}

void ShaderDrawing::draw_text(std::string text, float x, float y, float scale, float r, float g, float b, float a)
{
    glUseProgram(ShaderDraw::fontBox.shdr_pgm);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
    transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

    ShaderDraw::apply_Matrix[2][0] = 0;
    ShaderDraw::apply_Matrix[2][1] = 0;
    glBindVertexArray(ShaderDraw::fontBox.vaoid[0]);
    glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (translateMat);

    GLint check = glGetUniformLocation(ShaderDraw::fontBox.shdr_pgm, "uModelToNDC");
    if (check >= 0)
    {
        glUniformMatrix3fv(check, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else
    {
        std::cout << "model Uniform doesn't exist!!! \n";
        std::exit(EXIT_FAILURE);
    }

    glUniform4f(glGetUniformLocation(ShaderDraw::fontBox.shdr_pgm, "textColor"), r, g, b, a);

    glActiveTexture(GL_TEXTURE0);

    scale = scale / 40;

    float firstX = -x / 2;
    float X      = 0;
    float Y      = 0;

    for (auto c = text.begin(); c != text.end(); c++)
    {
        ShaderDrawing::ShaderDraw::Character ch   = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
        GLfloat                              xpos = X + ch.Bearing.x * scale;
        GLfloat                              ypos = Y - (ch.Size.y - ch.Bearing.y) * scale;
        X += (ch.Advance >> 6) * scale;
    }
    X      = -X / 2;
    firstX = X;

    for (auto c = text.begin(); c != text.end(); c++)
    {
        if (*c != '\n')
        {
            ShaderDrawing::ShaderDraw::Character ch   = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
            GLfloat                              xpos = X + ch.Bearing.x * scale;
            GLfloat                              ypos = Y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w               = ch.Size.x * scale;
            GLfloat h               = ch.Size.y * scale;
            GLfloat vertices[6 * 4] = { xpos, ypos + h, 0.0f, 0.0f, xpos,     ypos, 0.0f, 1.0f, xpos + w, ypos,     1.0f, 1.0f,

                                        xpos, ypos + h, 0.0f, 0.0f, xpos + w, ypos, 1.0f, 1.0f, xpos + w, ypos + h, 1.0f, 0.0f };

            glNamedBufferSubData(ShaderDraw::fontBox.vboid[0], 0, sizeof(GLfloat) * 6 * 4, vertices);
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            X += (ch.Advance >> 6) * scale;
        }
        else if (*c == '\n')
        {
            ShaderDrawing::ShaderDraw::Character ch = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
            GLfloat                              h  = ch.Size.y * scale + 5.0f;
            Y -= h;
            X = firstX;
        }
    }
    glBindVertexArray(0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

    void ShaderDrawing::draw_text(std::string text, float x, float y, float scale, double radians, float r, float g, float b)
    {
        glUseProgram(ShaderDraw::fontBox.shdr_pgm);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glm::mat3 translateMat{ 1.f };
        translateMat[0][0] = 1.f;
        translateMat[1][1] = 1.f;
        translateMat[2][2] = 1.f;
        translateMat[2][0] = static_cast<float>(x);
        translateMat[2][1] = static_cast<float>(y);

        glm::mat3 rotateMat{ 1.f };
        rotateMat[0][0] = cos(radians);
        rotateMat[1][0] = -sin(radians);
        rotateMat[0][1] = sin(radians);
        rotateMat[1][1] = cos(radians);

        glm::mat3 transApplyMatrix{ 1.f };
        transApplyMatrix[2][0] = ShaderDraw::apply_Matrix[2][0];
        transApplyMatrix[2][1] = ShaderDraw::apply_Matrix[2][1];

        ShaderDraw::apply_Matrix[2][0] = 0;
        ShaderDraw::apply_Matrix[2][1] = 0;
        glBindVertexArray(ShaderDraw::fontBox.vaoid[0]);
        glm::mat3 mdl_to_ndc_xform = ShaderDraw::world_to_ndc_xform * (translateMat * rotateMat * transApplyMatrix);

        GLint check = glGetUniformLocation(ShaderDraw::fontBox.shdr_pgm, "uModelToNDC");
        if (check >= 0)
        {
            glUniformMatrix3fv(check, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
        }
        else
        {
            std::cout << "model Uniform doesn't exist!!! \n";
            std::exit(EXIT_FAILURE);
        }

        glUniform3f(glGetUniformLocation(ShaderDraw::fontBox.shdr_pgm, "textColor"), r, g, b);

        glActiveTexture(GL_TEXTURE0);

        scale = scale / 40;

        float firstX = -x / 2;
        float X      = 0;
        float Y      = 0;

        std::vector<float> set = { 0.0f };
        int                i   = 0;

        for (auto c = text.begin(); c != text.end(); c++)
        {
            if (*c != '\n')
            {
                ShaderDrawing::ShaderDraw::Character ch   = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
                GLfloat                              xpos = set[i] + ch.Bearing.x * scale;
                GLfloat                              ypos = Y - (ch.Size.y - ch.Bearing.y) * scale;
                set[i] += (ch.Advance >> 6) * scale;
            }
            else if (*c == '\n')
            {
                i++;
                set.push_back(0.0f);
            }
        }
        X           = set[0];
        size_t size = set.size();
        for (size_t i = 0; i < size; i++)
        {
            if (set[i] > X)
            {
                X = set[i];
            }
        }
        X      = -X / 2;
        firstX = X;

        for (auto c = text.begin(); c != text.end(); c++)
        {
            if (*c != '\n')
            {
                ShaderDrawing::ShaderDraw::Character ch   = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
                GLfloat                              xpos = X + ch.Bearing.x * scale;
                GLfloat                              ypos = Y - (ch.Size.y - ch.Bearing.y) * scale;

                GLfloat w               = ch.Size.x * scale;
                GLfloat h               = ch.Size.y * scale;
                GLfloat vertices[6 * 4] = { xpos, ypos + h, 0.0f, 0.0f, xpos,     ypos, 0.0f, 1.0f, xpos + w, ypos,     1.0f, 1.0f,

                                            xpos, ypos + h, 0.0f, 0.0f, xpos + w, ypos, 1.0f, 1.0f, xpos + w, ypos + h, 1.0f, 0.0f };

                glNamedBufferSubData(ShaderDraw::fontBox.vboid[0], 0, sizeof(GLfloat) * 6 * 4, vertices);
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                X += (ch.Advance >> 6) * scale;
            }
            else if (*c == '\n')
            {
                ShaderDrawing::ShaderDraw::Character ch = ShaderDrawing::ShaderDraw::Fonts[ShaderDrawing::ShaderDraw::currentFont].Characters[*c];
                GLfloat                              h  = ch.Size.y * scale + 5.0f;
                Y -= h;
                X = firstX;
            }
        }

        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

void ShaderDrawing::EndWIndow()
{
    glDeleteBuffers(1, &ShaderDraw::box.vaoid[0]);
    glDeleteBuffers(1, &ShaderDraw::box.vaoid[1]);
    glDeleteBuffers(1, &ShaderDraw::box.vboid[0]);
    glDeleteBuffers(1, &ShaderDraw::box.vboid[1]);

    glDeleteBuffers(1, &ShaderDraw::textureBox.vaoid[0]);
    glDeleteBuffers(1, &ShaderDraw::textureBox.vaoid[1]);
    glDeleteBuffers(1, &ShaderDraw::textureBox.vboid[0]);
    glDeleteBuffers(1, &ShaderDraw::textureBox.vboid[1]);

    glDeleteBuffers(1, &ShaderDraw::circle.vaoid[0]);
    glDeleteBuffers(1, &ShaderDraw::circle.vaoid[1]);
    glDeleteBuffers(1, &ShaderDraw::circle.vboid[0]);
    glDeleteBuffers(1, &ShaderDraw::circle.vboid[1]);

    glDeleteBuffers(1, &ShaderDraw::fontBox.vaoid[0]);
    glDeleteBuffers(1, &ShaderDraw::fontBox.vaoid[1]);
    glDeleteBuffers(1, &ShaderDraw::fontBox.vboid[0]);
    glDeleteBuffers(1, &ShaderDraw::fontBox.vboid[1]);
}