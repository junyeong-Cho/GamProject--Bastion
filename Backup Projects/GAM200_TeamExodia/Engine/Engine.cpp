/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#pragma once
#include "Engine.h"


Engine::Engine() :
#ifdef _DEBUG				
    logger(CS230::Logger::Severity::Debug, true, last_tick)
#else 						
    logger(CS230::Logger::Severity::Event, false, last_tick)
#endif
{ }

Engine::~Engine() {}


void Engine::Start(std::string window_title)
{
    logger.LogEvent("Engine Started");
    window.Start(window_title);

    unsigned int seed = static_cast<unsigned int>(time(NULL));

    srand(seed);

    logger.LogEvent("Random seed: " + std::to_string(seed));

    //Start other services
    last_test = last_tick;
}

void Engine::Stop()
{
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();

    double FPSUpdate = 1 / TargetFPS;


    if (dt >= FPSUpdate)
    {
        logger.LogVerbose("Engine Update");
        last_tick = now;

        // dt -= FPSUpdate;
        frame_count++;

        gamestatemanager.Update(dt);
        input.Update();
        window.Update();

        if (frame_count >= FPSTargetFrames)
        {
            std::chrono::duration<double>now_and_test = now - last_test;

            double actual_time = frame_count / now_and_test.count();
            logger.LogDebug("FPS: " + std::to_string(actual_time));

            frame_count = 0;
            last_test = now;
        }

    }

    //Update other services
}



bool Engine::HasGameEnded()
{
    return gamestatemanager.HasGameEnded();
}


void Engine::AddFont(const std::filesystem::path& file_name)
{
    fonts.push_back(CS230::Font(file_name));
}
