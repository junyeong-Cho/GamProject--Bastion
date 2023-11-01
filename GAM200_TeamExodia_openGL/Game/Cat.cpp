/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"


#include "Cat.h"
#include "Portal.h"
#include "Mode1.h"
#include "States.h"
#include "Particles.h"


Cat::Cat(Math::vec2 start_position, GameObject* starting_floor_ptr = nullptr) : GameObject(start_position), standing_on(starting_floor_ptr)
{
    AddGOComponent(new GAM200::Sprite("Assets/Cat.spt", (this)));
    SetVelocity({ 0, 0 });
    SetPosition(start_position);

    hurt_timer = new Timer(0.0);
    AddGOComponent(hurt_timer);

    current_state = &state_idle;
    current_state->Enter(this);
}


void Cat::update_x_velocity(double dt)
{
    Math::vec2 newVelocity = GetVelocity();

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right))
    {
        newVelocity.x += x_acceleration * dt;
        if (newVelocity.x > max_velocity)
        {
            newVelocity.x = max_velocity;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left))
    {
        newVelocity.x -= x_acceleration * dt;
        if (newVelocity.x < -max_velocity)
        {
            newVelocity.x = -max_velocity;
        }
    }
    else
    {
        if (newVelocity.x > x_drag * dt)
        {
            newVelocity.x -= x_drag * dt;
        }
        else if (newVelocity.x < -x_drag * dt)
        {
            newVelocity.x += x_drag * dt;
        }
        else
        {
            newVelocity.x = 0;
        }
    }

    SetVelocity(newVelocity);
}


void Cat::Update(double dt)
{
    GameObject::Update(dt);


    auto collider = GetGOComponent<GAM200::RectCollision>();

    if (collider != nullptr)
    {
        auto bounds = collider->WorldBoundary();

        if (bounds.Left() < Engine::GetGameStateManager().GetGSComponent<GAM200::Camera>()->GetPosition().x)
        {
            UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<GAM200::Camera>()->GetPosition().x - bounds.Left(), 0 });
            SetVelocity({ 0, GetVelocity().y });
        }

        if (bounds.Right() > Engine::GetGameStateManager().GetGSComponent<GAM200::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
        {
            UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<GAM200::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - bounds.Right(), 0 });
            SetVelocity({ 0, GetVelocity().y });
        }
    }

    //old version of Collision
    /*
    if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2)
    {
        SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
    if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
    {
        SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
    */

}


void Cat::Draw(Math::TransformationMatrix camera_matrix)
{
    if (hurt_timer->Remaining() == 0.0 || hurt_timer->TickTock() == true)
    {
        GAM200::GameObject::Draw(camera_matrix);
    }
}



bool Cat::CanCollideWith(GameObjectTypes type)
{
    if (type == GameObjectTypes::Particle)
    {
        return false;
    }
    else
    {
        return true;
    }

}


