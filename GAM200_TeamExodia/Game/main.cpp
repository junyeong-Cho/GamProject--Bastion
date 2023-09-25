/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  main.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 15, 2023
Updated:    September 26, 2023
*/


#include <iostream>

#include "../Engine/Engine.h"

#include "../Game/Main_menu.h"
#include "../Game/Splash.h"
#include "../Game/Mode1.h"
#include "../Game/Mode2.h"


int main() 
{
    try 
    {
        Engine& engine = Engine::Instance();
        engine.Start("GAM200 - Team: Exodia");

        //vector의 형태로 만들어졌기 때문에, 여러개의 font를 추가할 수 있음
        //또한 이 때문에 font를 추가할 때, 순서가 중요함

        engine.AddFont("Assets/Font_Simple.png");
        engine.AddFont("Assets/Font_Outlined.png");

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


