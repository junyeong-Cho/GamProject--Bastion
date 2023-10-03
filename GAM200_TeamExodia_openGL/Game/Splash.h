#pragma once


#include "../Engine/GameState.h"


class Splash : public GAM200::GameState
{
public:
    Splash();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;



    std::string GetName() override { return "Splash"; }
public:

    double counter = 0;

    int x = 0;
    int velocity = 100;
    
};
