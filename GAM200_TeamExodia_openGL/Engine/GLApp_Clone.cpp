/*
#include "GameState.h"
#include "../Engine/GLApp_Clone.h"
#include "../Engine/ImGuiHelper.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>


namespace
{
    //attr�� �ش��ϴ� �÷��׸� value�� �����ϴ� �Լ�
    void hint_gl(SDL_GLattr attr, int value)
    {
        // https://wiki.libsdl.org/SDL_GL_SetAttribute
        if (const auto success = SDL_GL_SetAttribute(attr, value); success != 0)
        {
            std::cerr << "Failed to Set GL Attribute: " << SDL_GetError() << '\n';
        }
    }

    template <typename... Message> [[noreturn]] void throw_error_message(Message&&... more_messages)
    {
        std::ostringstream stringOut;
        (stringOut << ... << more_messages);

        throw std::runtime_error{stringOut.str()};
    }
}

Engine::Engine(const char* title, int desired_width, int desired_height) 
{
    if (title == nullptr || title[0] == '\0')
    {
        throw_error_message("App title shouldn't be empty");
    }


    //SDL_INIT_VIDEO�� �÷��׸� ����� ���� ���� ��� �ʱ�ȭ
    //�����ϸ� �����޼��� ���
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw_error_message("Failed to init SDK error: ", SDL_GetError());
    }


    //�Ʒ� �÷��׵��� SDL_video.h ���Ͽ� ���ǵǾ� ����
    //�� �ҷ��ö��� <SDL2/SDL.h>�Ἥ �ҷ���
    hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    hint_gl(SDL_GL_DOUBLEBUFFER, true);
    hint_gl(SDL_GL_STENCIL_SIZE, 8);
    hint_gl(SDL_GL_DEPTH_SIZE, 24);
    hint_gl(SDL_GL_RED_SIZE, 8);
    hint_gl(SDL_GL_GREEN_SIZE, 8);
    hint_gl(SDL_GL_BLUE_SIZE, 8);
    hint_gl(SDL_GL_ALPHA_SIZE, 8);
    hint_gl(SDL_GL_MULTISAMPLEBUFFERS, 1);
    hint_gl(SDL_GL_MULTISAMPLESAMPLES, 4);

    
    //desired_width�� desired_height�� �ִ� �ּҰ����� ����
    //SDL_CreateWindow������ desired_width�� desired_height�� ����� â�� ũ�⸦ ����
    desired_width  = std::max(640, std::min(16384, desired_width));
    desired_height = std::max(480, std::min(16384, desired_height));

    //���� ������ �Ӽ�
    //ó�� ���� ��ġ: ����
    //OpenGL context ���� | ������ ũ�� ���� ���� | ��DPI��� ���
    ptr_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desired_width, desired_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (ptr_window == nullptr)
    {
        throw_error_message("Failed to create window: ", SDL_GetError());
    }

    //������ ���� window �Ӽ��� ���� gl_context�� �����.
    //���� nullptr�̸� ������ ��ȯ�Ѵ�.
    if (gl_context = SDL_GL_CreateContext(ptr_window); gl_context == nullptr)
    {
        throw_error_message("Faild to create opengl context: ", SDL_GetError());
    }

    SDL_GL_MakeCurrent(ptr_window, gl_context);

    if (const auto result = glewInit(); GLEW_OK != result)
    {
        throw_error_message("Unable to initialize GLEW - error: ", glewGetErrorString(result));
    }

    //Vsync�� Ȱ��ȭ �ϴ� �ڵ��̴�.
    //ó���� ADAPTIVE_VSYNC�� ���� �����غ���, �����ϸ� �Ϲ� VSYNC�� �����ϰ� �ȴ�.
    constexpr int ADAPTIVE_VSYNC = -1;
    constexpr int VSYNC          =  1;
    if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
    {
        SDL_GL_SetSwapInterval(VSYNC);
    }

    ImGuiHelper::Initialize(ptr_window, gl_context);

    int width = 0, height = 0;
    SDL_GL_GetDrawableSize(ptr_window, &width, & height);
    ptr_gamestate = create_program(width, height);

}

Engine::~Engine()
{
    delete ptr_gamestate;
    ImGuiHelper::Shutdown();
    SDL_GL_DeleteContext(gl_context);
    SDL_Quit();
}

void Engine::Update()
{
    SDL_Event event{ 0 };
    while (SDL_PollEvent(&event) != 0)
    {
        ImGuiHelper::FeedEvent(event);
        ptr_gamestate->HandleEvent(*ptr_window, event);
        if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) [[unlikely]]
        {
            is_done = true;
        }
    }
    ptr_gamestate->Update();
    ptr_gamestate->Draw();

    ImGuiHelper::Begin();
    ptr_gamestate->ImGuiDraw();
    ImGuiHelper::End(ptr_window, gl_context);

    SDL_GL_SwapWindow(ptr_window);
}

bool Engine::IsDone() const noexcept
{
    return is_done;
}
*/