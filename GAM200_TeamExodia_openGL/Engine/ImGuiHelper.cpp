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
        //실행 중인 ImGui 버전 확인
        IMGUI_CHECKVERSION();

        //ImGui 컨텍스트 생성해서 ImGui::CreateContext()에 저장
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        //ImGui를 OpenGL로 초기화, glsl_version은 OpenGL 버전 || imgui_impl_sdl.h 참고
        ImGui_ImplSDL2_InitForOpenGL(sdl_window, gl_context);
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }


    //SDL 이벤트를 ImGui로 전달
    void FeedEvent(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }


    //ImGui 프레임 렌더링 전 시작, 새로운 프레임 생성
    void Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }


    //ImGui 프레임 렌더링 후 종료
    void End(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context)
    {
        //ImGui 명령 렌더링 -> OpenGL 명령으로 변환
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //뷰포트 지원 여부 확인
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(sdl_window, gl_context);
        }
    }

    //ImGui 종료
    void Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}
