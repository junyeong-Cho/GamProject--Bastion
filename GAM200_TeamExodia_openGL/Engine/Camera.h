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
        Camera(Math::rect player_zone);                         //�÷��̾ �����, ī�޶� ������� ���� ����� ������ٰ���
        void SetPosition(Math::vec2 new_position);              //ī�޶��� �⺻��ġ�� ��������
        const Math::vec2& GetPosition() const;
        void SetLimit(Math::irect new_limit);                   //���״�� ī�޶� �����̴� ������ ���ѽ�����
        void Update(const Math::vec2& player_position);
        Math::TransformationMatrix GetMatrix();
    private:
        Math::irect limit;                                      //Setlimit���� ��Ƶ� limit ����
        Math::vec2 position;
        Math::rect player_zone;
    };
}
