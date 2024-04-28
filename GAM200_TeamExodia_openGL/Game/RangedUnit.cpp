
#include "RangedUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


RangedUnit::RangedUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    GAM200::SoundEffect::Tower_Placing().play();
}

void RangedUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
    GetGOComponent<GAM200::Sprite>()->Update(dt);
}

void RangedUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GAM200::GameObject::Draw(camera_matrix);
}

void RangedUnit::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    target->TakeDamage(damage);
    InsertDPS(damage);

    //change_state(&state_attacking);
}

bool RangedUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void RangedUnit::ResolveMerge(GameObject* other_object)
{

}


void Bow_1::ResolveCollision(GameObject* other_object)
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
bool Bow_1::CanMergeWith(GameObjectTypes type)
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
void Bow_1::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_1)
    {
        new Transform_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Bow_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bow_1::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bow_1* unit = static_cast<Bow_1*>(object);
    unit->attack_count = 0;

}
void Bow_1::State_None::Update(GameObject* object, double dt)
{
    Bow_1* unit = static_cast<Bow_1*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bow_1::State_None::CheckExit(GameObject* object)
{
    Bow_1* unit = static_cast<Bow_1*>(object);

}
void Bow_1::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bow_1* unit = static_cast<Bow_1*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bow_1::State_Attack::Update(GameObject* object, double dt)
{
    Bow_1* unit = static_cast<Bow_1*>(object);

    unit->attack_count += dt;
}
void Bow_1::State_Attack::CheckExit(GameObject* object)
{
    Bow_1* unit = static_cast<Bow_1*>(object);

    unit->change_state(&unit->state_none);
}


void Bow_2::ResolveCollision(GameObject* other_object)
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
bool Bow_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_2:
        return true;
    default:
        return false;
    }
}
void Bow_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_2)
    {
        new Bow_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bow_2::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bow_2* unit = static_cast<Bow_2*>(object);
    unit->attack_count = 0;

}
void Bow_2::State_None::Update(GameObject* object, double dt)
{
    Bow_2* unit = static_cast<Bow_2*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bow_2::State_None::CheckExit(GameObject* object)
{
    Bow_2* unit = static_cast<Bow_2*>(object);

}
void Bow_2::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bow_2* unit = static_cast<Bow_2*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bow_2::State_Attack::Update(GameObject* object, double dt)
{
    Bow_2* unit = static_cast<Bow_2*>(object);

    unit->attack_count += dt;
}
void Bow_2::State_Attack::CheckExit(GameObject* object)
{
    Bow_2* unit = static_cast<Bow_2*>(object);

    unit->change_state(&unit->state_none);
}

void Bow_4::ResolveCollision(GameObject* other_object)
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
bool Bow_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_4:
        return true;
    default:
        return false;
    }
}
void Bow_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_4)
    {
        new Bow_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bow_4::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bow_4* unit = static_cast<Bow_4*>(object);
    unit->attack_count = 0;

}
void Bow_4::State_None::Update(GameObject* object, double dt)
{
    Bow_4* unit = static_cast<Bow_4*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bow_4::State_None::CheckExit(GameObject* object)
{
    Bow_4* unit = static_cast<Bow_4*>(object);

}
void Bow_4::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bow_4* unit = static_cast<Bow_4*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bow_4::State_Attack::Update(GameObject* object, double dt)
{
    Bow_4* unit = static_cast<Bow_4*>(object);

    unit->attack_count += dt;
}
void Bow_4::State_Attack::CheckExit(GameObject* object)
{
    Bow_4* unit = static_cast<Bow_4*>(object);

    unit->change_state(&unit->state_none);
}

void Bow_8::ResolveCollision(GameObject* other_object)
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
bool Bow_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bow_8:
        return true;
    default:
        return false;
    }
}
void Bow_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bow_8)
    {
        new Bow_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bow_8::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bow_8* unit = static_cast<Bow_8*>(object);
    unit->attack_count = 0;

}
void Bow_8::State_None::Update(GameObject* object, double dt)
{
    Bow_8* unit = static_cast<Bow_8*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bow_8::State_None::CheckExit(GameObject* object)
{
    Bow_8* unit = static_cast<Bow_8*>(object);

}
void Bow_8::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bow_8* unit = static_cast<Bow_8*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bow_8::State_Attack::Update(GameObject* object, double dt)
{
    Bow_8* unit = static_cast<Bow_8*>(object);

    unit->attack_count += dt;
}
void Bow_8::State_Attack::CheckExit(GameObject* object)
{
    Bow_8* unit = static_cast<Bow_8*>(object);

    unit->change_state(&unit->state_none);
}

void Bow_16::ResolveCollision(GameObject* other_object)
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
bool Bow_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Bow_16::ResolveMerge(GameObject* other_object)
{

}
void Bow_16::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bow_16* unit = static_cast<Bow_16*>(object);
    unit->attack_count = 0;

}
void Bow_16::State_None::Update(GameObject* object, double dt)
{
    Bow_16* unit = static_cast<Bow_16*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bow_16::State_None::CheckExit(GameObject* object)
{
    Bow_16* unit = static_cast<Bow_16*>(object);

}
void Bow_16::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bow_16* unit = static_cast<Bow_16*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bow_16::State_Attack::Update(GameObject* object, double dt)
{
    Bow_16* unit = static_cast<Bow_16*>(object);

    unit->attack_count += dt;
}
void Bow_16::State_Attack::CheckExit(GameObject* object)
{
    Bow_16* unit = static_cast<Bow_16*>(object);

    unit->change_state(&unit->state_none);
}