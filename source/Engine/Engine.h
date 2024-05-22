/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    MAy 1, 2024
*/

#pragma once
#include "Window.h"
#include "Logger.h"
#include "Input.h"
#include "Font.h"
#include "Mouse.h"
#include "Audio.h"


#include "GameStateManager.h"
#include "TextureManager.h"

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


    static GAM200::Font& GetFont(int index)
    {
        return Instance().fonts[index];
    }


    static GAM200::AudioManager& GetAudioManager()
    {
        return Instance().audiomanager;
    }

    //   static GAM200::Mouse& GetMouse()
    //   {
       //	return Instance().mouse;
       //}


    void Start(const char* window_title, int desired_width, int desired_height, OriginPosition position);
    void Stop();
    void Update();
    bool HasGameEnded();

    void push();
    void pop();

    void AddFont(const std::filesystem::path& file_name);
    void SetSpeed(double value) { speed = value; }

    static constexpr bool IsShaderEnabled()
    {
		return EnableShader;
	}

private:
    double speed = 1.0;
    std::vector<GAM200::Font> fonts;

    std::chrono::system_clock::time_point last_tick = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point last_test;

    int frame_count = 0;

    static constexpr double TargetFPS = 144.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);

    static constexpr bool EnableShader = true;

    Engine();
    ~Engine();

    GAM200::Logger logger;
    GAM200::Window window;
    GAM200::GameStateManager gamestatemanager;
    GAM200::TextureManager   texturemanager;
    GAM200::Input input;
    GAM200::AudioManager     audiomanager;

    //GAM200::Mouse mouse;




};