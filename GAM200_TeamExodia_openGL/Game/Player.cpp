/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Player.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		10, 2023
*/

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Player.h"
#include "Mode1.h"
#include "States.h"


Player::Player(Math::vec2 start_position, GameObject* starting_tile_ptr = nullptr) : GameObject(start_position), standing_tile(starting_tile_ptr) {
    //AddGOComponent(new GAM200::Sprite("Assets/Cat.spt", (this)));
    AddGOComponent(new GAM200::RectCollision({ {static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, {static_cast<int>(GetPosition().x) + size, static_cast<int>(GetPosition().y + size)} }, this));

    SetVelocity({ 0, 0 });
    SetPosition(start_position);

    //hurt_timer = new Timer(0.0);
    //AddGOComponent(hurt_timer);

    current_state = &state_idle;
    current_state->Enter(this);
}


void Player::Update(double dt) {
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



}

void Player::Draw(Math::TransformationMatrix camera_matrix) {
    /*if (hurt_timer->Remaining() == 0.0 || hurt_timer->TickTock() == true)
    {
        GAM200::GameObject::Draw(camera_matrix);
    }*/
    //GAM200::GameObject::Draw(camera_matrix);

    GAM200::DrawShape shape;
    
    shape.SetColor(0.5f, 0.5f, 1.0f, 1.0f);
    shape.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size, size);
}


bool Player::CanCollideWith(GameObjectTypes type) {
    /*if (type == GameObjectTypes::Particle)
    {
        return false;
    }
    else
    {
        return true;
    }*/
    if (type == GameObjectTypes::Tile) {
        return true;
    }
    else
        return false;
}

void Player::ResolveCollision(GameObject* other_object) {
    Math::rect player_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

    Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

    switch (other_object->Type()) {

    case GameObjectTypes::Monster:

        break;


    case GameObjectTypes::Tile:
        Engine::GetLogger().LogEvent("Tile colliding\n");
        if (player_rect.Right() > other_rect.Left() && player_rect.Left() < other_rect.Right()) {
            // player is approaching top to bottom
            if (player_rect.Bottom() < other_rect.Top() && player_rect.Top() > other_rect.Top()) {

            }
            // player is approaching bottom to top
            else if (player_rect.Top() < other_rect.Bottom() && player_rect.Bottom() < other_rect.Bottom()) {

            }
        }
        if (player_rect.Top() > other_rect.Bottom() && player_rect.Bottom() < other_rect.Top()) {
            // player is approaching left to right
            if (player_rect.Left() < other_rect.Right() && player_rect.Right() > other_rect.Right()) {

            }
            // player is approaching right to left
            else if (player_rect.Right() < other_rect.Left() && player_rect.Left() < other_rect.Left()) {

            }
        }

        if (player_rect.Right() > other_rect.Left() && player_rect.Left() < other_rect.Right() && player_rect.Top() < other_rect.Bottom())
        {
            // If Cat is on top of the crate
            UpdatePosition({ 0, other_rect.Bottom() - player_rect.Top() });

            SetVelocity({ GetVelocity().x, 0 });
        }
        else if (player_rect.Left() < other_rect.Right() && player_rect.Right() > other_rect.Right())
        {
            // If Cat is colliding with crate on the left side
            UpdatePosition({ other_rect.Right() - player_rect.Left(), 0 });

            SetVelocity({ 0, GetVelocity().y });
        }
        else if (player_rect.Right() > other_rect.Left() && player_rect.Left() < other_rect.Left())
        {
            // If Cat is colliding with crate on the right side
            UpdatePosition({ other_rect.Left() - player_rect.Right(), 0 });

            SetVelocity({ 0, GetVelocity().y });
        }
        

        break;


    case GameObjectTypes::Tower:

        break;
    
    default:

        break;
    }
}

void Player::update_velocity(double dt) {
    Math::vec2 newVelocity = GetVelocity();

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right))
    {
        newVelocity.x += acceleration * dt;
        if (newVelocity.x > max_velocity)
        {
            newVelocity.x = max_velocity;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left))
    {
        newVelocity.x -= acceleration * dt;
        if (newVelocity.x < -max_velocity)
        {
            newVelocity.x = -max_velocity;
        }
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up))
    {
        newVelocity.y += acceleration * dt;
        if (newVelocity.y > max_velocity)
        {
            newVelocity.y = max_velocity;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Down))
    {
        newVelocity.y -= acceleration * dt;
        if (newVelocity.y < -max_velocity)
        {
            newVelocity.y = -max_velocity;
        }
    }
    else
    {
        if (newVelocity.x > drag * dt)
        {
            newVelocity.x -= drag * dt;
        }
        else if (newVelocity.x < -drag * dt)
        {
            newVelocity.x += drag * dt;
        }
        else
        {
            newVelocity.x = 0;
        }
        if (newVelocity.y > drag * dt)
        {
            newVelocity.y -= drag * dt;
        }
        else if (newVelocity.y < -drag * dt)
        {
            newVelocity.y += drag * dt;
        }
        else
        {
            newVelocity.y = 0;
        }
    }

    SetVelocity(newVelocity);

}

// State Idle
void Player::State_Idle::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    //player->GetGOComponent<Player::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Player::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }

void Player::State_Idle::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Up)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Down)) {
        player->change_state(&player->state_moving);
    }
}

// State Moving
void Player::State_Moving::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    //player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Moving));
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && player->GetVelocity().x >= 0)
    {
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up) && player->GetVelocity().y >= 0)
        {
            player->SetScale({ 1, 1 });
        }
        else {
            player->SetScale({ 1, -1 });
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && player->GetVelocity().x <= 0)
    {
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up) && player->GetVelocity().y >= 0)
        {
            player->SetScale({ -1, 1 });
        }
        else {
            player->SetScale({ -1, -1 });
        }
    }
}

void Player::State_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_velocity(dt);
}

void Player::State_Moving::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);

    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && player->GetVelocity().x < 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::Down) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::Up) && player->GetVelocity().y < 0)
        )
    {
        player->change_state(&player->state_skidding);
    }
    else if (player->GetVelocity().x == 0)
    {
        player->change_state(&player->state_idle);
    }
}

// State Dashing
void Player::State_Dashing::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);

}

void Player::State_Dashing::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {

}

void Player::State_Dashing::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Up)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Down)) {
        player->change_state(&player->state_moving);
    }
}

// State Skidding
void Player::State_Skidding::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    //player->GetGOComponent<Player::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Player::State_Skidding::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {

    Player* player = static_cast<Player*>(object);

    double newXVelocity{};
    double newYVelocity{};

    if (player->GetVelocity().x > 0)
    {
        newXVelocity = player->GetVelocity().x - (drag + acceleration) * dt;
    }
    else if (player->GetVelocity().x < 0)
    {
        newXVelocity = player->GetVelocity().x + (drag + acceleration) * dt;
    }
    if (player->GetVelocity().y > 0)
    {
        newYVelocity = player->GetVelocity().y - (drag + acceleration) * dt;
    }
    else if (player->GetVelocity().y < 0)
    {
        newYVelocity = player->GetVelocity().y + (drag + acceleration) * dt;
    }

    player->SetVelocity({ newXVelocity, newYVelocity });
}

void Player::State_Skidding::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left) && player->GetVelocity().x < 0)
    {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right) && player->GetVelocity().x > 0)
    {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Down) && player->GetVelocity().y < 0)
    {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up) && player->GetVelocity().y > 0)
    {
        player->change_state(&player->state_moving);
    }
}

