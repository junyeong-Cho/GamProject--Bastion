

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Monster.h"
#include "States.h"


Monster::Monster(Math::vec2 position, Player* player) : GameObject(position), m_player(player) {
    SetPosition(position);
    SetVelocity({ 0, 0 });
    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{60, 60} }, this));

    current_state = &state_walking;
    current_state->Enter(this);

    next_tile_position = path[current_tile_position];

    Engine::GetLogger().LogDebug("Monster constructor");
    path = Astar::GetInstance().GetPath();

    /*for (auto& map : path) {
        Engine::GetLogger().LogDebug(std::to_string(map.first.x) + ", " + std::to_string(map.first.y) + " / " + std::to_string(map.second.x) + ", " + std::to_string(map.second.y));
    }*/
}


void Monster::Update(double dt) {
    GameObject::Update(dt);

   /* Engine::GetLogger().LogDebug("Current tile position: (" + std::to_string(current_tile_position.x) + ", " + std::to_string(current_tile_position.y) +
                                ") Next tile position: (" + std::to_string(next_tile_position.x) + ", " + std::to_string(next_tile_position.y) + ")");*/
}

void Monster::Draw(Math::TransformationMatrix camera_matrix) {
    GAM200::DrawShape monster;

    monster.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    monster.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size, size);
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

    static int tile_size = Engine::GetWindow().GetSize().x / 16;

    Math::vec2 position = monster->GetPosition();

    monster->current_tile_position = Math::ivec2(static_cast<int>(position.x / tile_size), static_cast<int>(position.y / tile_size));
    if (monster->current_tile_position == monster->next_tile_position) {
        Engine::GetLogger().LogDebug(std::to_string(monster->next_tile_position.x) + ", " + std::to_string(monster->next_tile_position.y));
        monster->next_tile_position = monster->path[monster->current_tile_position];
        Engine::GetLogger().LogDebug(std::to_string(monster->next_tile_position.x) + ", " + std::to_string(monster->next_tile_position.y));
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
    /*Engine::GetLogger().LogDebug("Monster State Walking CheckExit\n");
    Monster* monster = static_cast<Monster*>(object);

    if (monster->current_tile_position == monster->next_tile_position) {
        if (0) {
            monster->change_state(&monster->state_walking);
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
    }*/

}
