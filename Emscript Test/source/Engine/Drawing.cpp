#include "Drawing.h"

#include <SDL_vulkan.h>


#include <vector>
#include <array>
#include <sstream>
#include <GL/glew.h>


Drawing::DrawApp::GLModel Drawing::DrawApp::box;
Drawing::DrawApp::GLModel Drawing::DrawApp::circle;
Drawing::DrawApp::GLModel Drawing::DrawApp::textureBox;
Drawing::DrawApp::GLModel Drawing::DrawApp::fontBox;
glm::vec4 Drawing::DrawApp::color{ 1.0f,1.0f,1.0f,1.0f };
glm::vec4 Drawing::DrawApp::previous_color;

glm::vec4 Drawing::DrawApp::outlineColor{ 0.f, 0.f, 0.f, 1.0f };
glm::vec4 Drawing::DrawApp::previous_Outlinecolor;

GLfloat Drawing::DrawApp::ar;
glm::mat3 Drawing::DrawApp::camwin_to_ndc_xform;
glm::mat3 Drawing::DrawApp::world_to_ndc_xform;
glm::mat3 Drawing::DrawApp::view_xform[2];
glm::mat3 Drawing::DrawApp::reset_view_xform[2];
glm::mat3 Drawing::DrawApp::privous_view_xform[2];
glm::mat3 Drawing::DrawApp::apply_Matrix{ 1.f };
glm::mat3 Drawing::DrawApp::previous_Matrix;

std::map<char, Drawing::DrawApp::Character> Drawing::DrawApp::Characters;

bool Drawing::DrawApp::isfill = true;
bool Drawing::DrawApp::previous_isfill = true;

unsigned int Drawing::DrawApp::current_image_mode = 0;
unsigned int Drawing::DrawApp::current_rectangle_mode = 0;
unsigned int Drawing::DrawApp::previous_image_mode = 0;
unsigned int Drawing::DrawApp::previous_rectangle_mode = 0;
unsigned int Drawing::DrawApp::current_coordinate_mode = 0;
unsigned int Drawing::DrawApp::previous_coordinate_mode = 0;

int Drawing::DrawApp::task = 0;
int Drawing::DrawApp::previous_task = 0;

const char* vertexShaderSource = R"(
    #version 410
layout (location = 0) in vec2 vVertexPosition;

uniform mat3 uModelToNDC;
void main() {
gl_Position = vec4(vec2(uModelToNDC * vec3(vVertexPosition, 1.f)), 0.0,
1.0);
}
)";

const char* fragmentShaderSource = "#version 410\n"
"uniform vec4 color;\n"
"out vec4 fFragClr;\n"
"void main()\n"
"{\n"
"   fFragClr = color;\n"
"}\n\0";


const char* vertexTextureShader = R"(
#version 410

layout (location=0) in vec2 vVertexPosition;
layout (location=1) in vec2 vVertexTexturePosition;

layout (location=0) out vec2 vTexCoord;

uniform mat3 uModelToNDC;

void main() {
  gl_Position = vec4(vec2(uModelToNDC * vec3(vVertexPosition, 1.f)), 0.0, 1.0);
  vTexCoord = vVertexTexturePosition;
}
)";

const char* fragmentTextureShader = R"(
#version 410

layout(location=0) in vec2 vTexCoord;
uniform int task;
uniform sampler2D uTex2d;

layout (location=0) out vec4 fFragClr;
void main () 
{
    fFragClr = texture(uTex2d, vTexCoord);
    if(task == 1)
    {
        //fFragClr *= vec4(0.35f * fFragClr.x / 1.0f * fFragClr.w / 1.0f ,0.35f* fFragClr.y / 1.0f* fFragClr.w / 1.0f ,0.35f* fFragClr.z / 1.0f* fFragClr.w / 1.0f,1.f );
        fFragClr *= vec4(1.0f * fFragClr.w / 1.0f , 0.65f* fFragClr.w / 1.0f,  fFragClr.z,1.f );
        
    }
    else if(task == 2)
    {
        fFragClr *= vec4(0.3f * fFragClr.x / 1.0f * fFragClr.w / 1.0f ,0.3f* fFragClr.y / 1.0f* fFragClr.w / 1.0f ,fFragClr.z,1.f );
    }   
    
}
)";

