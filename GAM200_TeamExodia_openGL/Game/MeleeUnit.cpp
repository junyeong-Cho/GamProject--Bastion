
#include "MeleeUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"

extern bool tutorial_merge;

MeleeUnit::MeleeUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{ 
    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}
void MeleeUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
    //GetGOComponent<GAM200::Sprite>()->Update(dt);
}
void MeleeUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GAM200::GameObject::Draw(camera_matrix);
}
void MeleeUnit::ResolveCollision(GameObject* other_object)
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
bool MeleeUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void MeleeUnit::ResolveMerge(GameObject* other_object)
{

}


void MeleeUnit::State_None::Enter(GameObject* object)
{

    MeleeUnit* unit = static_cast<MeleeUnit*>(object);
    unit->attack_count = 0;

}
void MeleeUnit::State_None::Update(GameObject* object, double dt)
{
    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void MeleeUnit::State_None::CheckExit(GameObject* object)
{
    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

}
void MeleeUnit::State_Attack::Enter(GameObject* object)
{

    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void MeleeUnit::State_Attack::Update(GameObject* object, double dt)
{
    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

    unit->attack_count += dt;
}
void MeleeUnit::State_Attack::CheckExit(GameObject* object)
{
    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

    unit->change_state(&unit->state_none);
}


bool Sword_1::CanMergeWith(GameObjectTypes type)
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
void Sword_1::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_1)
    {
        new Sword_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Transform_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Spear_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
}


bool Sword_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_2:
        return true;
    default:
        return false;
    }
}
void Sword_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_2)
    {
        new Sword_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sword_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_4:
        return true;
    default:
        return false;
    }
}
void Sword_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_4)
    {
        new Sword_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sword_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_8:
        return true;
    default:
        return false;
    }
}
void Sword_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_8)
    {
        new Sword_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sword_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Sword_16::ResolveMerge(GameObject* other_object)
{

}