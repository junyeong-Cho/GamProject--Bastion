/*
 * Junyeong Cho
 * GAM200
 * Fall 2023
 * Original Author: Rudy Castan
 */

#include "ImGuiHelper.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

#include <SDL2/SDL_video.h>

namespace ImGuiHelper
{
    void Initialize(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context)
    {
        //���� ���� ImGui ���� Ȯ��
        IMGUI_CHECKVERSION();

        //ImGui ���ؽ�Ʈ �����ؼ� ImGui::CreateContext()�� ����
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        //ImGui�� OpenGL�� �ʱ�ȭ, glsl_version�� OpenGL ���� || imgui_impl_sdl.h ����
        ImGui_ImplSDL2_InitForOpenGL(sdl_window, gl_context);
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }


    //SDL �̺�Ʈ�� ImGui�� ����
    void FeedEvent(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }


    //ImGui ������ ������ �� ����, ���ο� ������ ����
    void Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }


    //ImGui ������ ������ �� ����
    void End(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context)
    {
        //ImGui ��� ������ -> OpenGL ������� ��ȯ
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //����Ʈ ���� ���� Ȯ��
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(sdl_window, gl_context);
        }
    }

    //ImGui ����
    void Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}
