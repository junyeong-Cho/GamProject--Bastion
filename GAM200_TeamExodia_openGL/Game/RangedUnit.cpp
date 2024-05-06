
#include "RangedUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"

extern bool tutorial_merge;

RangedUnit::RangedUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    GAM200::SoundEffect::Tower_Placing().play();
}
void RangedUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
    //GetGOComponent<GAM200::Sprite>()->Update(dt);
}
void RangedUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GAM200::GameObject::Draw(camera_matrix);
}
void RangedUnit::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    if (GetPosition().x < target->GetPosition().x)
        SetScale({ 1, 1 });
    else
        SetScale({ -1, 1 });

    change_state(&state_attacking);
}
bool RangedUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void RangedUnit::ResolveMerge(GameObject* other_object)
{

}


void RangedUnit::State_None::Enter(GameObject* object)
{

    RangedUnit* unit = static_cast<RangedUnit*>(object);
    unit->attack_count = 0;

}
void RangedUnit::State_None::Update(GameObject* object, double dt)
{
    RangedUnit* unit = static_cast<RangedUnit*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void RangedUnit::State_None::CheckExit(GameObject* object)
{
    RangedUnit* unit = static_cast<RangedUnit*>(object);

}
void RangedUnit::State_Attack::Enter(GameObject* object)
{

    RangedUnit* unit = static_cast<RangedUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void RangedUnit::State_Attack::Update(GameObject* object, double dt)
{
    RangedUnit* unit = static_cast<RangedUnit*>(object);

    unit->attack_count += dt;
}
void RangedUnit::State_Attack::CheckExit(GameObject* object)
{
    RangedUnit* unit = static_cast<RangedUnit*>(object);

    unit->change_state(&unit->state_none);
}


bool Bow_1::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_1:
        return true;

    case GameObjectTypes::Bow_1:
        return true;

    case GameObjectTypes::Bomb_1:
        return true;

    default:
        return false;
    }
}
void Bow_1::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_1)
    {
        new Transform_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Bow_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
}


bool Bow_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_2:
        return true;
    default:
        return false;
    }
}
void Bow_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_2)
    {
        new Bow_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool Bow_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_4:
        return true;
    default:
        return false;
    }
}
void Bow_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_4)
    {
        new Bow_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool Bow_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_8:
        return true;
    default:
        return false;
    }
}
void Bow_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_8)
    {
        new Bow_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool Bow_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Bow_16::ResolveMerge(GameObject* other_object)
{

}