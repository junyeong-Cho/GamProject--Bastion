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


<<<<<<< Updated upstream
Player::Player(Math::vec2 start_position, int size_x, int size_y) : GameObject(start_position, 0, { 0.5 , 0.5 }), size_x(size_x), size_y(size_y),
                                       arm("assets/images/arm.spt", (this)), boost("assets/images/boost.spt", (this)), 
                                       dash("assets/images/dash.spt", (this)), 
                                       muzzle_effect("assets/images/muzzle_effect.spt", (this))
{
    soundEffect->LoadFile("Assets/Sounds/SoundEffect/gun_sound_meca.wav");
=======

int Player::additional_attack_dmg = 0;
bool Player::shot_gun_mode = false;
bool Player::god_mode = false;
double Player::attack_cool = 1.0;
bool Player::recover_enabled = false;

Player::Player(Math::vec2 start_position, int size_x, int size_y) : GameObject(start_position, 0, { 0.5 , 0.5 }), size_x(size_x), size_y(size_y),
arm("assets/images/arm.spt", (this)), boost("assets/images/boost.spt", (this)),
dash("assets/images/dash.spt", (this)),
muzzle_effect("assets/images/muzzle_effect.spt", (this))
{
   
>>>>>>> Stashed changes
    AddGOComponent(new GAM200::Sprite("assets/images/Player.spt", (this)));
    double pi = 3.14159265359;
    //AddGOComponent(new GAM200::Sprite("Assets/Player.spt", this));
   // UpdateRotation(180* (pi / 180));
    SetPosition(start_position);
    SetVelocity({ 0, 0 });
    //   AddGOComponent(new GAM200::RectCollision({ {static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, {static_cast<int>(GetPosition().x) + size_x, static_cast<int>(GetPosition().y + size_y)} }, this));

       //hurt_timer = new Timer(0.0);
       //AddGOComponent(hurt_timer);
    life_count = max_life;

    boost.PlayAnimation(static_cast<int>(dash_anm::dash_none));
    boost.PlayAnimation(static_cast<int>(boost_anm::None));
    arm.PlayAnimation(static_cast<int>(arm_anm::None));
    dash.PlayAnimation(static_cast<int>(dash_anm::dash_none));
    muzzle_effect.PlayAnimation(static_cast<int>(arm_anm::None));

    current_state = &state_idle;
    current_state->Enter(this);
}


void Player::Update(double dt) {
    if (life_count <= 0)
        return;

    GameObject::Update(dt);
    GetGOComponent<GAM200::Sprite>()->Update(dt);
<<<<<<< Updated upstream

    arm.Update(dt);
    boost.Update(dt);
    dash.Update(dt);
    muzzle_effect.Update(dt);
=======
>>>>>>> Stashed changes

    arm.Update(dt);
    boost.Update(dt);
    dash.Update(dt);
    muzzle_effect.Update(dt);
    auto collider = GetGOComponent<GAM200::RectCollision>();


<<<<<<< Updated upstream
=======
  //add parts
    if (!dash_active) {
        dash_count += dt;
    }

    if (dash_count > dash_latency) {
        dash_life++;
        dash_count = 0;
    }
    //add parts

>>>>>>> Stashed changes
    invincibility_count += dt;
    attack_count += dt;
    if (!dash_active) {
        dash_count += dt;
    }

    if (dash_count > dash_latency) {
        dash_life++;
        dash_count = 0;
    }


    invincibility_count += dt;
    attack_count += dt;

    
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
        {
           // boost.PlayAnimation(static_cast<int>(boost_anm::left));
            if (is_thrusting == false)
            {
                boost.PlayAnimation(static_cast<int>(boost_anm::left));
                current_state = &Left_Moving;
                is_thrusting = true;
            }
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
        {
             if (is_thrusting == false)
            {
              boost.PlayAnimation(static_cast<int>(boost_anm::right));
              current_state = &Right_Moving;
                is_thrusting = true;
            }
           
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
        {
            if (is_thrusting == false)
            {
                boost.PlayAnimation(static_cast<int>(boost_anm::front));
                current_state = &Front_Moving;
                is_thrusting = true;
            }
            
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S))
        {
            if (is_thrusting == false)
            {
                boost.PlayAnimation(static_cast<int>(boost_anm::back));
                current_state = &Back_Moving;
                is_thrusting = true;
            }

        }
        else
        {
            if (is_thrusting == true)
            {
                boost.PlayAnimation(static_cast<int>(boost_anm::None));
                current_state = &state_idle;
                is_thrusting = false;
            }
        }

       



        if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::W))
        {
            if(dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::front_move_dash));//fucking bug
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::S))
        {
            if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::back_move_dash));
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::A))
        {
            if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::left_move_dash));
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::D))
        {
            if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::right_move_dash));
        }
        else
        {
            dash.PlayAnimation(static_cast<int>(dash_anm::dash_none));
        }
      

    



