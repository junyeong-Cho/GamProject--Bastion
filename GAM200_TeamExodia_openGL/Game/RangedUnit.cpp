
#include "RangedUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


RangedUnit::RangedUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{

    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void RangedUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void RangedUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw   
    if (attack_animation_count >= 0)
    {
        shooter_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        shooter_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
}

void RangedUnit::ResolveCollision(GameObject* other_object)
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
    target->TakeDamage(damage);
    InsertDPS(damage);

    attack_animation_count = attack_animation_time;

    change_state(&state_none);
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
}
void RangedUnit::State_None::CheckExit(GameObject* object)
{
    RangedUnit* unit = static_cast<RangedUnit*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}

void RangedUnit::State_Attack::Enter(GameObject* object)
{

}
void RangedUnit::State_Attack::Update(GameObject* object, double dt)
{

}
void RangedUnit::State_Attack::CheckExit(GameObject* object)
{


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
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Bow_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
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