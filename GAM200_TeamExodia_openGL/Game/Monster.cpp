

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Monster.h"
#include "States.h"

#include "Score.h"
#include "Gold.h"
#include "Life.h"

Monster::Monster(Math::vec2 position, Player* player) : GameObject(position), m_player(player) {
    SetPosition(position);
    SetVelocity({ 0, 0 });
    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size_x, size_y} }, this));

    current_state = &state_walking;
    current_state->Enter(this);

    path = Astar::GetInstance().GetPath();

    tile_index = 0;
    current_tile_position = path[tile_index++];
    SetPosition({ 80.0 * static_cast<double>(current_tile_position.x), 80.0 * static_cast<double>(current_tile_position.y) });
    next_tile_position = path[tile_index++];

    fill_color = { 1.0f, 0.0f, 0.0f };

}


void Monster::Update(double dt) {
    GameObject::Update(dt);


}

void Monster::Draw(Math::TransformationMatrix camera_matrix) {
    /*GAM200::DrawShape monster;

    monster.SetColor(fill_color.r, fill_color.g, fill_color.b, 1.0f);

    monster.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);*/
    e.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
  
}

void Monster::ResolveCollision(GameObject* other_object) {

    if (other_object->Type() == GameObjectTypes::Player)
    {
        Engine::GetLogger().LogDebug("Resolve Collision player\n");
        //RemoveGOComponent<GAM200::RectCollision>();

        //change_state(&state_dead);
    }

    if (other_object->Type() == GameObjectTypes::Bullet)
    {
        Engine::GetLogger().LogDebug("Resolve Collision bullet\n");
        RemoveGOComponent<GAM200::RectCollision>();

        Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
        Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

        scoreComponent->Add(score);
        goldComponent->Add(gold);

        change_state(&state_dead);
    }
}

void Monster::State_Dead::Enter(GameObject* object)
{
    Monster* monster = static_cast<Monster*>(object);
    monster->fill_color = { 0.f, 0.f, 0.f };
    //monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}

void Monster::State_Dead::Update(GameObject* object, double dt)
{
    Monster* monster = static_cast<Monster*>(object);

    monster->resisting_count += dt;
    if (monster->resisting_count >= monster->resisting_time) {
        monster->Destroy();
    }
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

        monster->next_tile_position = monster->path[(monster->tile_index++)];

        /*Engine::GetLogger().LogDebug(std::to_string(monster->current_tile_position.x) + ", " + std::to_string(monster->current_tile_position.y) + " -> " + std::to_string(monster->next_tile_position.x) + ", " + std::to_string(monster->next_tile_position.y));
        Engine::GetLogger().LogDebug(std::to_string(monster->GetPosition().x) + ", " + std::to_string(monster->GetPosition().y) + "\n");*/

        if (monster->tile_index == monster->path.size()) {\
            Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
            lifeComponent->Subtract(1);
            monster->change_state(&monster->state_dead);
        }
        Math::ivec2 direction = monster->next_tile_position - monster->current_tile_position;
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

}

Basic_Monster::Basic_Monster(Math::vec2 position, Player* player) : Monster(position, player) {
    fill_color = { 1.0f, 0.0f, 0.0f };
    walking_speed = 80;
    size = 60;

    score = 1;
    gold = 10;
}

Fast_Monster::Fast_Monster(Math::vec2 position, Player* player) : Monster(position, player) {
    fill_color = { 1.0f, 0.984f, 0.255f };
    walking_speed = 160;
    size = 40;

    score = 2;
    gold = 20;
}