/*   if(!Engine::GetInput().keyDown(GAM200::Input::Keys::Space) ||
       Engine::GetInput().keyDown(GAM200::Input::Keys::W) ||
       Engine::GetInput().keyDown(GAM200::Input::Keys::A) ||
       Engine::GetInput().keyDown(GAM200::Input::Keys::S) ||
       Engine::GetInput().keyDown(GAM200::Input::Keys::D))
   {
       boost.PlayAnimation(static_cast<int>(dash_anm::dash_none));
   }*/








    //add parts
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        // boost.PlayAnimation(static_cast<int>(boost_anm::left));
        if (is_thrusting == false)
        {
            boost.PlayAnimation(static_cast<int>(boost_anm::left));
            current_state = &Left_Moving;
            is_thrusting = true;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
    {
        if (is_thrusting == false)
        {
            boost.PlayAnimation(static_cast<int>(boost_anm::right));
            current_state = &Right_Moving;
            is_thrusting = true;
        }

    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
    {
        if (is_thrusting == false)
        {
            boost.PlayAnimation(static_cast<int>(boost_anm::front));
            current_state = &Front_Moving;
            is_thrusting = true;
        }

    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S))
    {
        if (is_thrusting == false)
        {
            boost.PlayAnimation(static_cast<int>(boost_anm::back));
            current_state = &Back_Moving;
            is_thrusting = true;
        }

    }
    else
    {
        if (is_thrusting == true)
        {
            boost.PlayAnimation(static_cast<int>(boost_anm::None));
            current_state = &state_idle;
            is_thrusting = false;
        }
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::W))
    {
        if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::front_move_dash));//fucking bug
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::S))
    {
        if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::back_move_dash));
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::A))
    {
        if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::left_move_dash));
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        if (dash_active)
            dash.PlayAnimation(static_cast<int>(dash_anm::right_move_dash));
    }
    else
    {
        dash.PlayAnimation(static_cast<int>(dash_anm::dash_none));
    }
    //add parts




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


if (dash_on[0] == true || dash_on[1] == true || dash_on[2] == true || dash_on[3] == true)
{
    four_way_dash_on = true;
}
else
{
    four_way_dash_on = false;
}
    Math::vec2 player_position = Math::vec2({ GetPosition().x + size_x / 2, GetPosition().y + size_y / 2 });
    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();

    Math::vec2 real_mouse_position = Math::vec2({ mouse_position.x, mouse_position.y });
    Math::vec2 bullet_direction = Math::vec2({ real_mouse_position.x - player_position.x, real_mouse_position.y - player_position.y });
    bullet_direction /= bullet_direction.GetLength();
    
    




    if (dash_on[0] == true || dash_on[1] == true || dash_on[2] == true || dash_on[3] == true)
    {
        four_way_dash_on = true;
    }
    else
    {
        four_way_dash_on = false;
    }

    if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT) &&
        attack_count >= attack_cool &&
        Engine::GetGameStateManager().GetGSComponent<BuildMode>()->IsBuilding() == false
<<<<<<< Updated upstream
        && four_way_dash_on == false && is_fired == false)
    {
        // Some machanism
     //   soundEffect->Play(0);
        is_fired = true;
        
      
        
        
           arm.PlayAnimation(static_cast<int>(arm_anm::arm_fire));
           muzzle_effect.PlayAnimation(static_cast<int>(arm_anm::arm_fire));
           bullet_is_fired = true;
        new Basic_Bullet(player_position, bullet_direction * Bullet::DefaultVelocity);
=======
        && four_way_dash_on == false && is_fired == false
        )
    {
        is_fired = true;
        arm.PlayAnimation(static_cast<int>(arm_anm::arm_fire));
        muzzle_effect.PlayAnimation(static_cast<int>(arm_anm::arm_fire));
        bullet_is_fired = true;

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
            GAM200::SoundEffect::Shotgun().play();

        }
        else
        {
            new Basic_Bullet(player_position, bullet_direction * Bullet::DefaultVelocity);
            GAM200::SoundEffect::Attack().play();
        }
