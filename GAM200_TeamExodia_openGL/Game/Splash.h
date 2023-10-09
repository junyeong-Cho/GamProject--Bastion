/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splah.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October    4, 2023
Updated:    October    10, 2023
*/

#pragma once

#include "IProgram.h"

#include "../Engine/GameState.h"

#include "../Engine/Texture.h"


class Splash : public GAM200::GameState 
{
public:
    Splash();
    void Load()                                  override;
    void Update(double dt)                       override;
    void Unload()                                override;
    void Draw()                                  override;

    void ImguiDraw()                             override;
    void HandleEvent(SDL_Event& event)           override;



    std::string GetName() override { return "Splash"; }


    struct
    {
        GLuint handle = 0;
        int    width = 0;
        int    height = 0;
        bool   loaded = false;
    } example_image;

public:
    float bruh = 1;

    double counter = 0;

    int x = 0;
    int y = 0;
    int velocity = 600;
    

    GAM200::Texture molu = GAM200::Texture("assets/images/molu.jpeg", GAM200::Texture::TextureType::TRIANGLE);

};
