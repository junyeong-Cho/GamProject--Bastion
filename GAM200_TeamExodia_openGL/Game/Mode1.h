#pragma once

#include "IProgram.h"

#include "../Engine/GameState.h"


class Mode1 : public GAM200::GameState
{
public:
    Mode1();
    void Load()                                  override;
    void Update(double dt)                       override;
    void Unload()                                override;
    void Draw()                                  override;

    void ImguiDraw()                             override;
    void HandleEvent(SDL_Event& event)           override;



    std::string GetName() override { return "Mode1"; }
public:

    double counter = 0;

    int x = 0;
    int y = 0;
    int velocity = 500;

};