>>>>>>> Stashed changes

        attack_count = 0;
    }
    else
    {
        if (is_fired == true)
        {
            is_fired = false;
<<<<<<< Updated upstream
           // arm.PlayAnimation(static_cast<int>(arm_anm::None));
            muzzle_effect.PlayAnimation(static_cast<int>(arm_anm::None));
        }
    }
    
   
    
   
    std::cout << return_idle_count << std::endl;

 








=======
            // arm.PlayAnimation(static_cast<int>(arm_anm::None));
            muzzle_effect.PlayAnimation(static_cast<int>(arm_anm::None));
        }
    }
>>>>>>> Stashed changes


}


void Player::Draw(Math::TransformationMatrix camera_matrix) {
    if (life_count <= 0)
        return;


    //p.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
<<<<<<< Updated upstream
    GetGOComponent<GAM200::Sprite>()->Draw(GetMatrix()); 
  
    
       
   
        if (dash_on[0] || dash_on[1] || dash_on[2] || dash_on[3])
        {
            
            dash.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
        }
        else
        {
            boost.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
            arm.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
        }

        

        if (bullet_is_fired == true)
        {
            muzzle_effect.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
         }
    
=======
    GetGOComponent<GAM200::Sprite>()->Draw(GetMatrix());




    if (dash_on[0] || dash_on[1] || dash_on[2] || dash_on[3])
    {

        dash.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
    }
    else
    {
        boost.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
        arm.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
    }



    if (bullet_is_fired == true)
    {
        muzzle_effect.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
    }

>>>>>>> Stashed changes
}


bool Player::CanCollideWith(GameObjectTypes type) {

    if (static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
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

void Player::ResolveCollision(GameObject* other_object) {//////////////
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
        life_count -= monster->GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
    }



    switch (other_object->Type()) {

    case GameObjectTypes::Monster:
        life_count -= Monster::GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
        break;

    case GameObjectTypes::Basic_Monster:
        life_count -= Basic_Monster::GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
        break;

    case GameObjectTypes::Fast_Monster:
        life_count -= Fast_Monster::GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
        break;

    case GameObjectTypes::Slow_Monster:
        life_count -= Slow_Monster::GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
        break;

    case GameObjectTypes::Weak_Monster:
        life_count -= Weak_Monster::GetDamage();
        invincibility_count = 0;
        other_object->ResolveCollision(this);
        break;



    case GameObjectTypes::Tile:

        break;

    case GameObjectTypes::Block_Tile:
        /*if (abs(centerX) > abs(centerY)) {
            if (centerX < 0) {
                UpdatePosition(Math::vec2{ (other_rect.Left() - player_rect.Right()), 0.0 });
                SetVelocity({ 0, GetVelocity().y });
            }
            else {
                UpdatePosition(Math::vec2{ (other_rect.Right() - player_rect.Left()), 0.0 });
                SetVelocity({ 0, GetVelocity().y });
            }
        }
        else {
            if (centerY < 0) {
                UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - player_rect.Top()) });
                SetVelocity({ GetVelocity().x, 0 });
            }
            else {
                UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - player_rect.Bottom()) });
                SetVelocity({ GetVelocity().x, 0 });
            }
        }*/

        break;
    case GameObjectTypes::Pass__Tile:

        break;

    case GameObjectTypes::Tower:

        break;

    default:

        break;
    }
}

<<<<<<< Updated upstream

=======
//add parts
>>>>>>> Stashed changes
void Player::update_velocity(double dt) {
    Math::vec2 newVelocity = GetVelocity();

    if (dash_life <= 0) {
        dash_active = false;
<<<<<<< Updated upstream
    }
    //Dash
  /*  if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space))
        && dash_count >= dash_cool) {
       
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
            dash_left = 500;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
            dash_right = 100;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
            dash_front = 100;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
            dash_back = 100;
        }
        dash_count = 0;
    }
    else
    {
         dash_right = 1;
         dash_left = 1;
         dash_front = 1;
         dash_back = 1;
         dash_on = false;
    }*/
        if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::A)))
