/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  main.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 15, 2023
Updated:    March 22, 2023
*/


#include <iostream>

#include "../Engine/Engine.h"

int main() {
    try {
        Engine& engine = Engine::Instance();
        engine.Start("Assignment 12 - junyeong.cho@digipen.edu");

        //vector의 형태로 만들어졌기 때문에, 여러개의 font를 추가할 수 있음
        //또한 이 때문에 font를 추가할 때, 순서가 중요함

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


