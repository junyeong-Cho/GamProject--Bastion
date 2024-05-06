
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
*/

#pragma once
#include "Engine/GameState.h"

class Mode1 : public GAM200::GameState 
{
public:
    Mode1();
    void Load() override;
    void Update(double dt)  override;
    void Unload()           override;
	void Draw()             override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;

    std::string GetName() override { return "Mode1"; }
public:
    int counter = 0;
};