=======
    }
    //Dash
  /*  if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space))
        && dash_count >= dash_cool) {

        if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
            dash_left = 500;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
            dash_right = 100;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
            dash_front = 100;
        }
        else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
            dash_back = 100;
        }
        dash_count = 0;
    }
    else
    {
         dash_right = 1;
         dash_left = 1;
         dash_front = 1;
         dash_back = 1;
         dash_on = false;
    }*/
    if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::A)))
    {
        //Dash
        if (dash_active)
            dash_on[1] = true;
        Engine::GetLogger().LogDebug("dash_left_on");
    }
    else
    {
        dash_accel = 1;

        dash_on[1] = false;

    }

    if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::D)))
    {
        //Dash
        if (dash_active)
            dash_on[3] = true;
        Engine::GetLogger().LogDebug("dash_right_on");
    }
    else
    {
        dash_accel = 1;

        dash_on[3] = false;

    }

    if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::W)))
    {
        //Dash
        if (dash_active)
            dash_on[0] = true;
        Engine::GetLogger().LogDebug("dash_front_on");
    }
    else
    {
        dash_accel = 1;

        dash_on[0] = false;

    }

    if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::S)))
    {
        //Dash
        if (dash_active)
            dash_on[2] = true;
        Engine::GetLogger().LogDebug("dash_back_on");
    }
    else
    {
        dash_accel = 1;

        dash_on[2] = false;

    }
    //Dash
    if (dash_on[0] || dash_on[1] || dash_on[2] || dash_on[3]) {
        dash_life--;
    }
    if (dash_original_life == dash_life) {
        dash_active = true;
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        newVelocity.x += acceleration * dt;
        newVelocity.x += dash_accel;
        if (newVelocity.x > max_velocity && dash_on[3] == false)
        {
            newVelocity.x = max_velocity;
        }
        else if (dash_on[3] == true)
        {
            dash_accel = 700;
            dash_right = 700;
            newVelocity.x += dash_right;
        }
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
    {
        newVelocity.x -= acceleration * dt;
        newVelocity.x -= dash_accel;
        if (newVelocity.x < -max_velocity && dash_on[1] == false)
        {
            newVelocity.x = -max_velocity;
        }

        else if (dash_on[1] == true)
        {
            dash_accel = 700;
            dash_left = 700;
            newVelocity.x -= dash_left;
        }
    }


    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
    {
        newVelocity.y += acceleration * dt;
        newVelocity.y += dash_accel;
        if (newVelocity.y > max_velocity && dash_on[0] == false)
        {
            newVelocity.y = max_velocity;
        }

        else if (dash_on[0] == true)
        {
            dash_accel = 700;
            dash_front = 700;
            newVelocity.y += dash_front;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S))
    {
        newVelocity.y -= acceleration * dt;
        newVelocity.y -= dash_accel;
        if (newVelocity.y < -max_velocity && dash_on[2] == false)
        {
            newVelocity.y = -max_velocity;
        }

        else if (dash_on[2] == true)
        {
            dash_accel = 700;
            dash_back = 700;
            newVelocity.y -= dash_back;
        }
    }
    else {
        if (newVelocity.x > drag * dt)
>>>>>>> Stashed changes
        {
            //Dash
            if(dash_active)
            dash_on[1] = true;
            Engine::GetLogger().LogDebug("dash_left_on");
        }
        else
        {
            dash_accel = 1;

            dash_on[1] = false;

        }

        if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::D)))
        {
            //Dash
            if (dash_active)
            dash_on[3] = true;
            Engine::GetLogger().LogDebug("dash_right_on");
        }
        else
        {
            dash_accel = 1;

            dash_on[3] = false;

        }

        if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::W)))
        {
            //Dash
            if (dash_active)
            dash_on[0] = true;
            Engine::GetLogger().LogDebug("dash_front_on");
        }
        else
        {
            dash_accel = 1;

            dash_on[0] = false;

        }

        if ((Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space) && Engine::GetInput().keyDown(GAM200::Input::Keys::S)))
        {
            //Dash
            if (dash_active)
            dash_on[2] = true;
            Engine::GetLogger().LogDebug("dash_back_on");
        }
        else
        {
            dash_accel = 1;

            dash_on[2] = false;

        }
        //Dash
    if (dash_on[0] || dash_on[1] || dash_on[2] || dash_on[3]) {
        dash_life--;
    }
    if (dash_original_life == dash_life) {
        dash_active = true;
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
    {
        newVelocity.x += acceleration  * dt;
        newVelocity.x += dash_accel;
        if (newVelocity.x > max_velocity  && dash_on[3] == false)
        {
            newVelocity.x = max_velocity;
        }
        else if (dash_on[3] == true)
        {
            dash_accel = 700;
            dash_right = 700;
            newVelocity.x += dash_right;
        }
    }
    
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A) )
    {
        newVelocity.x -= acceleration  * dt;
        newVelocity.x -= dash_accel;
        if (newVelocity.x < -max_velocity && dash_on[1] == false)
        {
            newVelocity.x = -max_velocity;
        }
        
        else if (dash_on[1] == true)
        {
            dash_accel = 700;
            dash_left = 700;
            newVelocity.x -= dash_left;
        }
    }

