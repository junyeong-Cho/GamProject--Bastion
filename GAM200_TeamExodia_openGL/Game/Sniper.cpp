
#include "Sniper.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


SniperUnit::SniperUnit(double attack_time, int damage, Math::vec2 position, double range) :
    attack_time(attack_time),
    damage(damage),
    Unit(range, position)
{

    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void SniperUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

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