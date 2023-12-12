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
#include "../Engine/GameObjectManager.h"

#include "Player.h"
#include "Mode1.h"
#include "States.h"
#include "Bullet.h"
#include "Monster.h"
#include "BuildMode.h"

#include "../Engine/Mouse.h"


Player::Player(Math::vec2 start_position, int size_x, int size_y) : GameObject(start_position), size_x(size_x), size_y(size_y) 
{
    soundEffect->LoadFile("Assets/Sounds/SoundEffect/gun_sound_meca.wav");

    //AddGOComponent(new GAM200::Sprite("Assets/Player.spt", this));

    SetPosition(start_position);
    SetVelocity({ 0, 0 });
    AddGOComponent(new GAM200::RectCollision({ {static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, {static_cast<int>(GetPosition().x) + size_x, static_cast<int>(GetPosition().y + size_y)} }, this));

    //hurt_timer = new Timer(0.0);
    //AddGOComponent(hurt_timer);
    life_count = max_life;

    current_state = &state_idle;
    current_state->Enter(this);

}


void Player::Update(double dt) {
    if (life_count <= 0)
        return;

    GameObject::Update(dt);

    auto collider = GetGOComponent<GAM200::RectCollision>();

    invincibility_count += dt;
    attack_count += dt;
    
    if (collider != nullptr)
    {
        auto bounds = collider->WorldBoundary();
        Math::vec2 camera_position = Engine::GetGameStateManager().GetGSComponent<GAM200::Camera>()->GetPosition();
        Math::ivec2 window_size = Engine::GetWindow().GetSize();

        if (bounds.Left() < camera_position.x)
        {
            UpdatePosition({ camera_position.x - bounds.Left(), 0 });
            SetVelocity({ 0, GetVelocity().y });
        }

        if (bounds.Right() > camera_position.x + window_size.x)
        {
            UpdatePosition({ camera_position.x + window_size.x - bounds.Right(), 0 });
            SetVelocity({ 0, GetVelocity().y });
        }

        if (bounds.Bottom() < camera_position.y)
        {
            UpdatePosition({ 0, camera_position.y - bounds.Bottom() });
            SetVelocity({ GetVelocity().x, 0 });
        }

        if (bounds.Top() > camera_position.y + window_size.y)
        {
            UpdatePosition({ 0, camera_position.y + window_size.y - bounds.Top() });
            SetVelocity({ GetVelocity().x, 0 });
        }
    }

    Math::vec2 player_position = Math::vec2({ GetPosition().x + size_x / 2, GetPosition().y + size_y / 2 });
    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();

    Math::vec2 real_mouse_position = Math::vec2({ mouse_position.x, mouse_position.y });
    Math::vec2 bullet_direction = Math::vec2({ real_mouse_position.x - player_position.x, real_mouse_position.y - player_position.y });
    bullet_direction /= bullet_direction.GetLength();
    if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT) && 
        attack_count>=attack_cool && 
        Engine::GetGameStateManager().GetGSComponent<BuildMode>()->IsBuilding() == false
        )
    {
        if (shot_gun_mode)
        {
            Math::vec2 offset(static_cast<double>(size_x) * 0.1, static_cast<double>(size_y) * 0.1);

            Math::vec2 left_bullet_direction = Math::vec2({ real_mouse_position.x - player_position.x, real_mouse_position.y - player_position.y });
            Math::vec2 right_bullet_direction = Math::vec2({ real_mouse_position.x - player_position.x, real_mouse_position.y - player_position.y });

            left_bullet_direction.Normalize();
            right_bullet_direction.Normalize();

            left_bullet_direction.Rotate(10.0);
            right_bullet_direction.Rotate(-10.0);


            new Basic_Bullet(player_position, bullet_direction * Bullet::DefaultVelocity);
            new Basic_Bullet(player_position, left_bullet_direction * Bullet::DefaultVelocity);
            new Basic_Bullet(player_position, right_bullet_direction * Bullet::DefaultVelocity);
        }
        else
        {
            new Basic_Bullet(player_position, bullet_direction * Bullet::DefaultVelocity);
        }

        attack_count = 0;
    }
}

void Player::Draw(Math::TransformationMatrix camera_matrix) {
    if (life_count <= 0)
        return;

    p.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
    //GAM200::GameObject::Draw(camera_matrix);
}


bool Player::CanCollideWith(GameObjectTypes type) {
    
    if(static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
       static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster_End)
       )
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Player::ResolveCollision(GameObject* other_object) {
    if (invincibility_count < invincibilityTime)
        return;

    Math::rect player_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
    Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

    double centerX = (player_rect.Left() + player_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
    double centerY = (player_rect.Top() + player_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;


    Monster* monster = static_cast<Monster*>(other_object);

    if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
        static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster_End)
        )
    {
        if (god_mode)
            return;
        life_count -= monster->GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
    }
    else if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Tower) &&
        static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Tower_End)
        )
    {

        other_object->ResolveCollision(this);
    }

}

void Player::update_velocity(double dt) {
    Math::vec2 newVelocity = GetVelocity();

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        newVelocity.x += acceleration * dt;
        if (newVelocity.x > max_velocity)
        {
            newVelocity.x = max_velocity;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
    {
        newVelocity.x -= acceleration * dt;
        if (newVelocity.x < -max_velocity)
        {
            newVelocity.x = -max_velocity;
        }
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
    {
        newVelocity.y += acceleration * dt;
        if (newVelocity.y > max_velocity)
        {
            newVelocity.y = max_velocity;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S))
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
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->state_moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
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
    //else if (player->GetVelocity().x == 0 || player->GetVelocity().y == 0)
    //{
    //    player->change_state(&player->state_idle);
    //} // 이거 없애니까 아무튼 됨,.
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