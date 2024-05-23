
#include "MagicUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Audio.h"


MagicUnit::MagicUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    //Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}

void MagicUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}
void MagicUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}
void MagicUnit::ResolveCollision(GameObject* other_object)
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
bool MagicUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void MagicUnit::ResolveMerge(GameObject* other_object)
{

}
void MagicUnit::State_None::Enter(GameObject* object)
{

    MagicUnit* unit = static_cast<MagicUnit*>(object);
    unit->attack_count = 0;

}
void MagicUnit::State_None::Update(GameObject* object, double dt)
{
    MagicUnit* unit = static_cast<MagicUnit*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}


void MagicUnit::State_None::CheckExit(GameObject* object)
{
    MagicUnit* unit = static_cast<MagicUnit*>(object);

}
void MagicUnit::State_Attack::Enter(GameObject* object)
{

    MagicUnit* unit = static_cast<MagicUnit*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void MagicUnit::State_Attack::Update(GameObject* object, double dt)
{
    MagicUnit* unit = static_cast<MagicUnit*>(object);

    unit->attack_count += dt;
}
void MagicUnit::State_Attack::CheckExit(GameObject* object)
{
    MagicUnit* unit = static_cast<MagicUnit*>(object);

    unit->change_state(&unit->state_none);
}


bool Bomb_1::CanMergeWith(GameObjectTypes type)
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
void Bomb_1::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_1)
    {
        new Spear_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Bomb_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
}


bool Bomb_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_2:
        return true;
    default:
        return false;
    }
}
void Bomb_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_2)
    {
        new Bomb_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Bomb_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_4:
        return true;
    default:
        return false;
    }
}
void Bomb_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_4)
    {
        new Bomb_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Bomb_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_8:
        return true;
    default:
        return false;
    }
}
void Bomb_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_8)
    {
        new Bomb_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}


bool Bomb_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Bomb_16::ResolveMerge(GameObject* other_object)
{

}