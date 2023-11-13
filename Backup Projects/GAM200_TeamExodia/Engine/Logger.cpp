/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#include <string>
#include <iostream>
#include <chrono>
#include <map>

#include "Logger.h"





CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start_time) : min_level(severity), out_stream("Trace.log"), start_time(start_time)
{
	if (use_console == true)
	{
		out_stream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger()
{
	out_stream.flush();
	out_stream.close();
}



void CS230::Logger::log(CS230::Logger::Severity severity, std::string message)
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