const char* fontVertexShader = R"(
#version 410
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

uniform mat3 uModelToNDC;

layout (location=0) out vec2 TexCoords;




void main()
{
    gl_Position = vec4(vec2(uModelToNDC * vec3(vertex.xy, 1.0)), 0.0, 1.0);
    TexCoords = vertex.zw;
}  
)";

const char* fontFragmentShader = R"(
#version 410
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
} 
)";




void Drawing::DrawApp::setBoxModel()
{
    std::vector<glm::vec2> pos_vtx;
    pos_vtx.push_back({ 0.5f,-0.5f });
    pos_vtx.push_back({ 0.5f,0.5f });
    pos_vtx.push_back({ -0.5f,0.5f });
    pos_vtx.push_back({ -0.5f,-0.5f });




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

    std::vector<GLushort> idx_vtx{ 0, 1, 2, 2, 3, 0 };


    GLuint EBO;
    glCreateBuffers(1, &EBO);
    glNamedBufferStorage(EBO,
        sizeof(GLushort) * idx_vtx.size(),
        idx_vtx.data(),
        GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(VAO, EBO);
    glBindVertexArray(0);
    GLuint vertexShader = box.compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = box.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // 셰이더 프로그램 생성 및 링크
    box.shdr_pgm = box.createShaderProgram(vertexShader, fragmentShader);


    box.draw_cnt = 6;
    box.primitive_cnt = 4;
    box.vaoid[0] = VAO;
    box.primitive_type = GL_TRIANGLES;

    std::vector<glm::vec2> pos_vtx2;
    pos_vtx2.push_back({ 1.0f,0.0f });
    pos_vtx2.push_back({ 1.0f,1.0f });
    pos_vtx2.push_back({ 0.0f,1.0f });
    pos_vtx2.push_back({ 0.0f,0.0f });
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

void Drawing::DrawApp::setCircleModel()
{
    int const count{ 30 + 1 };
    std::vector<glm::vec2> cpos_vtx;
    float offset = 360 / static_cast<float>(30);
    cpos_vtx.push_back({ 0,0 });
    for (int i = 1; i < count; i++)
    {
        float degree = i * offset;
        double radians = degree * 3.14159 / 180;
        cpos_vtx.push_back({ cos(radians), sin(radians) });
    }




    GLuint cVBO;
    glCreateBuffers(1, &cVBO);
    glNamedBufferStorage(cVBO,
        sizeof(glm::vec2) * cpos_vtx.size(),
        nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(cVBO, 0,
        sizeof(glm::vec2) * cpos_vtx.size(), cpos_vtx.data());

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
    glNamedBufferStorage(cebo_hdl,
        sizeof(GLushort) * cidx_vtx.size(),
        cidx_vtx.data(),
        GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(cVAO, cebo_hdl);
    glBindVertexArray(0);

    circle.primitive_type = GL_TRIANGLE_FAN;
    circle.primitive_cnt = 30;

    circle.vaoid[0] = cVAO;
    circle.draw_cnt = static_cast<GLuint>(cidx_vtx.size());
    GLuint cvertexShader = circle.compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint cfragmentShader = circle.compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    circle.shdr_pgm = circle.createShaderProgram(cvertexShader, cfragmentShader);
}


void Drawing::DrawApp::setTextureModel()
{
    std::vector<glm::vec2> tpos_vtx;
    std::vector<glm::vec2> tpos_tex;
    tpos_vtx.push_back({ -.5f,.5f }); tpos_tex.push_back({ 0.f,1.f });
    tpos_vtx.push_back({ .5f,.5f }); tpos_tex.push_back({ 1.f,1.f });
    tpos_vtx.push_back({ -.5f,-.5f }); tpos_tex.push_back({ 0.f,0.f });
    tpos_vtx.push_back({ .5f,-.5f }); tpos_tex.push_back({ 1.f,0.f });



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


    std::array<GLushort, 4> tidx_vtx;

    tidx_vtx[0] = { 0 };
    tidx_vtx[1] = { 2 };
    tidx_vtx[2] = { 1 };
    tidx_vtx[3] = { 3 };


    GLuint tEBO;
    glCreateBuffers(1, &tEBO);
    glNamedBufferStorage(tEBO,
        sizeof(GLushort) * tidx_vtx.size(),
        tidx_vtx.data(),
        GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(tVAO, tEBO);
    glBindVertexArray(0);

    GLuint tvertexShader = textureBox.compileShader(GL_VERTEX_SHADER, vertexTextureShader);
    GLuint tfragmentShader = textureBox.compileShader(GL_FRAGMENT_SHADER, fragmentTextureShader);
    textureBox.shdr_pgm = textureBox.createShaderProgram(tvertexShader, tfragmentShader);

    textureBox.primitive_type = GL_TRIANGLE_STRIP;
    textureBox.primitive_cnt = 4;
    textureBox.draw_cnt = static_cast<GLuint>(tidx_vtx.size());
    textureBox.vaoid[0] = tVAO;

    std::vector<glm::vec2> tpos_vtx2;
    tpos_vtx2.push_back({ .0f,1.f });
    tpos_vtx2.push_back({ 1.f,1.f });
    tpos_vtx2.push_back({ .0f,.0f });
    tpos_vtx2.push_back({ 1.f,.0f });

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
    glVertexArrayVertexBuffer(tVAO2, 1, tVBO2, sizeof(glm::vec2) * tpos_vtx.size(), sizeof(glm::vec2));
    glVertexArrayAttribFormat(tVAO2, 1, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(tVAO2, 1, 1);
    textureBox.vaoid[1] = tVAO2;
    glVertexArrayElementBuffer(tVAO2, tEBO);
    glBindVertexArray(0);

    textureBox.vboid[0] = tVBO;
    textureBox.vboid[1] = tVBO2;


}


void Drawing::DrawApp::init(SDL_Window* pWindow)
{
    setBoxModel();
    setCircleModel();
    setTextureModel();




    GLsizei fb_width, fb_height;
    SDL_Vulkan_GetDrawableSize(pWindow, &fb_width, &fb_height);
    ar = static_cast<GLfloat>(fb_width) / fb_height;

    view_xform[0] = glm::mat3{ 1.f };
    DrawApp::view_xform[0][2][0] = 0.0f;
    DrawApp::view_xform[0][2][1] = 0.0f;

    reset_view_xform[0] = view_xform[0];


    view_xform[1] = glm::mat3{ 1.f };
    view_xform[1][2][0] = static_cast<float>(-fb_width / 2);
    view_xform[1][2][1] = static_cast<float>(-fb_height / 2);

    reset_view_xform[1] = view_xform[1];



    camwin_to_ndc_xform = glm::mat3{ 1.f };
    camwin_to_ndc_xform[0][0] = 2 / static_cast<float>(ar * fb_height);
    camwin_to_ndc_xform[1][1] = 2 / static_cast<float>(fb_height);


    world_to_ndc_xform = camwin_to_ndc_xform * view_xform[DrawApp::current_coordinate_mode];

}



GLuint Drawing::DrawApp::GLModel::compileShader(unsigned int shaderType, const char* sourceCode) 
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    // 컴파일 상태 확인
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) 
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, log.data());

        std::cerr << "Shader 컴파일 오류:\n" << log.data() << std::endl;

        glDeleteShader(shader);

        return 0;
    }
    return shader;
}


// 셰이더 프로그램 생성 및 링크 함수
GLuint Drawing::DrawApp::GLModel::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) 
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // 링크 결과 확인
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




void Drawing::draw_box(float x, float y, float width, float height)
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
    transApplyMatrix[2][0] = DrawApp::apply_Matrix[2][0];
    transApplyMatrix[2][1] = DrawApp::apply_Matrix[2][1];

    DrawApp::apply_Matrix[2][0] = 0;
    DrawApp::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * (transApplyMatrix * translateMat * DrawApp::apply_Matrix * scaleMat);


    //glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * translateMat * rotateMat * scaleMat * DrawApp::apply_Matrix;;

    glUseProgram(DrawApp::box.shdr_pgm);
    glBindVertexArray(DrawApp::box.vaoid[DrawApp::current_rectangle_mode]);
    GLint uniform_var_loc1 =
        glGetUniformLocation(DrawApp::box.shdr_pgm,
            "uModelToNDC");
    if (uniform_var_loc1 >= 0) {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE,
            glm::value_ptr(mdl_to_ndc_xform));
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    GLint uniformOutlinedColor =
        glGetUniformLocation(DrawApp::box.shdr_pgm,
            "color");
    if (uniformOutlinedColor >= 0) {
        glUniform4f(uniformOutlinedColor, DrawApp::outlineColor.x, DrawApp::outlineColor.y, DrawApp::outlineColor.z, DrawApp::outlineColor.w);
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    glLineWidth(1.5f);
    glDrawElements(GL_LINE_LOOP, DrawApp::box.draw_cnt, GL_UNSIGNED_SHORT, NULL);

    if (DrawApp::isfill == true)
    {
        GLint uniformColor =
            glGetUniformLocation(DrawApp::box.shdr_pgm,
                "color");
        if (uniformColor >= 0) 
        {
            glUniform4f(uniformColor, DrawApp::color.x, DrawApp::color.y, DrawApp::color.z, DrawApp::color.w);
        }
        else 
        {
            std::cout << "Uniform variable doesn't exist!!!\n";
            std::exit(EXIT_FAILURE);
        }
        glLineWidth(1.0f);
        glDrawElements(DrawApp::box.primitive_cnt, DrawApp::box.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    }
    glBindVertexArray(0);
    glUseProgram(0);

}

void Drawing::draw_circle(int x, int y, int width, int height)
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
    transApplyMatrix[2][0] = DrawApp::apply_Matrix[2][0];
    transApplyMatrix[2][1] = DrawApp::apply_Matrix[2][1];

    DrawApp::apply_Matrix[2][0] = 0;
    DrawApp::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * (transApplyMatrix * translateMat * DrawApp::apply_Matrix * scaleMat);

    //glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * translateMat * rotateMat * scaleMat;
    //mdl_to_ndc_xform *= DrawApp::apply_Matrix;

    glUseProgram(DrawApp::circle.shdr_pgm);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(DrawApp::circle.vaoid[0]);
    GLint uniform_var_loc1 =
        glGetUniformLocation(DrawApp::circle.shdr_pgm,
            "uModelToNDC");
    if (uniform_var_loc1 >= 0) {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE,
            glm::value_ptr(mdl_to_ndc_xform));
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLint uniformOutlinedColor =
        glGetUniformLocation(DrawApp::box.shdr_pgm,
            "color");
    if (uniformOutlinedColor >= 0) {
        glUniform4f(uniformOutlinedColor, DrawApp::outlineColor.x, DrawApp::outlineColor.y, DrawApp::outlineColor.z, DrawApp::outlineColor.w);
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    glLineWidth(1.5f);
    glDrawElements(GL_LINE_STRIP_ADJACENCY, DrawApp::circle.draw_cnt, GL_UNSIGNED_SHORT, NULL);





    if (DrawApp::isfill == true)
    {
        GLint uniformColor =
            glGetUniformLocation(DrawApp::circle.shdr_pgm,
                "color");
        if (uniformColor >= 0) {
            glUniform4f(uniformColor, DrawApp::color.x, DrawApp::color.y, DrawApp::color.z, DrawApp::color.w);
        }
        else {
            std::cout << "Uniform variable doesn't exist!!!\n";
            std::exit(EXIT_FAILURE);
        }
        glLineWidth(1.0f);
        glDrawElements(DrawApp::circle.primitive_type, DrawApp::circle.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    }
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

void Drawing::draw_image(Image& image, int x, int y, int width, int height)
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
    transApplyMatrix[2][0] = DrawApp::apply_Matrix[2][0];
    transApplyMatrix[2][1] = DrawApp::apply_Matrix[2][1];

    DrawApp::apply_Matrix[2][0] = 0;
    DrawApp::apply_Matrix[2][1] = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * (transApplyMatrix * translateMat * DrawApp::apply_Matrix * scaleMat);


    glUseProgram(DrawApp::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);

    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glBindVertexArray(DrawApp::textureBox.vaoid[DrawApp::current_image_mode]);
    GLint uniform_var_loc1 =
        glGetUniformLocation(DrawApp::textureBox.shdr_pgm,
            "uModelToNDC");

    if (uniform_var_loc1 >= 0) 
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE,
            glm::value_ptr(mdl_to_ndc_xform));
    }
    else 
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }


    GLint uniform_task = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "task");
    if (uniform_task >= 0)
    {
        glUniform1i(uniform_task, DrawApp::task);
    }
    else 
    {
        std::cout << "돌아가 시발";
    }


    GLuint tex_loc = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0)
    {
        glUniform1i(tex_loc, 1);
    }
    else 
    {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    glDrawElements(DrawApp::textureBox.primitive_type, DrawApp::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);

}

