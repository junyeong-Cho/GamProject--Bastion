/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  PrototyeSplash.cpp
Project:    GAM200 Engine
Author:		Hyeonjoon Nam
Created:    November 13, 2023
Updated:    December 15, 2023
*/


#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"

#include "../Game/States.h"
#include "../Game/PrototypeSplash.h"


#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>



namespace
{
    //bool LoadTextureFromFile(const std::filesystem::path& filename, GLuint& out_texture, int& out_width, int& out_height);
}


PrototypeSplash::PrototypeSplash()
{
    
}

void PrototypeSplash::Load()
{
    counter = 0;

  //  example_image.loaded = LoadTextureFromFile("assets/images/DigiPen_Dragon.png", example_image.handle, example_image.width, example_image.height);



}

void PrototypeSplash::Update(double dt)
{
    if (Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::LEFT)) {
        x += (int)(velocity * dt);
    }
    else if (Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::RIGHT)) {
        x -= (int)(velocity * dt);
    }

    if (Engine::GetInput().WheelIsMoved())
    {
        if (Engine::GetInput().MouseWheelDirection() == GAM200::Input::MouseWheel::Up)
        {
			y += (int)(velocity * dt);
		}
        else if (Engine::GetInput().MouseWheelDirection() == GAM200::Input::MouseWheel::Down)
        {
			y -= (int)(velocity * dt);
		}
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        x += (int)(velocity * dt);
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
	{
		x -= (int)(velocity * dt);
	}
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
    {
        y += (int)(velocity * dt);
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::S))
	{
		y -= (int)(velocity * dt);
	}
    

    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::R))
    {
        Engine::GetGameStateManager().ReloadGameState();
    }
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().ClearNextGameState();
    }
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Enter))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
    }

}

void PrototypeSplash::Unload()
{
    x = 0;
    y = 0;
}

void PrototypeSplash::Draw()
{
    //Engine::GetWindow().Clear(UINT_MAX);

   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::GetWindow().Clear(0.392f, 0.584f, 0.929f, 1.0f);

    GAM200::DrawShape shape;

    


    

    shape.DrawRectangle(0, 0, 1280, 720);

    splash.Draw(0, 0, 1280, 720);



}


void PrototypeSplash::ImguiDraw()
{

    ImGui::Begin("Program Info");
    {
	    ImGui::Text("FPS: %f", "55.5");
		ImGui::Text("Frame Time: %f", "55.5");
		ImGui::Text("Counter: %f", counter);


        //In-game-gameplay editor demo version
        float velocity_f = static_cast<float>(velocity); 

        if (ImGui::SliderFloat("Velocity", &velocity_f, 100.0f, 600.0f, "%.0f"))
        {
            velocity = static_cast<int>(velocity_f);
        }
    }
    ImGui::End();

    
    ImGui::Begin("Mouse Location");
    {
        ImGui::Text("Mouse Position X : %d", Engine::Instance().GetInput().GetMousePosition().x);
        ImGui::Text("Mouse Position Y : %d", Engine::Instance().GetInput().GetMousePosition().y);
    }

    ImGui::End();
    

    /*
    if (example_image.loaded)
    {
        ImGui::Begin("OpenGL Texture Test");
        ImGui::Text("handle = %d", example_image.handle);
        ImGui::Text("size = %d x %d", example_image.width, example_image.height);
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(example_image.handle)),
            ImVec2(static_cast<float>(example_image.width), static_cast<float>(example_image.height)));
        ImGui::End();
    }
    */
}

void PrototypeSplash::HandleEvent(SDL_Event& event)
{
if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Engine::GetLogger().LogDebug("Escape key pressed");

		}
	}
}



