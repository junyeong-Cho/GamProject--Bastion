/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Component.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    September 30, 2023
*/

#pragma once


namespace GAM200
{
	class Component
	{
	public:
		virtual ~Component() {};
		virtual void Update(double) {};
	};
}