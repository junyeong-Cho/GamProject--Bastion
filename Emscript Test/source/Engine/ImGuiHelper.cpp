/*
 * Junyeong Cho
 * GAM200
 * Fall 2023
 * Original Author: Rudy Castan
 */

#include "ImGuiHelper.h"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <imgui.h>

#include <SDL_video.h>

namespace ImGuiHelper
{
    void Initialize(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context)
    {
        // Check the version of ImGui running
        IMGUI_CHECKVERSION();

        // Create ImGui context and save it with ImGui::CreateContext()
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        // Initialize ImGui for OpenGL, glsl_version is the OpenGL version || see imgui_impl_sdl.h for reference
        ImGui_ImplSDL2_InitForOpenGL(sdl_window, gl_context);
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }


    // Pass SDL events to ImGui
    void FeedEvent(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }


    // Begin rendering ImGui frame before the new frame is created
    void Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }


    // Finish rendering ImGui frame
    void End(util::not_null<SDL_Window*> sdl_window, util::not_null<SDL_GLContext> gl_context)
    {
        // Render ImGui commands -> convert to OpenGL commands
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Check if viewport support is enabled
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(sdl_window, gl_context);
        }

    }

    // Shutdown ImGui
    void Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}
