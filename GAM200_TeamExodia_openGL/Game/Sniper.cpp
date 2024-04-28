
#include "Sniper.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


SniperUnit::SniperUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
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
    GameObject::Draw(camera_matrix);
}

void SniperUnit::ResolveCollision(GameObject* other_object)
{
    if (current_state->GetName() == "None")
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    attack_animation_count = attack_animation_time;

    //change_state(&state_none);
}

bool SniperUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void SniperUnit::ResolveMerge(GameObject* other_object)
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
void Sniper_2::State_None::Enter(GameObject* object)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Sniper_2::State_None::Update(GameObject* object, double dt)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);

    unit->attack_count += dt;
}
void Sniper_2::State_None::CheckExit(GameObject* object)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Sniper_2::State_Attack::Enter(GameObject* object)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Sniper_2::State_Attack::Update(GameObject* object, double dt)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);

    unit->attack_count += dt;
}
void Sniper_2::State_Attack::CheckExit(GameObject* object)
{
    Sniper_2* unit = static_cast<Sniper_2*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
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
void Sniper_4::State_None::Enter(GameObject* object)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Sniper_4::State_None::Update(GameObject* object, double dt)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);

    unit->attack_count += dt;
}
void Sniper_4::State_None::CheckExit(GameObject* object)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Sniper_4::State_Attack::Enter(GameObject* object)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Sniper_4::State_Attack::Update(GameObject* object, double dt)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);

    unit->attack_count += dt;
}
void Sniper_4::State_Attack::CheckExit(GameObject* object)
{
    Sniper_4* unit = static_cast<Sniper_4*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
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
void Sniper_8::State_None::Enter(GameObject* object)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Sniper_8::State_None::Update(GameObject* object, double dt)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);

    unit->attack_count += dt;
}
void Sniper_8::State_None::CheckExit(GameObject* object)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Sniper_8::State_Attack::Enter(GameObject* object)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Sniper_8::State_Attack::Update(GameObject* object, double dt)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);

    unit->attack_count += dt;
}
void Sniper_8::State_Attack::CheckExit(GameObject* object)
{
    Sniper_8* unit = static_cast<Sniper_8*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
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
void Sniper_16::State_None::Enter(GameObject* object)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Sniper_16::State_None::Update(GameObject* object, double dt)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);

    unit->attack_count += dt;
}
void Sniper_16::State_None::CheckExit(GameObject* object)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Sniper_16::State_Attack::Enter(GameObject* object)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Sniper_16::State_Attack::Update(GameObject* object, double dt)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);

    unit->attack_count += dt;
}
void Sniper_16::State_Attack::CheckExit(GameObject* object)
{
    Sniper_16* unit = static_cast<Sniper_16*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}
