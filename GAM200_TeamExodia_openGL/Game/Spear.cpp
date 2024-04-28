
#include "Spear.h"

#include "Monster.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


SpearUnit::SpearUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}



void SpearUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void SpearUnit::ResolveCollision(GameObject* other_object)
{
    if (current_state->GetName() == "None")
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(GetPosition(), range, damage);
    InsertDPS(dmg);

    attack_animation_count = attack_animation_time;

    //change_state(&state_none);
}

void SpearUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}

bool SpearUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void SpearUnit::ResolveMerge(GameObject* other_object)
{

}


void Spear_2::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    change_state(&state_attacking);
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
void Spear_2::State_None::Enter(GameObject* object)
{
    Spear_2* unit = static_cast<Spear_2*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Spear_2::State_None::Update(GameObject* object, double dt)
{
    Spear_2* unit = static_cast<Spear_2*>(object);

    unit->attack_count += dt;
}
void Spear_2::State_None::CheckExit(GameObject* object)
{
    Spear_2* unit = static_cast<Spear_2*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Spear_2::State_Attack::Enter(GameObject* object)
{
    Spear_2* unit = static_cast<Spear_2*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Spear_2::State_Attack::Update(GameObject* object, double dt)
{
    Spear_2* unit = static_cast<Spear_2*>(object);

    unit->attack_count += dt;
}
void Spear_2::State_Attack::CheckExit(GameObject* object)
{
    Spear_2* unit = static_cast<Spear_2*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}

void Spear_4::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    change_state(&state_attacking);
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
void Spear_4::State_None::Enter(GameObject* object)
{
    Spear_4* unit = static_cast<Spear_4*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Spear_4::State_None::Update(GameObject* object, double dt)
{
    Spear_4* unit = static_cast<Spear_4*>(object);

    unit->attack_count += dt;
}
void Spear_4::State_None::CheckExit(GameObject* object)
{
    Spear_4* unit = static_cast<Spear_4*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Spear_4::State_Attack::Enter(GameObject* object)
{
    Spear_4* unit = static_cast<Spear_4*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Spear_4::State_Attack::Update(GameObject* object, double dt)
{
    Spear_4* unit = static_cast<Spear_4*>(object);

    unit->attack_count += dt;
}
void Spear_4::State_Attack::CheckExit(GameObject* object)
{
    Spear_4* unit = static_cast<Spear_4*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}

void Spear_8::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    change_state(&state_attacking);
}
bool Spear_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Spear_8:
        return true;
    default:
        return false;
    }
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
void Spear_8::State_None::Enter(GameObject* object)
{
    Spear_8* unit = static_cast<Spear_8*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Spear_8::State_None::Update(GameObject* object, double dt)
{
    Spear_8* unit = static_cast<Spear_8*>(object);

    unit->attack_count += dt;
}
void Spear_8::State_None::CheckExit(GameObject* object)
{
    Spear_8* unit = static_cast<Spear_8*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Spear_8::State_Attack::Enter(GameObject* object)
{
    Spear_8* unit = static_cast<Spear_8*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Spear_8::State_Attack::Update(GameObject* object, double dt)
{
    Spear_8* unit = static_cast<Spear_8*>(object);

    unit->attack_count += dt;
}
void Spear_8::State_Attack::CheckExit(GameObject* object)
{
    Spear_8* unit = static_cast<Spear_8*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}

void Spear_16::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    change_state(&state_attacking);
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
void Spear_16::State_None::Enter(GameObject* object)
{
    Spear_16* unit = static_cast<Spear_16*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Spear_16::State_None::Update(GameObject* object, double dt)
{
    Spear_16* unit = static_cast<Spear_16*>(object);

    unit->attack_count += dt;
}
void Spear_16::State_None::CheckExit(GameObject* object)
{
    Spear_16* unit = static_cast<Spear_16*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Spear_16::State_Attack::Enter(GameObject* object)
{
    Spear_16* unit = static_cast<Spear_16*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Spear_16::State_Attack::Update(GameObject* object, double dt)
{
    Spear_16* unit = static_cast<Spear_16*>(object);

    unit->attack_count += dt;
}
void Spear_16::State_Attack::CheckExit(GameObject* object)
{
    Spear_16* unit = static_cast<Spear_16*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}