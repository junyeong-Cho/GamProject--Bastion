/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robots.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/


#include "Robots.h"

#include "../Engine/GameStateManager.h"

#include "../Engine/Collision.h"
#include "../Engine/Engine.h"


//Old Constructure for the robot
/*
Robot::Robot(Math::vec2 position) : CS230::GameObject(position)
{
    AddGOComponent(new CS230::Sprite("Assets/Robot.spt", (this)));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    //AddGOComponent(new Score());
}
*/

Robot::Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary) : GAM200::GameObject(position), m_cat(cat), m_left_boundary(left_boundary), m_right_boundary(right_boundary)
{
    AddGOComponent(new GAM200::Sprite("Assets/Robot.spt", (this)));
    GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));

    current_state = &state_walking;
    current_state->Enter(this);
}


void Robot::ResolveCollision(GameObject* other_object)
{
    //Math::rect robot_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();

    if (other_object->Type() == GameObjectTypes::Cat)
    {
        RemoveGOComponent<GAM200::RectCollision>();

        Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
        scoreComponent->Add(1);

        change_state(&state_dead);
    }
}


void Robot::State_Dead::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    robot->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));

}

void Robot::State_Dead::Update(GameObject* object, double dt)
{

}

void Robot::State_Dead::CheckExit(GameObject* object)
{

}


void Robot::State_Walking::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    robot->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
    robot->m_walking_direction = WalkingDirection::Right;
}

void Robot::State_Walking::Update(GameObject* object, double dt)
{
    Robot* robot = static_cast<Robot*>(object);
    Math::vec2 position = robot->GetPosition();
    Math::vec2 scale = robot->GetScale();

    float imageOffset = 11.0;

    if (robot->m_walking_direction == WalkingDirection::Right)
    {
        position.x += robot->walking_speed * dt;

        if (position.x > robot->m_right_boundary)
        {
            position.x = robot->m_right_boundary;
            robot->m_walking_direction = WalkingDirection::Left; // Start moving left
            scale.x = -fabs(scale.x);
        }
    }
    else // Left
    {
        position.x -= robot->walking_speed * dt;

        if (position.x < robot->m_left_boundary)
        {
            position.x = robot->m_left_boundary;
            robot->m_walking_direction = WalkingDirection::Right;
            scale.x = fabs(scale.x);
        }
    }

    robot->SetScale(scale);
    robot->SetPosition(position);

}

void Robot::State_Walking::CheckExit(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    Math::vec2 cat_position = robot->m_cat->GetPosition();

    if (cat_position.x >= robot->m_left_boundary && cat_position.x <= robot->m_right_boundary)
    {
        if ((robot->m_walking_direction == WalkingDirection::Right && cat_position.x > robot->GetPosition().x) ||
            (robot->m_walking_direction == WalkingDirection::Left && cat_position.x < robot->GetPosition().x))
        {
            robot->change_state(&robot->state_angry);
        }
    }
}


void Robot::State_Angry::Enter(GameObject* object)
{
    Robot* robot = static_cast<Robot*>(object);
    robot->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Angry));
}

void Robot::State_Angry::Update(GameObject* object, double dt)
{
    Robot* robot = static_cast<Robot*>(object);

    Math::vec2 position = robot->GetPosition();
    Math::vec2 scale = robot->GetScale();


    if (robot->m_walking_direction == WalkingDirection::Right)
    {
        position.x += robot->angry_speed * dt;

        if (position.x > robot->m_right_boundary)
        {
            position.x = robot->m_right_boundary;
            robot->m_walking_direction = WalkingDirection::Left; // Start moving left
            scale.x = -fabs(scale.x);
        }
    }
    else // Left
    {
        position.x -= robot->angry_speed * dt;

        if (position.x < robot->m_left_boundary)
        {
            position.x = robot->m_left_boundary;
            robot->m_walking_direction = WalkingDirection::Right;
            scale.x = fabs(scale.x);
        }
    }

    robot->SetScale(scale);
    robot->SetPosition(position);
}

void Robot::State_Angry::CheckExit(GameObject* object)
{

}