void Drawing::draw_image_freely(Image& image, int x, int y, int width, int height)
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
    transApplyMatrix[2][0] = DrawApp::apply_Matrix[2][0];
    transApplyMatrix[2][1] = DrawApp::apply_Matrix[2][1];

    
    DrawApp::apply_Matrix[2][0] = 0;
    DrawApp::apply_Matrix[2][1] = 0;

    glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * (transApplyMatrix * translateMat * DrawApp::apply_Matrix * scaleMat);

    glUseProgram(DrawApp::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);

    
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(DrawApp::textureBox.vaoid[DrawApp::current_image_mode]);
    GLint uniform_var_loc1 = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "uModelToNDC");

    if (uniform_var_loc1 >= 0) 
    {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
    }
    else 
    {
        std::cerr << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLuint tex_loc = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0) 
    {
        glUniform1i(tex_loc, 1);
    }
    else 
    {
        std::cerr << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    glDrawElements(DrawApp::textureBox.primitive_type, DrawApp::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Drawing::push()
{
    DrawApp::privous_view_xform[DrawApp::current_coordinate_mode] = DrawApp::view_xform[DrawApp::current_coordinate_mode];
    DrawApp::previous_color                                       = DrawApp::color;
    DrawApp::previous_Outlinecolor                                = DrawApp::outlineColor;
    DrawApp::previous_Matrix                                      = DrawApp::apply_Matrix;
    DrawApp::previous_image_mode                                  = DrawApp::current_image_mode;
    DrawApp::previous_rectangle_mode                              = DrawApp::current_rectangle_mode;
    DrawApp::previous_coordinate_mode                             = DrawApp::current_coordinate_mode;
    DrawApp::previous_isfill                                      = DrawApp::isfill;
    DrawApp::previous_task                                        = DrawApp::task;

}

void Drawing::pop()
{

    DrawApp::current_coordinate_mode = DrawApp::previous_coordinate_mode;
    DrawApp::view_xform[DrawApp::current_coordinate_mode] = DrawApp::privous_view_xform[DrawApp::current_coordinate_mode];
    DrawApp::color = DrawApp::previous_color;
    DrawApp::outlineColor = DrawApp::previous_Outlinecolor;
    DrawApp::apply_Matrix = DrawApp::previous_Matrix;
    DrawApp::current_image_mode = DrawApp::previous_image_mode;
    DrawApp::current_rectangle_mode = DrawApp::previous_rectangle_mode;
    DrawApp::isfill = DrawApp::previous_isfill;
    DrawApp::world_to_ndc_xform = DrawApp::camwin_to_ndc_xform * DrawApp::view_xform[DrawApp::current_coordinate_mode];
    DrawApp::task = DrawApp::previous_task;
}

void Drawing::translateView(float x, float y)
{
    glm::mat3 translate{ 1.f };
    translate[2][0] = x;
    translate[2][1] = y;
    DrawApp::view_xform[DrawApp::current_coordinate_mode] *= translate;
    DrawApp::world_to_ndc_xform = DrawApp::camwin_to_ndc_xform * DrawApp::view_xform[DrawApp::current_coordinate_mode];
}

void Drawing::set_color(int red, int green, int blue, int alpha)
{
    DrawApp::color = glm::vec4{ red / 255.f, green / 255.f,blue / 255.f, alpha / 255.f };
}

void Drawing::applyMatrix(float a, float b, float c, float d, float e, float f)
{
    DrawApp::apply_Matrix[0][0] = a;
    DrawApp::apply_Matrix[1][0] = b;
    DrawApp::apply_Matrix[2][0] = c;
    DrawApp::apply_Matrix[0][1] = d;
    DrawApp::apply_Matrix[1][1] = e;
    DrawApp::apply_Matrix[2][1] = f;

    DrawApp::apply_Matrix[2][2] = 1;
}

void Drawing::set_rectangle_mode(DrawOriginMode mode)
{
    DrawApp::current_rectangle_mode = static_cast<unsigned int>(mode);
}
void Drawing::set_image_mode(DrawOriginMode mode)
{
    DrawApp::current_image_mode = static_cast<unsigned int>(mode);
}

void Drawing::set_coordinate_mode(CoordinateSystem mode)
{
    DrawApp::current_coordinate_mode = static_cast<unsigned int>(mode);
    DrawApp::world_to_ndc_xform = DrawApp::camwin_to_ndc_xform * DrawApp::view_xform[DrawApp::current_coordinate_mode];
}

void Drawing::draw_image(Drawing::Image& image, int x, int y, int texelX, int texelY, int texelWidth, int texelHeight)
{


    std::vector<glm::vec2> tpos_vtx;
    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX)                       / static_cast<float>(image.GetWidth())), 
                                  static_cast<float>((image.GetHeight() - texelY)) / static_cast<float>(image.GetHeight()) });

    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX + texelWidth) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY)) / static_cast<float>(image.GetHeight()) });
    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY - texelHeight)) / static_cast<float>(image.GetHeight()) });
    tpos_vtx.push_back(glm::vec2{ (static_cast<float>(texelX + texelWidth) / static_cast<float>(image.GetWidth())), static_cast<float>((image.GetHeight() - texelY - texelHeight)) / static_cast<float>(image.GetHeight()) });



    glNamedBufferSubData(DrawApp::textureBox.vboid[DrawApp::current_image_mode], sizeof(glm::vec2) * 4, sizeof(glm::vec2) * tpos_vtx.size(), tpos_vtx.data());


    glm::mat3 scaleMat{ 1.f };

    scaleMat[0][0] = static_cast<float>(texelWidth);
    scaleMat[1][1] = static_cast<float>(texelHeight);
    /*glm::mat3 rotateMat{1.f};
    rotateMat[0][0] = cos(.0f);
    rotateMat[1][0] = -sin(.0f);
    rotateMat[0][1] = sin(.0f);
    rotateMat[1][1] = cos(.0f);*/
    glm::mat3 translateMat{ 1.f };
    translateMat[0][0] = 1.f;
    translateMat[1][1] = 1.f;
    translateMat[2][2] = 1.f;
    translateMat[2][0] = static_cast<float>(x);
    translateMat[2][1] = static_cast<float>(y);

    glm::mat3 transApplyMatrix{ 1.f };
    transApplyMatrix[2][0] = DrawApp::apply_Matrix[2][0];
    transApplyMatrix[2][1] = DrawApp::apply_Matrix[2][1];

    DrawApp::apply_Matrix[2][0] = 0;
    DrawApp::apply_Matrix[2][1] = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat3 mdl_to_ndc_xform = DrawApp::world_to_ndc_xform * (transApplyMatrix * translateMat * DrawApp::apply_Matrix * scaleMat);

    /*std::cout << (scaleMat * DrawApp::apply_Matrix)[0][0] << " " << (scaleMat * DrawApp::apply_Matrix)[0][1] << " " << (scaleMat * DrawApp::apply_Matrix)[0][2] << std::endl;
    std::cout << (scaleMat * DrawApp::apply_Matrix)[1][0] << " " << (scaleMat * DrawApp::apply_Matrix)[1][1] << " " << (scaleMat * DrawApp::apply_Matrix)[1][2] << std::endl;
    std::cout << (scaleMat * DrawApp::apply_Matrix)[2][0] << " " << (scaleMat * DrawApp::apply_Matrix)[2][1] << " " << (scaleMat * DrawApp::apply_Matrix)[2][2] << std::endl;*/
    glUseProgram(DrawApp::textureBox.shdr_pgm);
    glBindTextureUnit(1, image.textureID);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(image.textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glBindVertexArray(DrawApp::textureBox.vaoid[DrawApp::current_image_mode]);
    GLint uniform_var_loc1 =
        glGetUniformLocation(DrawApp::textureBox.shdr_pgm,
            "uModelToNDC");
    if (uniform_var_loc1 >= 0) {
        glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE,
            glm::value_ptr(mdl_to_ndc_xform));
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    GLuint tex_loc = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "uTex2d");
    if (tex_loc >= 0)
    {
        glUniform1i(tex_loc, 1);
    }
    else {
        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }
    GLint uniform_task = glGetUniformLocation(DrawApp::textureBox.shdr_pgm, "task");
    if (uniform_task >= 0)
    {
        glUniform1i(uniform_task, DrawApp::task);
    }
    else {
        std::cout << "없다 시발아";
    }


    glDrawElements(DrawApp::textureBox.primitive_type, DrawApp::textureBox.draw_cnt, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glUseProgram(0);
    std::vector<glm::vec2> tpos_tex;
    tpos_tex.push_back({ 0.f,1.f });
    tpos_tex.push_back({ 1.f,1.f });
    tpos_tex.push_back({ 0.f,0.f });
    tpos_tex.push_back({ 1.f,0.f });
    glNamedBufferSubData(DrawApp::textureBox.vboid[DrawApp::current_image_mode], sizeof(glm::vec2) * 4, sizeof(glm::vec2) * tpos_tex.size(), tpos_tex.data());




}


