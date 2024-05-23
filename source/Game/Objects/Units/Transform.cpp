
#include "Transform.h"
#include "BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Audio.h"

TransformUnit::TransformUnit(double transform_cool, double transform_time, double T_attack_time, double attack_time, int damage, Math::vec2 position, double range) :
    transform_cool(transform_cool),
    transform_time(transform_time),
    T_attack_time(T_attack_time),
    Unit(attack_time, damage, range, position)
{
    //Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}

void TransformUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}
void TransformUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}
void TransformUnit::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    double   dmg    = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, GetDamage());
    InsertDPS(GetDamage());

    if (GetPosition().x < target->GetPosition().x)
        SetScale({ 1, 1 });
    else
        SetScale({ -1, 1 });

    change_state(&state_attacking);
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

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void TransformUnit::State_None::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

}
void TransformUnit::State_Attack::Enter(GameObject* object)
{

    TransformUnit* unit = static_cast<TransformUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void TransformUnit::State_Attack::Update(GameObject* object, double dt)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->attack_count += dt;
}
void TransformUnit::State_Attack::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->change_state(&unit->state_none);
}


bool Transform_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_2:
        return true;
    case GameObjectTypes::Sniper_2:
            return true;
    case GameObjectTypes::Spear_2:
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
    else if (other_object->Type() == GameObjectTypes::Sniper_2)
    {
        new DmgBuff_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Spear_2)
    {
        new AtkspdBuff_4(GetPosition());
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