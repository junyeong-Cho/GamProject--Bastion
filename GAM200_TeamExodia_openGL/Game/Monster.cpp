

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Monster.h"
#include "States.h"


Monster::Monster(Math::vec2 position, Player* player) : GameObject(position), m_player(player) {
    SetPosition(position);
    SetVelocity({ 0, 0 });
    //AddGOComponent(new GAM200::RectCollision({ {static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, {static_cast<int>(GetPosition().x) + size, static_cast<int>(GetPosition().y + size)} }, this));
    AddGOComponent(new GAM200::RectCollision({  }, this));

    current_state = &state_walking;
    current_state->Enter(this);

    next_tile_position = path[current_tile_position];
}

void Monster::ResolveCollision(GameObject* other_object) {

    if (other_object->Type() == GameObjectTypes::Player)
    {
        RemoveGOComponent<GAM200::RectCollision>();

        change_state(&state_dead);
    }
}

void Monster::State_Dead::Enter(GameObject* object)
{
    Monster* monster = static_cast<Monster*>(object);
    //monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));

}

void Monster::State_Dead::Update(GameObject* object, double dt)
{

}

void Monster::State_Dead::CheckExit(GameObject* object)
{

}


void Monster::State_Walking::Enter(GameObject* object)
{
    Monster* monster = static_cast<Monster*>(object);
    //monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
    monster->m_walking_direction = WalkingDirection::Right;
}

void Monster::State_Walking::Update(GameObject* object, double dt)
{
    Monster* monster = static_cast<Monster*>(object);
    Math::vec2 position = monster->GetPosition();
    static int tile_size = Engine::GetWindow().GetSize().x / 16;
    monster->current_tile_position = Math::ivec2(static_cast<int>(position.x / tile_size), static_cast<int>(position.y / tile_size));
    
    if (monster->m_walking_direction == WalkingDirection::Right)
    {
        position.x += monster->walking_speed * dt; 
    }
    else if (monster->m_walking_direction == WalkingDirection::Left) {
        position.x -= monster->walking_speed * dt; 
    }
    else if (monster->m_walking_direction == WalkingDirection::UP) {
        position.y += monster->walking_speed * dt; 
    }
    else if (monster->m_walking_direction == WalkingDirection::DOWN) {
        position.y -= monster->walking_speed * dt; 
    }

    monster->SetPosition(position);
}

void Monster::State_Walking::CheckExit(GameObject* object)
{
    Monster* monster = static_cast<Monster*>(object);
    //Math::vec2 player_position = monster->m_player->GetPosition();

    if (monster->current_tile_position == monster->next_tile_position) {
        
        if (0) {
            monster->change_state(&monster->state_dead);
        }

        monster->next_tile_position = monster->path[monster->next_tile_position];
        Math::ivec2 direction = monster->path[monster->next_tile_position] - monster->next_tile_position;
        if (direction.x == 1) {
            monster->m_walking_direction = WalkingDirection::Right;
        }
        else if (direction.x == -1) {
            monster->m_walking_direction = WalkingDirection::Left;
        }
        else if (direction.y == 1) {
            monster->m_walking_direction = WalkingDirection::UP;
        }
        else if (direction.y == -1) {
            monster->m_walking_direction = WalkingDirection::DOWN;
        }
    }

    //if (player_position.x >= monster->boundary.Left() && player_position.x <= monster->boundary.Right())
    //{
    //    if ((monster->m_walking_direction == WalkingDirection::Right && player_position.x > monster->GetPosition().x) ||
    //        (monster->m_walking_direction == WalkingDirection::Left && player_position.x < monster->GetPosition().x))
    //    {
    //        //monster->change_state(&monster->state_angry);
    //    }
    //}
}
