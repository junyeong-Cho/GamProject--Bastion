#define SDL_MAIN_HANDLED

#include <iostream>

#include "../Engine/Engine.h"

#include "Game/Splash.h"
#include "Game/MainMenu.h"
#include "../Modes/Game.h"


int main()
{
    try
    {
        Engine& engine = Engine::Instance();

        // 16:9
        engine.Start("GAM200 - Team: Exodia", 1280, 800, OriginPosition::LEFT_DOWN);

        engine.AddFont("assets/Font_Simple.png");
        engine.AddFont("assets/Font_Outlined.png");

        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Main_menu main_menu;
        engine.GetGameStateManager().AddGameState(main_menu);
        Game game;
        engine.GetGameStateManager().AddGameState(game);

        while (engine.HasGameEnded() == false)
        {
            engine.Update();
        }

        engine.Stop();

        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return -1;
    }

}