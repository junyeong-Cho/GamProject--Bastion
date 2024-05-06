/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    December 15, 2023
*/

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <map>

/*
namespace GAM200
{
    Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start_time) :
        min_level(severity),
        out_stream("Trace.log"),
        use_console(use_console),
        start_time(start_time)
    {
    }

    Logger::~Logger()
    {
        out_stream.flush();
        out_stream.close();
    }

    void Logger::log(Severity severity, std::string message)
    {
        const std::string severity_levels[] = { "Verbose", "Debug", "Event", "Error" };

        if (min_level > severity)
        {
            return;
        }

        std::ostringstream log_stream;
        log_stream.precision(4);
        log_stream << '[' << std::fixed << second_since_start() << "]\t";
        log_stream << severity_levels[int(severity)] << "\t" << message << std::endl;

        if (use_console)
        {
            std::cout << log_stream.str();
        }

        out_stream << log_stream.str();
    }
}
*/

#ifdef _WIN32
GAM200::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start_time) : min_level(severity), out_stream("Trace.log"), start_time(start_time)
{
	if (use_console == true)
	{
		out_stream.set_rdbuf(std::cout.rdbuf());
	}
}

GAM200::Logger::~Logger()
{
	out_stream.flush();
	out_stream.close();
}


void GAM200::Logger::log(GAM200::Logger::Severity severity, std::string message)
{

	const std::string severity_levels[] = { "Verbose", "Debug", "Event", "Error" };

	if (min_level > severity)
	{
		return;
	}



	out_stream.precision(4);
	out_stream << '[' << std::fixed << second_since_start() << "]\t";


	out_stream << severity_levels[int(severity)] << "\t" << message << std::endl;


	//severity_levels[(int)severity]

	//out_stream << severity_strings[severity] << "\t" << message << std::endl;

	return;
}

#else

GAM200::Logger::Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point start_time)
	: min_level(severity), start_time(start_time), out_stream(nullptr)
{
	if (use_console)
	{
		out_stream = &std::cout;
	}
	else
	{
		file_stream.open("Trace.log");
		out_stream = &file_stream;
	}
}

GAM200::Logger::~Logger()
{
	if (out_stream == &file_stream)
	{
		file_stream.flush();
		file_stream.close();
	}
}



void GAM200::Logger::log(GAM200::Logger::Severity severity, std::string message)
{

	const std::string severity_levels[] = { "Verbose", "Debug", "Event", "Error" };

	if (min_level > severity)
	{
		return;
	}



	out_stream->precision(4);


	*out_stream << '[' << std::fixed << second_since_start() << "]\t";
	*out_stream << severity_levels[int(severity)] << "\t" << message << std::endl;


	//severity_levels[(int)severity]

	//out_stream << severity_strings[severity] << "\t" << message << std::endl;

	return;
}


#endif
