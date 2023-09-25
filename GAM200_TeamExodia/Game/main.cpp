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

        //vector�� ���·� ��������� ������, �������� font�� �߰��� �� ����
        //���� �� ������ font�� �߰��� ��, ������ �߿���

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


