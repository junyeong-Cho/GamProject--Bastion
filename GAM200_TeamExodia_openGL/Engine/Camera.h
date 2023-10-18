/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "ComponentManager.h"

#include "Vec2.h"
#include "Rect.h"
#include "Matrix.h"

namespace GAM200
{
    class Camera : public Component
    {
    public:
        Camera(Math::rect player_zone);                         //플레이어가 벗어나면, 카메라가 따라오게 만들 기능을 만들어줄곳임
        void SetPosition(Math::vec2 new_position);              //카메라의 기본위치르 설정해줌
        const Math::vec2& GetPosition() const;
        void SetLimit(Math::irect new_limit);                   //말그대로 카메라 움직이는 범위를 제한시켜줌
        void Update(const Math::vec2& player_position);
        Math::TransformationMatrix GetMatrix();
    private:
        Math::irect limit;                                      //Setlimit값을 담아둘 limit 변수
        Math::vec2 position;
        Math::rect player_zone;
    };
}
