#define SDL_MAIN_HANDLED

#include <iostream>

#include "../Engine/Engine.h"

#include "../Game/PrototypeSplash.h"
#include "../Game/PrototypeMode1.h"


//#include "Engine/Engine.h"
#include "Game/Main_menu.h"
#include "Game/Splash.h"
#include "Game/Mode1.h"
#include "Game/Mode2.h"



/*

int main()
{
    try
    {
        Engine& engine = Engine::Instance();
        // 16:9
        //engine.Start("GAM200 - Team: Exodia", 960, 540, OriginPosition::LEFT_DOWN);
        engine.Start("GAM200 - Team: Exodia", 1280, 720, OriginPosition::LEFT_DOWN);


        PrototypeSplash  splash;
        PrototypeMode1   mode1;
        engine.GetGameStateManager().AddGameState(splash);
        engine.GetGameStateManager().AddGameState(mode1);

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
*/

int main()
{
    try
    {
        Engine& engine = Engine::Instance();
        // 16:9
        //engine.Start("GAM200 - Team: Exodia", 960, 540, OriginPosition::LEFT_DOWN);
        engine.Start("GAM200 - Team: Exodia", 1280, 720, OriginPosition::LEFT_DOWN);

        engine.AddFont("assets/Font_Simple.png");
        engine.AddFont("assets/Font_Outlined.png");

        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Main_menu main_menu;
        engine.GetGameStateManager().AddGameState(main_menu);
        Mode1 mode1;
        engine.GetGameStateManager().AddGameState(mode1);
        Mode2 mode2;
        engine.GetGameStateManager().AddGameState(mode2);


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