
#include "Spear.h"
#include "RangedUnit.h"
#include "Sniper.h"
#include "BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Engine/DrawShape.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Audio.h"


SpearUnit::SpearUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    //Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}

void SpearUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}
void SpearUnit::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    double   dmg    = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, GetDamage());
    InsertDPS(dmg);

    if (GetPosition().x < target->GetPosition().x)
        SetScale({ 1, 1 });
    else
        SetScale({ -1, 1 });

    change_state(&state_attacking);
}
void SpearUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}
bool SpearUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void SpearUnit::ResolveMerge(GameObject* other_object)
{

}


void SpearUnit::State_None::Enter(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);
    unit->attack_count = 0;
}
void SpearUnit::State_None::Update(GameObject* object, double dt)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void SpearUnit::State_None::CheckExit(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);
    if (unit->stunned == true)
    {
        unit->change_state(&unit->state_stun);
    }
}
void SpearUnit::State_Attack::Enter(GameObject* object)
{

    SpearUnit* unit = static_cast<SpearUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void SpearUnit::State_Attack::Update(GameObject* object, double dt)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    unit->attack_count += dt;
}
void SpearUnit::State_Attack::CheckExit(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    unit->change_state(&unit->state_none);
}
void SpearUnit::State_Stun::Enter(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    unit->stun_count = 0;
}
void SpearUnit::State_Stun::Update(GameObject* object, double dt)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    unit->stun_count += dt;
}
void SpearUnit::State_Stun::CheckExit(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    if (unit->stun_count >= unit->stun_time)
    {
        unit->change_state(&unit->state_none);
        unit->stunned = false;
    }
}


bool Spear_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Spear_2:
        return true;
    case GameObjectTypes::Transform_2:
        return true;
    case GameObjectTypes::Sniper_2:
        return true;
    default:
        return false;
    }
}
void Spear_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Spear_2)
    {
        new Spear_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Transform_2)
    {
        new AtkspdBuff_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Sniper_2)
    {
        new Rambo_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Spear_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Spear_4:
        return true;
    default:
        return false;
    }
}
void Spear_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Spear_4)
    {
        new Spear_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Spear_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Spear_8:
        return true;
    default:
        return false;
    }
}
void Spear_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Spear_8)
    {
        new Spear_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Spear_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Spear_16::ResolveMerge(GameObject* other_object)
{

}