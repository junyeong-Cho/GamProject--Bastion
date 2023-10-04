#define SDL_MAIN_HANDLED

#include <iostream>

#include "../Engine/Engine.h"

#include "../Game/Splash.h"
#include "../Game/Mode1.h"




int main()
{
    try
    {
        Engine& engine = Engine::Instance();
        engine.Start("GAM200 - Team: Exodia", 1200, 800, OriginPosition::LEFT_DOWN);


        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);

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