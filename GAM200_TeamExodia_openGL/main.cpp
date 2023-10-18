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
        // 16:9
        //engine.Start("GAM200 - Team: Exodia", 960, 540, OriginPosition::LEFT_DOWN);
        engine.Start("GAM200 - Team: Exodia", 1280, 720, OriginPosition::LEFT_DOWN);


        Splash splash;
        Mode1 mode1;
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