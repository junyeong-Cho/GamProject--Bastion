
#include "MeleeUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"


MeleeUnit::MeleeUnit(double attack_time, int damage, Math::vec2 position, double range) :
    attack_time(attack_time),
    damage(damage),
    Unit(range, position)
{ 

    current_state = &state_none;
    current_state->Enter(this);
}

void MeleeUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

}

void MeleeUnit::ResolveCollision(GameObject* other_object)
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
}
void MeleeUnit::State_None::CheckExit(GameObject* object)
{
    MeleeUnit* unit = static_cast<MeleeUnit*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking); 
    }
}

void MeleeUnit::State_Attack::Enter(GameObject* object)
{

}
void MeleeUnit::State_Attack::Update(GameObject* object, double dt)
{

}
void MeleeUnit::State_Attack::CheckExit(GameObject* object)
{


}







void Sword_1::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw        
    if (current_state->GetName() == "None")
    {
        melee_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        melee_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
}


bool Sword_1::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_1:
        return true;

    case GameObjectTypes::Bomb_1:
        return true;

    case GameObjectTypes::Bow_1:
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
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Transform_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Spear_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}



void Sword_2::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw        
    if (current_state->GetName() == "None")
    {
        melee_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        melee_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
}


bool Sword_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    default:
        return false;
    }
}
void Sword_2::ResolveMerge(GameObject* other_object)
{

}