void Drawing::set_fill(bool set)
{
    Drawing::DrawApp::isfill = set;
}

void Drawing::set_line_color(int red, int green, int blue, int alpha)
{
    DrawApp::outlineColor = glm::vec4{ red / 255.f, green / 255.f,blue / 255.f, alpha / 255.f };
}

void Drawing::EndWIndow()
{
    glDeleteBuffers(1, &DrawApp::box.vaoid[0]);
    glDeleteBuffers(1, &DrawApp::box.vaoid[1]);
    glDeleteBuffers(1, &DrawApp::box.vboid[0]);
    glDeleteBuffers(1, &DrawApp::box.vboid[1]);

    glDeleteBuffers(1, &DrawApp::textureBox.vaoid[0]);
    glDeleteBuffers(1, &DrawApp::textureBox.vaoid[1]);
    glDeleteBuffers(1, &DrawApp::textureBox.vboid[0]);
    glDeleteBuffers(1, &DrawApp::textureBox.vboid[1]);

    glDeleteBuffers(1, &DrawApp::circle.vaoid[0]);
    glDeleteBuffers(1, &DrawApp::circle.vaoid[1]);
    glDeleteBuffers(1, &DrawApp::circle.vboid[0]);
    glDeleteBuffers(1, &DrawApp::circle.vboid[1]);

    //glDeleteBuffers(1, &DrawApp::fontBox.vaoid[0]);
    //glDeleteBuffers(1, &DrawApp::fontBox.vaoid[1]);
    //glDeleteBuffers(1, &DrawApp::fontBox.vboid[0]);
    //glDeleteBuffers(1, &DrawApp::fontBox.vboid[1]);
}