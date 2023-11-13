/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ScreenWrap.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/


#pragma once


#include "../Engine/GameObject.h"
#include "../Engine/Component.h"

//Engine�� �Ϻΰ� �ƴ�, �� object�� ������ҵ��̱� ������, CS230 namespace�� ���� �ʾҴ�!
class ScreenWrap : public CS230::Component 
{
public:
    ScreenWrap(CS230::GameObject& object) : object(object) {}
    void Update(double dt) override;

private:
    CS230::GameObject& object;
};
