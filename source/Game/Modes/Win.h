#pragma once


#include "Engine/GameState.h"
#include "Engine/Texture.h"

class Win : public GAM200::GameState
{
public:
    Win();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;



    std::string GetName() override { return "Win"; }
public:

    double counter = 0;

    GAM200::Texture win;
};
