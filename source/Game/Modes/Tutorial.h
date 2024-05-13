
#pragma once

#include "Engine/IfWantShader.h"

#include "Game/States.h"

#include "Engine/GameObjectManager.h"
#include "Engine/TextureManager.h"

#include "Engine/Font.h"
#include "Engine/Texture.h"

#include "Engine/GameState.h"
#include "Engine/Sprite.h"


class GameSpeed_Button;
class Skip_Button;
class RangedUnit;

class Tutorial : public GAM200::GameState
{
public:
    Tutorial();

    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override
    {
        return "Tutorial";
    }

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;

    static void NextStep() { if(currentTask != SummonUnit) currentTask = static_cast<CurrentTask>(currentTask + 1); }
    static void PrevStep() { if(currentTask != Done)currentTask = static_cast<CurrentTask>(currentTask - 1); }

#if IfWantShader
    GAM200::Texture tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
    GAM200::Texture win  = GAM200::Texture("assets/win.png");
    GAM200::Texture lose = GAM200::Texture("assets/lose.png");
#else
    GAM200::Texture                  tower_ui = GAM200::Texture("assets/buttons/tower_ui.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture                  win      = GAM200::Texture("assets/win.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture                  lose     = GAM200::Texture("assets/lose.png", GAM200::Texture::TextureType::RECTANGLE);
#endif

private:

#if IfWantShader

#else
    std::unique_ptr<GAM200::Texture> trash;

    std::unique_ptr<GAM200::Texture> currentwave;
    std::unique_ptr<GAM200::Texture> time;
    std::unique_ptr<GAM200::Texture> gold;
    std::unique_ptr<GAM200::Texture> speed;
    std::unique_ptr<GAM200::Texture> monsters;
#endif

    enum InGameStates
    {
        InProgress,
        Win,
        Lose
    } in_game_state = InProgress;

    double count = 0.0;

    enum CurrentTask
    {
        SummonUnit,
        Merge,
        Limit,
        TabAndClick,
        Info,
        Done
    };

    static CurrentTask currentTask;

    bool taskChanged = false;
};