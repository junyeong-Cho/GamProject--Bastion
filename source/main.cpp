#define SDL_MAIN_HANDLED

#include <iostream>

#include "Engine/Engine.h"
#include "Engine/Drawing.h"

#include "Game/Splash.h"
#include "Game/Modes/MainMenu.h"
#include "Game/Modes/Game.h"
#include "Game/Modes/Setting.h"
#include "Game/Modes/HowToPlay.h"
#include "Game/Modes/Store.h"
#include "Game/Modes/Win.h"
#include "Game/Modes/Lose.h"
#include "Game/Modes/Game.h"
#include "Game/Modes/Tutorial.h"


#if defined(__EMSCRIPTEN__)
#    include <emscripten.h>
#    include <emscripten/bind.h>

namespace
{
    GAM200::Window* gApplicationWindow = nullptr;
    bool gNeedResize = false;
}

void main_loop()
{
    if (gNeedResize)
    {
        int newWidth, newHeight;
        SDL_GetWindowSize(gApplicationWindow->GetSDLWindow(), &newWidth, &newHeight);
        gApplicationWindow->ForceResize(newWidth, newHeight);
        gNeedResize = false;
    }

    gApplicationWindow->Update();
    if (gApplicationWindow->IsDone())
        emscripten_cancel_main_loop();
}

EMSCRIPTEN_BINDINGS(main_window)
{
    emscripten::function("setWindowSize", emscripten::optional_override([](int sizeX, int sizeY)
    {
        sizeX = std::max(400, sizeX);
        sizeY = std::max(400, sizeY);
        Math::ivec2 size = gApplicationWindow->GetSize();
        if (sizeX != size.x || sizeY != size.y)
        {
            gNeedResize = true;
            SDL_SetWindowSize(gApplicationWindow->GetSDLWindow(), sizeX, sizeY);
        }
    }));
}
#endif

int main()
{
    try
    {
        Engine& engine = Engine::Instance();

        // 16:9
        engine.Start("GAM200 - Team: Exodia", 1280, 800, OriginPosition::LEFT_DOWN);

        engine.AddFont("assets/Font_Simple.png");
        engine.AddFont("assets/Font_Outlined.png");

        engine.GetAudioManager().SetMusicVolume(30.f);

        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Main_menu main_menu;
        engine.GetGameStateManager().AddGameState(main_menu);
        Game game;
        engine.GetGameStateManager().AddGameState(game);
        HowToPlay how_to_play;
        engine.GetGameStateManager().AddGameState(how_to_play);
        Store store;
        engine.GetGameStateManager().AddGameState(store);
        Tutorial tutorial;
        engine.GetGameStateManager().AddGameState(tutorial);
        Win win;
        engine.GetGameStateManager().AddGameState(win);
        Lose lose;
        engine.GetGameStateManager().AddGameState(lose);
        Setting setting;
        engine.GetGameStateManager().AddGameState(setting);

#if     !defined(__EMSCRIPTEN__)
        while (engine.HasGameEnded() == false)
        {
            engine.Update();
        }
        engine.Stop();
        ShaderDrawing::EndWIndow();
#else
        // https://kripken.github.io/emscripten-site/docs/api_reference/emscripten.h.html#c.emscripten_set_main_loop_arg
        gApplicationWindow = &(engine.GetWindow());
        int simulate_infinite_loop = 1;
        int match_browser_framerate = -1;
        emscripten_set_main_loop(main_loop, match_browser_framerate, simulate_infinite_loop);
#endif

        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return -1;
    }

}