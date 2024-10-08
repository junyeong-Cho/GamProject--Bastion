#pragma once

#include "Engine/Font.h"
#include "Engine/GameState.h"
#include "Engine/Texture.h"
#include "Game/States.h"

class Setting : public GAM200::GameState
{
public:
    Setting();

    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;

    std::string GetName() override
    {
        return "Setting";
    }

private:

    GAM200::Texture* setting_background;
    GAM200::Texture* sound_box;
    GAM200::Texture* sound_bar;
};
