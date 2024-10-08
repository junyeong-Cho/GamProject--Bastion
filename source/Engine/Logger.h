/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    December 15, 2023
*/

#pragma once

#include <string>
#include <fstream>
#include <chrono>

namespace GAM200
{
    class Logger
    {
    public:
        enum class Severity
        {
            Verbose,  //Minor messages
            Debug,    //Only used while actively debugging
            Event,    //General event, like key press or state change
            Error     //Errors, such as file load errors
        };

        Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point start_time);
        ~Logger();

        void LogError(std::string text)
        {
            log(Severity::Error, text);
        }

        void LogEvent(std::string text)
        {
            log(Severity::Event, text);
        }

        void LogDebug(std::string text)
        {
            log(Severity::Debug, text);
        }

        void LogVerbose(std::string text)
        {
            log(Severity::Verbose, text);
        }

    private:
        Severity min_level;

#ifdef _WIN32
        std::ofstream out_stream;
#else
        std::ostream* out_stream;   // change: file output / pointer for std::cout 
        std::ofstream file_stream;  // add: file output
#endif

        std::chrono::system_clock::time_point start_time;

        void log(Severity severity, std::string message);

        double second_since_start()
        {
            auto now = std::chrono::system_clock::now();
            std::chrono::duration<double> check_start = now - start_time;

            return check_start.count();
        }
    };
}