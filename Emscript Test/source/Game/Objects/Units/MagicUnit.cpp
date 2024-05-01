
#include "MagicUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"



MagicUnit::MagicUnit(double attack_time, int damage, Math::vec2 position, double range) :
    Unit(attack_time, damage, range, position)
{
    //Sound
    //GAM200::SoundEffect::Tower_Placing().play();
}

void MagicUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void MagicUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}

void MagicUnit::ResolveCollision(GameObject* other_object)
{
    if (current_state->GetName() == "None")
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    attack_animation_count = attack_animation_time;

    //change_state(&state_none);
}

bool MagicUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void MagicUnit::ResolveMerge(GameObject* other_object)
{

}


void Bomb_1::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    change_state(&state_attacking);
}
bool Bomb_1::CanMergeWith(GameObjectTypes type)
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
void Bomb_1::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Sword_1)
    {
        new Spear_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bow_1)
    {
        new Sniper_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
    else if (other_object->Type() == GameObjectTypes::Bomb_1)
    {
        new Bomb_2(GetPosition());
        other_object->Destroy();
        Destroy();
        tutorial_merge = true;
    }
}
void Bomb_1::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bomb_1* unit = static_cast<Bomb_1*>(object);
    unit->attack_count = 0;

}
void Bomb_1::State_None::Update(GameObject* object, double dt)
{
    Bomb_1* unit = static_cast<Bomb_1*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bomb_1::State_None::CheckExit(GameObject* object)
{
    //Bomb_1* unit = static_cast<Bomb_1*>(object);

}
void Bomb_1::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bomb_1* unit = static_cast<Bomb_1*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bomb_1::State_Attack::Update(GameObject* object, double dt)
{
    Bomb_1* unit = static_cast<Bomb_1*>(object);

    unit->attack_count += dt;
}
void Bomb_1::State_Attack::CheckExit(GameObject* object)
{
    Bomb_1* unit = static_cast<Bomb_1*>(object);

    unit->change_state(&unit->state_none);
}


void Bomb_2::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    change_state(&state_attacking);
}
bool Bomb_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_2:
        return true;
    default:
        return false;
    }
}
void Bomb_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_2)
    {
        new Bomb_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bomb_2::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bomb_2* unit = static_cast<Bomb_2*>(object);
    unit->attack_count = 0;

}
void Bomb_2::State_None::Update(GameObject* object, double dt)
{
    Bomb_2* unit = static_cast<Bomb_2*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bomb_2::State_None::CheckExit(GameObject* object)
{
    //Bomb_2* unit = static_cast<Bomb_2*>(object);

}
void Bomb_2::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bomb_2* unit = static_cast<Bomb_2*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bomb_2::State_Attack::Update(GameObject* object, double dt)
{
    Bomb_2* unit = static_cast<Bomb_2*>(object);

    unit->attack_count += dt;
}
void Bomb_2::State_Attack::CheckExit(GameObject* object)
{
    Bomb_2* unit = static_cast<Bomb_2*>(object);

    unit->change_state(&unit->state_none);
}

void Bomb_4::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    change_state(&state_attacking);
}
bool Bomb_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_4:
        return true;
    default:
        return false;
    }
}
void Bomb_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_4)
    {
        new Bomb_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bomb_4::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bomb_4* unit = static_cast<Bomb_4*>(object);
    unit->attack_count = 0;

}
void Bomb_4::State_None::Update(GameObject* object, double dt)
{
    Bomb_4* unit = static_cast<Bomb_4*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bomb_4::State_None::CheckExit(GameObject* object)
{
    //Bomb_4* unit = static_cast<Bomb_4*>(object);

}
void Bomb_4::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bomb_4* unit = static_cast<Bomb_4*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bomb_4::State_Attack::Update(GameObject* object, double dt)
{
    Bomb_4* unit = static_cast<Bomb_4*>(object);

    unit->attack_count += dt;
}
void Bomb_4::State_Attack::CheckExit(GameObject* object)
{
    Bomb_4* unit = static_cast<Bomb_4*>(object);

    unit->change_state(&unit->state_none);
}

void Bomb_8::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    change_state(&state_attacking);
}
bool Bomb_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Bomb_8:
        return true;
    default:
        return false;
    }
}
void Bomb_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Bomb_8)
    {
        new Bomb_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Bomb_8::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bomb_8* unit = static_cast<Bomb_8*>(object);
    unit->attack_count = 0;

}
void Bomb_8::State_None::Update(GameObject* object, double dt)
{
    Bomb_8* unit = static_cast<Bomb_8*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bomb_8::State_None::CheckExit(GameObject* object)
{
    //Bomb_8* unit = static_cast<Bomb_8*>(object);

}
void Bomb_8::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bomb_8* unit = static_cast<Bomb_8*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bomb_8::State_Attack::Update(GameObject* object, double dt)
{
    Bomb_8* unit = static_cast<Bomb_8*>(object);

    unit->attack_count += dt;
}
void Bomb_8::State_Attack::CheckExit(GameObject* object)
{
    Bomb_8* unit = static_cast<Bomb_8*>(object);

    unit->change_state(&unit->state_none);
}

void Bomb_16::ResolveCollision(GameObject* other_object)
{
    if (!AttackReady())
        return;
    if (is_moving)
        return;

    Monster* target = static_cast<Monster*>(other_object);
    int dmg = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->WideDamage(target->GetPosition(), Map::basic_size * 1.5, damage);
    InsertDPS(dmg);

    change_state(&state_attacking);
}
bool Bomb_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Bomb_16::ResolveMerge(GameObject* other_object)
{

}
void Bomb_16::State_None::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("None enter");
    Bomb_16* unit = static_cast<Bomb_16*>(object);
    unit->attack_count = 0;

}
void Bomb_16::State_None::Update(GameObject* object, double dt)
{
    Bomb_16* unit = static_cast<Bomb_16*>(object);

    unit->attack_count += dt;

    if ((!Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->IsMonserNear(unit) || unit->attack_count >= 5.0) && unit->attack_count > 1.0)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
        unit->restart = true;
    }
}
void Bomb_16::State_None::CheckExit(GameObject* object)
{
   // Bomb_16* unit = static_cast<Bomb_16*>(object);

}
void Bomb_16::State_Attack::Enter(GameObject* object)
{
    Engine::GetLogger().LogDebug("Attack enter");
    Bomb_16* unit = static_cast<Bomb_16*>(object);

    if (unit->restart == true)
    {
        unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
        unit->restart = false;
    }
    unit->attack_count = 0;
}
void Bomb_16::State_Attack::Update(GameObject* object, double dt)
{
    Bomb_16* unit = static_cast<Bomb_16*>(object);

    unit->attack_count += dt;
}
void Bomb_16::State_Attack::CheckExit(GameObject* object)
{
    Bomb_16* unit = static_cast<Bomb_16*>(object);

    unit->change_state(&unit->state_none);
}