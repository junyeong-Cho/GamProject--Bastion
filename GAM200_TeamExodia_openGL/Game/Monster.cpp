

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Monster.h"
#include "States.h"

/*
Robot::Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary) : 
CS230::GameObject(position), m_cat(cat), m_left_boundary(left_boundary), m_right_boundary(right_boundary)
{
    AddGOComponent(new CS230::Sprite("Assets/Robot.spt", (this)));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));

    current_state = &state_walking;
    current_state->Enter(this);
}
*/
Monster::Monster(Math::vec2 position, Player* player) : GameObject(position), m_player(player) {
    //AddGOComponent(new GAM200::RectCollision({ Math::ivec2{static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, Math::ivec2{static_cast<int>(GetPosition().x) + size, static_cast<int>(GetPosition().y + size)} }, this));
    //AddGOComponent(new GAM200::RectCollision(Math::irect{ {static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y)}, {static_cast<int>(GetPosition().x) + size, static_cast<int>(GetPosition().y + size)} }, this));
    //AddGOComponent(new GAM200::RectCollision({ Math::ivec2{0, 0}, boundary.Size() }, this));
    //boundary = Math::irect({ 0, 0 }, { size, size });
}

void Monster::ResolveCollision(GameObject* other_object) {

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
    Math::vec2 scale = monster->GetScale();

    float imageOffset = 11.0;

    if (monster->m_walking_direction == WalkingDirection::Right)
    {
        position.x += monster->walking_speed * dt;

        if (position.x > monster->boundary.Right())
        {
            position.x = monster->boundary.Right();
            monster->m_walking_direction = WalkingDirection::Left; // Start moving left
            scale.x = -fabs(scale.x);
        }
    }
    else // Left
    {
        position.x -= monster->walking_speed * dt;

        if (position.x < monster->boundary.Left())
        {
            position.x = monster->boundary.Left();
            monster->m_walking_direction = WalkingDirection::Right;
            scale.x = fabs(scale.x);
        }
    }

    monster->SetScale(scale);
    monster->SetPosition(position);

}

void Monster::State_Walking::CheckExit(GameObject* object)
{
    Monster* monster = static_cast<Monster*>(object);
    Math::vec2 cat_position = monster->m_player->GetPosition();

    if (cat_position.x >= monster->boundary.Left() && cat_position.x <= monster->boundary.Right())
    {
        if ((monster->m_walking_direction == WalkingDirection::Right && cat_position.x > monster->GetPosition().x) ||
            (monster->m_walking_direction == WalkingDirection::Left && cat_position.x < monster->GetPosition().x))
        {
            //monster->change_state(&monster->state_angry);
        }
    }
}