void Cat::ResolveCollision(GameObject* other_object)
{
    //Cat* cat = static_cast<Cat*>(other_object);

    // Get the bounding box of the cat
    Math::rect cat_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

    Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();


    switch (other_object->Type())
    {
    case GameObjectTypes::Asteroid:
        if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0)
        {
            SetPosition({ GetPosition().x, other_rect.Top() });
            SetVelocity({ GetVelocity().x, bounce_velocity });
            other_object->ResolveCollision(this);
        }
        else
        {
            if (cat_rect.Left() < other_rect.Left())
            {
                SetVelocity({ -hurt_acceleration, hurt_velocity });
            }
            else
            {
                SetVelocity({ hurt_acceleration, hurt_velocity });
            }
            change_state(&state_falling);
            hurt_timer->Set(hurt_time);
        }
        standing_on = nullptr;
        break;


    case GameObjectTypes::Robot:


        if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0)
        {
            Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
            other_object->ResolveCollision(this);

            SetPosition({ GetPosition().x, other_rect.Top() });
            SetVelocity({ GetVelocity().x, pop_velocity });
        }
        else
        {
            if (cat_rect.Left() < other_rect.Left())
            {
                SetVelocity({ -hurt_acceleration, hurt_velocity });
            }
            else
            {
                SetVelocity({ hurt_acceleration, hurt_velocity });
            }
            change_state(&state_falling);
            hurt_timer->Set(hurt_time);
        }
        standing_on = nullptr;
        break;


        //Old ver of Asteroid Collision
        /*
        other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

        hurt_timer->Set(2.0);

        if (cat_rect.Left() < other_rect.Right() && GetVelocity().x < 0)
        {
            // Colliding with object on the left side
            UpdatePosition({ other_rect.Right() - cat_rect.Left(), 0 });

            // Modify the velocity to bounce back
            SetVelocity({ hurt_acceleration, hurt_velocity });

            change_state(&state_falling);
        }
        else if (cat_rect.Right() > other_rect.Left() && GetVelocity().x > 0)
        {
            // Colliding with object on the right side
            UpdatePosition({ other_rect.Left() - cat_rect.Right(), 0 });

            // Modify the velocity to bounce back
            SetVelocity({ -hurt_acceleration, hurt_velocity });

            change_state(&state_falling);
        }
        break;
        */

    case GameObjectTypes::Floor: [[fallthrough]];
    case GameObjectTypes::Crates:

        if (current_state == &state_falling)
        {
            if (cat_rect.Top() > other_rect.Top())
            {
                SetPosition({ GetPosition().x, other_rect.Top() });
                if (fall_start_position_y > Cat::LargeFallHeight)
                {
                    Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
                }
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
        if (cat_rect.Left() < other_rect.Left()) {
            UpdatePosition(Math::vec2{ (other_rect.Left() - cat_rect.Right()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        else {
            UpdatePosition(Math::vec2{ (other_rect.Right() - cat_rect.Left()), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        break;


        //Old version of Floor and Crates Collision
        /*
        other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

        if (cat_rect.Right() > other_rect.Left() && cat_rect.Left() < other_rect.Right() && cat_rect.Top() < other_rect.Bottom())
        {
            // If Cat is on top of the crate
            UpdatePosition({ 0, other_rect.Bottom() - cat_rect.Top() });

            SetVelocity({ GetVelocity().x, 0 });
        }
        else if (cat_rect.Left() < other_rect.Right() && cat_rect.Right() > other_rect.Right())
        {
            // If Cat is colliding with crate on the left side
            UpdatePosition({ other_rect.Right() - cat_rect.Left(), 0 });

            SetVelocity({ 0, GetVelocity().y });
        }
        else if (cat_rect.Right() > other_rect.Left() && cat_rect.Left() < other_rect.Left())
        {
            // If Cat is colliding with crate on the right side
            UpdatePosition({ other_rect.Left() - cat_rect.Right(), 0 });

            SetVelocity({ 0, GetVelocity().y });
        }
        break;
        */

    case GameObjectTypes::Portal:
        static_cast<Portal*>(other_object)->GoToState();

        break;

    default:


        break;
    }

}


//Old ver of Cat::Draw
/*
void Cat::Draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Draw(camera_matrix * object_matrix);
}
*/

//Old ver of Cat::Update
/*
void Cat::Update(double dt)
{
    current_state->Update(this, dt);
    sprite.Update(dt);
    position += velocity * dt;
    current_state->CheckExit(this);


    if (position.x < camera.GetPosition().x + sprite.GetFrameSize().x / static_cast<double>(2))
    {
        position.x = camera.GetPosition().x + sprite.GetFrameSize().x / static_cast<double>(2);
        velocity.x = 0;
    }
    if (position.x + sprite.GetFrameSize().x / static_cast<double>(2) > camera.GetPosition().x + Engine::GetWindow().GetSize().x)
    {
        position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / static_cast<double>(2);
        velocity.x = 0;
    }

    object_matrix = Math::TranslationMatrix(position);

    if (flipped == true)
    {
        object_matrix *= Math::ScaleMatrix({ -1, 1 });
    }
}
*/


//Sprite state
void Cat::State_Idle::Enter(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);
    cat->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Cat::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }

void Cat::State_Idle::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
}


void Cat::State_Jumping::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    cat->SetVelocity({ cat->GetVelocity().x, Cat::jump_velocity });
    cat->standing_on = nullptr;

}

void Cat::State_Jumping::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({ 0, -(Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt) });
    cat->update_x_velocity(dt);
}

void Cat::State_Jumping::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up) == false)
    {
        cat->SetVelocity({ cat->GetVelocity().x, 0 });
        cat->change_state(&cat->state_falling);
    }
    else if (cat->GetVelocity().y <= 0) {
        cat->change_state(&cat->state_falling);
    }
}


