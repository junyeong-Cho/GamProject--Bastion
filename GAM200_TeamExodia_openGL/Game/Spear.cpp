
#include "Spear.h"

#include "Monster.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


SpearUnit::SpearUnit(double attack_time, int damage, Math::vec2 position, double range) :
    attack_time(attack_time),
    damage(damage),
    Unit(range, position)
{

    current_state = &state_none;
    current_state->Enter(this);

    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}



void SpearUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

    attack_animation_count -= dt;
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

    attack_animation_count = attack_animation_time;

    change_state(&state_none);
}

void SpearUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);

    Math::vec2 position = GetPosition();

    // Unit draw   
    if (attack_animation_count >= 0)
    {
        spear_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
    else
    {
        spear_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
    }
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


bool Spear_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Spear_2:
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
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
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