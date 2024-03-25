
#include "Transform.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

TransformUnit::TransformUnit(double transform_cool, double transform_time, double T_attack_time, double attack_time, int damage, Math::vec2 position, double range) :
	transform_cool(transform_cool),
	transform_time(transform_time),
	T_attack_time(T_attack_time),
	attack_time(attack_time),
	damage(damage),
	Unit(range, position)
{
	current_state = &state_none;
	current_state->Enter(this);
}

void TransformUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

}

void TransformUnit::ResolveCollision(GameObject* other_object)
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
    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(GetPosition(), range, damage);
    change_state(&state_none);
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
    unit->transform_count += dt;

    if (!unit->transformed)
    {
        if (unit->transform_count >= unit->transform_cool)
        {
            unit->transformed = true;
        }
    }
    else if (unit->transformed)
    {
        if (unit->transform_count >= unit->transform_time)
        {
            unit->transformed = false;
        }
    }
}
void TransformUnit::State_None::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    if (unit->attack_count >= (unit->transformed ? unit->attack_time : unit->T_attack_time))
    {
        unit->change_state(&unit->state_attacking);
    }
}


void TransformUnit::State_Attack::Enter(GameObject* object)
{

}
void TransformUnit::State_Attack::Update(GameObject* object, double dt)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

    unit->transform_count += dt;

    if (unit->transformed)
    {
        if (unit->transform_count >= unit->transform_cool)
        {
            unit->transformed = true;
        }
    }
    else if (!unit->transformed)
    {
        if (unit->transform_count >= unit->transform_time)
        {
            unit->transformed = false;
        }
    }
}
void TransformUnit::State_Attack::CheckExit(GameObject* object)
{
    TransformUnit* unit = static_cast<TransformUnit*>(object);

}