void Cat::State_Falling::Enter(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);
    cat->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));

    cat->fall_start_position_y = cat->GetPosition().y;
}

void Cat::State_Falling::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({ 0, -(Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt) });
    cat->update_x_velocity(dt);
}

void Cat::State_Falling::CheckExit(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);
    if (cat->standing_on != nullptr)
    {
        double fall_height = cat->fall_start_position_y - cat->GetPosition().y;

        if (cat->GetVelocity().x > 0)
        {
            if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left))
            {
                cat->change_state(&cat->state_skidding);
            }
            else
            {
                cat->change_state(&cat->state_running);
            }
        }
        else if (cat->GetVelocity().x < 0)
        {
            if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right))
            {
                cat->change_state(&cat->state_skidding);
            }
            else
            {
                cat->change_state(&cat->state_running);
            }
        }
        else
        {
            if (fall_height > Cat::LargeFallHeight)
            {
                Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
            }
            cat->change_state(&cat->state_idle);
        }

        cat->SetVelocity({ cat->GetVelocity().x, 0 });
    }

    if (cat->GetPosition().y < -500) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}



void Cat::State_Running::Enter(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);
    cat->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && cat->GetVelocity().x >= 0)
    {
        cat->SetScale({ 1, 1 });
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && cat->GetVelocity().x <= 0)
    {
        cat->SetScale({ -1, 1 });
    }
}

void Cat::State_Running::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->update_x_velocity(dt);
}

void Cat::State_Running::CheckExit(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);
    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && cat->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && cat->GetVelocity().x < 0))
    {
        cat->change_state(&cat->state_skidding);
    }
    else if (cat->GetVelocity().x == 0)
    {
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Up))
    {
        cat->change_state(&cat->state_jumping);
    }

    if (cat->standing_on != nullptr && cat->standing_on->IsCollidingWith(cat->GetPosition()) == false) {
        cat->standing_on = nullptr;
        cat->change_state(&cat->state_falling);
    }

}



void Cat::State_Skidding::Enter(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);

    cat->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Skidding));

    /*
    auto particleManager = cat->GetGOComponent<CS230::ParticleManager<Particles::Smoke>>();
    particleManager->Emit(2, cat->GetPosition(), { 0, 0 }, { 2 * cat->GetVelocity().x, 0 }, Math::PI / 6);
    */

    //Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
    //other_object->ResolveCollision(this);

    Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 2 * cat->GetVelocity().x, 0 }, Math::PI / 6);

}

void Cat::State_Skidding::Update(GameObject* object, double dt)
{
    Cat* cat = static_cast<Cat*>(object);

    float newXVelocity{};

    if (cat->GetVelocity().x > 0)
    {
        newXVelocity = cat->GetVelocity().x - (x_drag + x_acceleration) * dt;
    }
    else if (cat->GetVelocity().x < 0)
    {
        newXVelocity = cat->GetVelocity().x + (x_drag + x_acceleration) * dt;
    }

    cat->SetVelocity({ newXVelocity, cat->GetVelocity().y });
}

void Cat::State_Skidding::CheckExit(GameObject* object)
{
    Cat* cat = static_cast<Cat*>(object);

    if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Up))
    {
        cat->change_state(&cat->state_jumping);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && cat->GetVelocity().x < 0)
    {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && cat->GetVelocity().x > 0)
    {
        cat->change_state(&cat->state_running);
    }
}