
#include "MagicUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


MagicUnit::MagicUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{

    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void MagicUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void MagicUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw   
    if (attack_animation_count >= 0)
    {
        bomb_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        bomb_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
}

void MagicUnit::ResolveCollision(GameObject* other_object)
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
    //target->TakeDamage(damage);
    Engine::GetLogger().LogDebug(TypeName() + "Attacked!");
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    attack_animation_count = attack_animation_time;

    change_state(&state_none);
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
}
void MagicUnit::State_None::CheckExit(GameObject* object)
{
    MagicUnit* unit = static_cast<MagicUnit*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}

void MagicUnit::State_Attack::Enter(GameObject* object)
{

}
void MagicUnit::State_Attack::Update(GameObject* object, double dt)
{

}
void MagicUnit::State_Attack::CheckExit(GameObject* object)
{


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
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Bomb_2(GetPosition());
        other_object->Destroy();
        Destroy();
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