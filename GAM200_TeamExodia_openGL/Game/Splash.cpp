/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splah.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October    4, 2023
Updated:    October    5, 2023
*/


#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"

#include "../Game/States.h"
#include "../Game/Splash.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>



namespace
{
    bool LoadTextureFromFile(const std::filesystem::path& filename, GLuint& out_texture, int& out_width, int& out_height);
}


Splash::Splash()
{
    
}

void Splash::Load()
{
    counter = 0;

    example_image.loaded = LoadTextureFromFile("assets/images/DigiPen_Dragon.png", example_image.handle, example_image.width, example_image.height);

}

void Splash::Update(double dt)
{
   // Engine::GetLogger().LogDebug(std::to_string(counter));


   // counter += dt;



    
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
    
    
    /*
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Enter))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
    }
    */
}

void Splash::Unload()
{
    x = 0;
    y = 0;
}

void Splash::Draw()
{
    //Engine::GetWindow().Clear(UINT_MAX);

    Engine::GetWindow().Clear(0.392f, 0.584f, 0.929f, 1.0f);

    GAM200::DrawShape shape;

    shape.DrawLine(0, 0, 500, 500);


    shape.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    shape.DrawRectangle(0, 0, 600, 400);



    shape.SetColor(0.0f, 1.0f, 0.0f, 1.0f);

    shape.DrawTriangle(x, y, 500, 400);

}

void Splash::ImguiDraw()
{

    ImGui::Begin("Program Info");
    {
	    ImGui::Text("FPS: %f", Engine::Instance().GetFPS());
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

   


    if (example_image.loaded)
    {
        ImGui::Begin("OpenGL Texture Test");
        ImGui::Text("handle = %d", example_image.handle);
        ImGui::Text("size = %d x %d", example_image.width, example_image.height);
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(example_image.handle)),
            ImVec2(static_cast<float>(example_image.width), static_cast<float>(example_image.height)));
        ImGui::End();
    }
    
}


void Splash::HandleEvent(SDL_Event& event)
{
if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Engine::GetLogger().LogDebug("Escape key pressed");

		}
	}
}


namespace
{
    // https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
    bool LoadTextureFromFile(const std::filesystem::path& filename, GLuint& out_texture, int& out_width, int& out_height)
    {
        // Load from file
        int            image_width = 0;
        int            image_height = 0;
        unsigned char* image_data = stbi_load(filename.string().c_str(), &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glCheck(glGenTextures(1, &image_texture));
        glBindTexture(GL_TEXTURE_2D, image_texture);

        // Setup filtering parameters for display
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // This is required on WebGL for non power-of-two textures
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glCheck(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
#endif
        glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data));
        stbi_image_free(image_data);

        out_texture = image_texture;
        out_width = image_width;
        out_height = image_height;

        return true;
    }
}

