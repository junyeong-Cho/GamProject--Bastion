
#include "Sniper.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


SniperUnit::SniperUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{

    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void SniperUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void SniperUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw   
    if (attack_animation_count >= 0)
    {
        sniper_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        sniper_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
}

void SniperUnit::ResolveCollision(GameObject* other_object)
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
}
void SniperUnit::State_None::CheckExit(GameObject* object)
{
    SniperUnit* unit = static_cast<SniperUnit*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}

void SniperUnit::State_Attack::Enter(GameObject* object)
{

}
void SniperUnit::State_Attack::Update(GameObject* object, double dt)
{

}
void SniperUnit::State_Attack::CheckExit(GameObject* object)
{


}


bool Sniper_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sniper_2:
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