<<<<<<< Updated upstream

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W) )
    {
        newVelocity.y += acceleration  * dt;
        newVelocity.y += dash_accel;
        if (newVelocity.y > max_velocity && dash_on[0] == false)
        {
            newVelocity.y = max_velocity;
        }

        else if (dash_on[0] == true)
        {
            dash_accel = 700;
            dash_front = 700;
            newVelocity.y += dash_front;
        }
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S) )
    {
        newVelocity.y -= acceleration  * dt;
        newVelocity.y -= dash_accel;
        if (newVelocity.y < -max_velocity && dash_on[2] == false)
        {
            newVelocity.y = -max_velocity;
        }

        else if (dash_on[2] == true)
        {
            dash_accel = 700;
            dash_back = 700;
            newVelocity.y -= dash_back;
        }
    }
    else {
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

=======
>>>>>>> Stashed changes
    SetVelocity(newVelocity);
}












// State Idle
void Player::State_Idle::Enter(GameObject* object)
{
<<<<<<< Updated upstream
    
=======

>>>>>>> Stashed changes
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Player::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }

void Player::State_Idle::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->Front_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->Right_Moving);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
        player->change_state(&player->Back_Moving);
    }
    else
    {
        player->change_state(&player->state_idle);

    }
}

// State front Moving
void Player::Front_Moving::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Front_Moving));
<<<<<<< Updated upstream
    
  
=======


>>>>>>> Stashed changes
}

void Player::Front_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_velocity(dt);
}

void Player::Front_Moving::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x < 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y < 0)
        )
    {
        player->change_state(&player->state_skidding);
    }
<<<<<<< Updated upstream
  
=======

>>>>>>> Stashed changes



    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->Front_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->Right_Moving);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
        player->change_state(&player->Back_Moving);
    }




}



//////////////////////



// State rihgt Moving
void Player::Right_Moving::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Rihgt_Moving));
<<<<<<< Updated upstream
    
=======

>>>>>>> Stashed changes
}

void Player::Right_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_velocity(dt);
}

void Player::Right_Moving::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x < 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y < 0)
        )
    {
        player->change_state(&player->state_skidding);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->Front_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->Right_Moving);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
        player->change_state(&player->Back_Moving);
    }
<<<<<<< Updated upstream
  
=======

>>>>>>> Stashed changes
}



//////////////////////



// State back Moving
void Player::Back_Moving::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Back_Moving));
<<<<<<< Updated upstream
    
=======

>>>>>>> Stashed changes
}

void Player::Back_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_velocity(dt);
}

void Player::Back_Moving::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x < 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y < 0)
        )
    {
        player->change_state(&player->state_skidding);
    }



    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->Front_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->Right_Moving);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
        player->change_state(&player->Back_Moving);
    }
}



//////////////////////



// State left Moving
void Player::Left_Moving::Enter(GameObject* object)
{
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Left_Moving));
<<<<<<< Updated upstream
  
=======

>>>>>>> Stashed changes
}

void Player::Left_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_velocity(dt);
}

void Player::Left_Moving::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if ((Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x < 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y < 0)
        )
    {
        player->change_state(&player->state_skidding);
    }



    if (Engine::GetInput().keyDown(GAM200::Input::Keys::W)) {
        player->change_state(&player->Front_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D)) {
        player->change_state(&player->Right_Moving);
    }

    if (Engine::GetInput().keyDown(GAM200::Input::Keys::A)) {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S)) {
        player->change_state(&player->Back_Moving);
    }
<<<<<<< Updated upstream
    
=======

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
   
=======

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
   /* if (Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x < 0)
    {
        player->change_state(&player->Left_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x > 0)
    {
        player->change_state(&player->Right_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y < 0)
    {
        player->change_state(&player->Back_Moving);
    }
    else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y > 0)
    {
        player->change_state(&player->Front_Moving);
    }*/
}
=======
    /* if (Engine::GetInput().keyDown(GAM200::Input::Keys::A) && player->GetVelocity().x < 0)
     {
         player->change_state(&player->Left_Moving);
     }
     else if (Engine::GetInput().keyDown(GAM200::Input::Keys::D) && player->GetVelocity().x > 0)
     {
         player->change_state(&player->Right_Moving);
     }
     else if (Engine::GetInput().keyDown(GAM200::Input::Keys::S) && player->GetVelocity().y < 0)
     {
         player->change_state(&player->Back_Moving);
     }
     else if (Engine::GetInput().keyDown(GAM200::Input::Keys::W) && player->GetVelocity().y > 0)
     {
         player->change_state(&player->Front_Moving);
     }*/
}

//add parts
>>>>>>> Stashed changes
