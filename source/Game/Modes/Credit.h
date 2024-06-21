#pragma once

#include "Engine/GameState.h"
#include "Engine/Texture.h"

class Credit : public GAM200::GameState
{
public:
    Credit();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;

    std::string GetName() override
    {
        return "Credit";
    }

public:
    GAM200::Texture credit = GAM200::Texture("assets/Background/credit.png");
};