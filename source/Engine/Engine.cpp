/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    December 15, 2023
*/



#include "Engine.h"
#include "Engine/Drawing.h"

#include <GL/glew.h>
#include <iostream>


Engine::Engine() :
#ifdef _DEBUG				
    logger(GAM200::Logger::Severity::Debug, true, last_tick)
#else 						
    logger(GAM200::Logger::Severity::Event, false, last_tick)
#endif
{ }

Engine::~Engine() {}


void Engine::Start(const char* window_title, int desired_width, int desired_height, OriginPosition position)
{
    logger.LogEvent("Engine Started");
    window.Start(window_title, desired_width, desired_height, position);

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

    dt *= speed;

    if (dt >= FPSUpdate)
    {
        logger.LogVerbose("Engine Update");
        last_tick = now;

        // dt -= FPSUpdate;
        frame_count++;

        gamestatemanager.Update(dt);
        //mouse.Update();
        input.Update();

        ShaderDrawing::ShaderDraw::updateShaders();


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
    fonts.push_back(GAM200::Font(file_name));
}


void Engine::push()
{
#if     !defined(__EMSCRIPTEN__)
    glPushAttrib(GL_CURRENT_BIT);
    glPushAttrib(GL_ENABLE_BIT);
    glPushAttrib(GL_TEXTURE_BIT);
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    glPushAttrib(GL_TRANSFORM_BIT);
    glPushAttrib(GL_VIEWPORT_BIT);
    glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_LIGHTING_BIT);
    glPushAttrib(GL_LINE_BIT);
    glPushAttrib(GL_POLYGON_BIT);
    glPushAttrib(GL_STENCIL_BUFFER_BIT);
    glPushAttrib(GL_TEXTURE_BIT);
    glPushAttrib(GL_FOG_BIT);
    glPushAttrib(GL_ACCUM_BUFFER_BIT);
    glPushAttrib(GL_LIST_BIT);
    glPushAttrib(GL_EVAL_BIT);
    glPushAttrib(GL_PIXEL_MODE_BIT);
    glPushAttrib(GL_HINT_BIT);
    glPushAttrib(GL_TEXTURE_BIT);
#endif
}

void Engine::pop()
{
    glPopAttrib();
}


