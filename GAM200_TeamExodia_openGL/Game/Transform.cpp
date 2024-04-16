
#include "Transform.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"

TransformUnit::TransformUnit(double transform_cool, double transform_time, double T_attack_time, double attack_time, int damage, Math::vec2 position, double range) :
    transform_cool(transform_cool),
    transform_time(transform_time),
    T_attack_time(T_attack_time),
    attack_time(attack_time),
    damage(damage),
    Unit(range, position)
{
    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void TransformUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

    attack_animation_count -= dt;
}

void TransformUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // unit draw   
    if (transformed)
    {
        if (attack_animation_count >= 0)
        {
            transform_default_melee_attack->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 300 / 2, 185 / 2);
        }
        else
        {
            transform_default_melee_idle->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 300 / 2, 185 / 2);
        }
    }
    else
    {
        if (attack_animation_count >= 0)
        {
            transform_melee_attack->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 300 / 2, 185 / 2);
        }
        else
        {
            transform_melee_idle->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 300 / 2, 185 / 2);
        }
    }
}

void TransformUnit::ResolveCollision(GameObject* other_object)
{
    if (current_state->GetName() == "None")
        return;
    if (is_moving)
        return;

    /*Monster* target = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestMonster(this);
    if (target == nullptr)
        return;
    Engine::GetLogger().LogDebug("Melee Unit attacked the monster!");
    target->TakeDamage(damage);
    change_state(&state_none);*/
    // TODO
    Monster* target = static_cast<Monster*>(other_object);
    Engine::GetLogger().LogDebug(TypeName() + "Attacked!");
    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(GetPosition(), range, damage);

    attack_animation_count = attack_animation_time;

    change_state(&state_none);
}

bool TransformUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void TransformUnit::ResolveMerge(GameObject* other_object)
{

}


void TransformUnit::State_None::Enter(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->attack_count = 0;
}
void TransformUnit::State_None::Update(GameObject* object, double dt)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->attack_count += dt;
    unit->transform_count += dt;

    if (!unit->transformed)
    {
        if (unit->transform_count >= unit->transform_cool)
        {
            Engine::GetLogger().LogDebug("Transform!");
            unit->transformed = true;
            unit->transform_count = 0;
        }
    }
    else if (unit->transformed)
    {
        if (unit->transform_count >= unit->transform_time)
        {
            Engine::GetLogger().LogDebug("Not Transform!");
            unit->transformed = false;
            unit->transform_count = 0;
        }
    }
}
void TransformUnit::State_None::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    if (unit->attack_count >= (unit->transformed ? unit->attack_time : unit->T_attack_time))
    {
        unit->change_state(&unit->state_attacking);
    }
}


void TransformUnit::State_Attack::Enter(GameObject* object)
{

}
void TransformUnit::State_Attack::Update(GameObject* object, double dt)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->transform_count += dt;

    if (!unit->transformed)
    {
        if (unit->transform_count >= unit->transform_cool)
        {
            unit->transformed = true;
            unit->transform_count = 0;
        }
    }
    else if (unit->transformed)
    {
        if (unit->transform_count >= unit->transform_time)
        {
            unit->transformed = false;
            unit->transform_count = 0;
        }
    }
}
void TransformUnit::State_Attack::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

}




bool Transform_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_2:
        return true;
    default:
        return false;
    }
}
void Transform_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_2)
    {
        new Transform_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Transform_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_4:
        return true;
    default:
        return false;
    }
}
void Transform_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_4)
    {
        new Transform_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Transform_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_8:
        return true;
    default:
        return false;
    }
}
void Transform_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_8)
    {
        new Transform_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Transform_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Transform_16::ResolveMerge(GameObject* other_object)
{

}