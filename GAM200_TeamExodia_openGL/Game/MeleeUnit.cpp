
#include "MeleeUnit.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


MeleeUnit::MeleeUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{ 
    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void MeleeUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void MeleeUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GAM200::GameObject::Draw(camera_matrix);
}

void MeleeUnit::ResolveCollision(GameObject* other_object)
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

bool MeleeUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void MeleeUnit::ResolveMerge(GameObject* other_object)
{

}


void Sword_1::ResolveCollision(GameObject* other_object)
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
bool Sword_1::CanMergeWith(GameObjectTypes type)
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
void Sword_1::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Sword_1* unit = static_cast<Sword_1*>(object);
    unit->attack_count = 0;

}
void Sword_1::State_None::Update(GameObject* object, double dt)
{
    Sword_1* unit = static_cast<Sword_1*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Sword_1::State_None::CheckExit(GameObject* object)
{
    Sword_1* unit = static_cast<Sword_1*>(object);

}
void Sword_1::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Sword_1* unit = static_cast<Sword_1*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Sword_1::State_Attack::Update(GameObject* object, double dt)
{
    Sword_1* unit = static_cast<Sword_1*>(object);

    unit->attack_count += dt;
}
void Sword_1::State_Attack::CheckExit(GameObject* object)
{
    Sword_1* unit = static_cast<Sword_1*>(object);

    unit->change_state(&unit->state_none);
}


void Sword_2::ResolveCollision(GameObject* other_object)
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
bool Sword_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_2:
        return true;
    default:
        return false;
    }
}
void Sword_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_2)
    {
        new Sword_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Sword_2::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Sword_2* unit = static_cast<Sword_2*>(object);
    unit->attack_count = 0;

}
void Sword_2::State_None::Update(GameObject* object, double dt)
{
    Sword_2* unit = static_cast<Sword_2*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Sword_2::State_None::CheckExit(GameObject* object)
{
    Sword_2* unit = static_cast<Sword_2*>(object);

}
void Sword_2::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Sword_2* unit = static_cast<Sword_2*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Sword_2::State_Attack::Update(GameObject* object, double dt)
{
    Sword_2* unit = static_cast<Sword_2*>(object);

    unit->attack_count += dt;
}
void Sword_2::State_Attack::CheckExit(GameObject* object)
{
    Sword_2* unit = static_cast<Sword_2*>(object);

    unit->change_state(&unit->state_none);
}

void Sword_4::ResolveCollision(GameObject* other_object)
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
bool Sword_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_4:
        return true;
    default:
        return false;
    }
}
void Sword_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_4)
    {
        new Sword_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Sword_4::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Sword_4* unit = static_cast<Sword_4*>(object);
    unit->attack_count = 0;

}
void Sword_4::State_None::Update(GameObject* object, double dt)
{
    Sword_4* unit = static_cast<Sword_4*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Sword_4::State_None::CheckExit(GameObject* object)
{
    Sword_4* unit = static_cast<Sword_4*>(object);

}
void Sword_4::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Sword_4* unit = static_cast<Sword_4*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Sword_4::State_Attack::Update(GameObject* object, double dt)
{
    Sword_4* unit = static_cast<Sword_4*>(object);

    unit->attack_count += dt;
}
void Sword_4::State_Attack::CheckExit(GameObject* object)
{
    Sword_4* unit = static_cast<Sword_4*>(object);

    unit->change_state(&unit->state_none);
}

void Sword_8::ResolveCollision(GameObject* other_object)
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
bool Sword_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Sword_8:
        return true;
    default:
        return false;
    }
}
void Sword_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_8)
    {
        new Sword_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Sword_8::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Sword_8* unit = static_cast<Sword_8*>(object);
    unit->attack_count = 0;

}
void Sword_8::State_None::Update(GameObject* object, double dt)
{
    Sword_8* unit = static_cast<Sword_8*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Sword_8::State_None::CheckExit(GameObject* object)
{
    Sword_8* unit = static_cast<Sword_8*>(object);

}
void Sword_8::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Sword_8* unit = static_cast<Sword_8*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Sword_8::State_Attack::Update(GameObject* object, double dt)
{
    Sword_8* unit = static_cast<Sword_8*>(object);

    unit->attack_count += dt;
}
void Sword_8::State_Attack::CheckExit(GameObject* object)
{
    Sword_8* unit = static_cast<Sword_8*>(object);

    unit->change_state(&unit->state_none);
}

void Sword_16::ResolveCollision(GameObject* other_object)
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
bool Sword_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Sword_16::ResolveMerge(GameObject* other_object)
{

}
void Sword_16::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Sword_16* unit = static_cast<Sword_16*>(object);
    unit->attack_count = 0;

}
void Sword_16::State_None::Update(GameObject* object, double dt)
{
    Sword_16* unit = static_cast<Sword_16*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Sword_16::State_None::CheckExit(GameObject* object)
{
    Sword_16* unit = static_cast<Sword_16*>(object);

}
void Sword_16::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Sword_16* unit = static_cast<Sword_16*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Sword_16::State_Attack::Update(GameObject* object, double dt)
{
    Sword_16* unit = static_cast<Sword_16*>(object);

    unit->attack_count += dt;
}
void Sword_16::State_Attack::CheckExit(GameObject* object)
{
    Sword_16* unit = static_cast<Sword_16*>(object);

    unit->change_state(&unit->state_none);
}