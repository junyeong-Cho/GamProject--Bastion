
#include "Sniper.h"
#include "BuffUnit.h"
#include "RangedUnit.h"

#include "Game/Objects/Monsters/Monster.h"


#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Audio.h"


SniperUnit::SniperUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    //Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}
void SniperUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}
void SniperUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}
void SniperUnit::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(GetDamage());
    InsertDPS(GetDamage());

    if (GetPosition().x < target->GetPosition().x)
        SetScale({ 1, 1 });
    else
        SetScale({ -1, 1 });

    change_state(&state_attacking);
}
bool SniperUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void SniperUnit::ResolveMerge(GameObject* other_object)
{

}


void SniperUnit::State_None::Enter(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);
    unit->attack_count = 0;
}
void SniperUnit::State_None::Update(GameObject* object, double dt)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void SniperUnit::State_None::CheckExit(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);
    if (unit->stunned == true)
    {
        unit->change_state(&unit->state_stun);
    }
}
void SniperUnit::State_Attack::Enter(GameObject* object)
{

    SniperUnit* unit = static_cast<SniperUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void SniperUnit::State_Attack::Update(GameObject* object, double dt)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    unit->attack_count += dt;
}
void SniperUnit::State_Attack::CheckExit(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    unit->change_state(&unit->state_none);
}
void SniperUnit::State_Stun::Enter(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    unit->stun_count = 0;
}
void SniperUnit::State_Stun::Update(GameObject* object, double dt)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    unit->stun_count += dt;
}
void SniperUnit::State_Stun::CheckExit(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    if (unit->stun_count >= unit->stun_time)
    {
        unit->change_state(&unit->state_none);
        unit->stunned = false;
    }
}


bool Sniper_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sniper_2:
        return true;
    case GameObjectTypes::Transform_2:
        return true;
    case GameObjectTypes::Spear_2:
        return true;
    default:
        return false;
    }
}
void Sniper_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sniper_2)
    {
        new Sniper_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Transform_2)
    {
        new DmgBuff_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Spear_2)
    {
        new Rambo_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sniper_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sniper_4:
        return true;
    default:
        return false;
    }
}
void Sniper_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sniper_4)
    {
        new Sniper_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sniper_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sniper_8:
        return true;
    default:
        return false;
    }
}
void Sniper_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sniper_8)
    {
        new Sniper_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Sniper_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Sniper_16::ResolveMerge(GameObject* other_object)
{

}