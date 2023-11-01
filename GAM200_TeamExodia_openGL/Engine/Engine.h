/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    September 30, 2023
*/

#pragma once

#include "../Engine/Window.h"
#include "../Engine/Logger.h"
#include "../Engine/Input.h"
//#include "../Engine/Font.h"
#include "../Engine/Mouse.h"


#include "../Engine/GameStateManager.h"
#include "../Engine/TextureManager.h"


#include <chrono>



class Engine
{
public:
    static Engine& Instance()
    {
        static Engine instance;
        return instance;
    }
    static GAM200::Logger& GetLogger()
    {
        return Instance().logger;
    }


    static GAM200::Window& GetWindow()
    {
        return Instance().window;
    }

    static GAM200::GameStateManager& GetGameStateManager()
    {
        return Instance().gamestatemanager;
    }

    static GAM200::Input& GetInput()
	{
        return Instance().input;
	}

    static GAM200::TextureManager& GetTextureManager()
    {
		return Instance().texturemanager;
	}
    

    static GAM200::Mouse& GetMouse()
    {
		return Instance().mouse;
	}


    void Start(const char* window_title, int desired_width, int desired_height, OriginPosition position);
    void Stop();
    void Update();
    bool HasGameEnded();

    void push();
    void pop();


private:

   // std::vector<GAM200::Font> fonts;


    std::chrono::system_clock::time_point last_tick = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point last_test;

    int frame_count = 0;

    static constexpr double TargetFPS = 144.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);

    Engine();
    ~Engine();

    GAM200::Logger logger;
    GAM200::Window window;
    GAM200::GameStateManager gamestatemanager;
    GAM200::TextureManager   texturemanager;
    GAM200::Input input;
    GAM200::Mouse mouse;




};
