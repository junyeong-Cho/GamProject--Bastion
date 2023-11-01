/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Animation.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once
#include <vector>
#include "Engine.h"


namespace GAM200
{
    enum class CommandType
    {
        PlayFrame,
        Loop,
        End
    };

    class Command
    {
    public:
        virtual ~Command() {}
        virtual CommandType Type() = 0;
    };


    class End : public Command
    {
    public:
        virtual CommandType Type() override { return CommandType::End; }
    private:
    };


    class Loop : public Command
    {
    public:
        Loop(int loop_index);
        virtual CommandType Type() override { return CommandType::Loop; }
        int LoopIndex();
    private:
        int loop_index;
    };

    class PlayFrame : public Command
    {
    public:
        PlayFrame(int frame, double duration);
        virtual CommandType Type() override { return CommandType::PlayFrame; }
        void Update(double dt);
        bool Ended();
        void ResetTime();
        int  Frame();
    private:
        int frame;
        double target_time;
        double timer;
    };


    class Animation
    {
    public:
        Animation();
        Animation(const std::filesystem::path& animation_file);
        ~Animation();

        void Update(double dt);
        int CurrentFrame();
        void Reset();
        bool Ended();
    private:


        int current_command;
        std::vector<Command*> commands;
        bool ended;
        PlayFrame* current_frame;
    };


}

