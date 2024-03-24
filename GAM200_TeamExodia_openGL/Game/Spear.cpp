
#include "Spear.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"


SpearUnit::SpearUnit(double attack_time, int damage, Math::vec2 position, double range) :
    attack_time(attack_time),
    damage(damage),
    Unit(range, position)
{

    current_state = &state_none;
    current_state->Enter(this);
}

void SpearUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

}

void SpearUnit::ResolveCollision(GameObject* other_object)
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
    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(GetPosition(), range, damage);
    change_state(&state_none);
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
}
void SpearUnit::State_None::CheckExit(GameObject* object)
{
    SpearUnit* unit = static_cast<SpearUnit*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}

void SpearUnit::State_Attack::Enter(GameObject* object)
{

}
void SpearUnit::State_Attack::Update(GameObject* object, double dt)
{

}
void SpearUnit::State_Attack::CheckExit(GameObject* object)
{


}