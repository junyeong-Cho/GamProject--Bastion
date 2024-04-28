
#include "Transform.h"

#include "Monster.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"

TransformUnit::TransformUnit(double transform_cool, double transform_time, double T_attack_time, double attack_time, int damage, Math::vec2 position, double range) :
    transform_cool(transform_cool),
    transform_time(transform_time),
    T_attack_time(T_attack_time),
    Unit(attack_time, damage, range, position)
{
    //Sound
    GAM200::SoundEffect::Tower_Placing().play();
}

void TransformUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

void TransformUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}

void TransformUnit::ResolveCollision(GameObject* other_object)
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

bool TransformUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void TransformUnit::ResolveMerge(GameObject* other_object)
{

}



bool Transform_2::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_2:
        return true;
    default:
        return false;
    }
}
void Transform_2::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_2)
    {
        new Transform_4(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Transform_2::State_None::Enter(GameObject* object)
{
    Transform_2* unit = static_cast<Transform_2*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Transform_2::State_None::Update(GameObject* object, double dt)
{
    Transform_2* unit = static_cast<Transform_2*>(object);

    unit->attack_count += dt;
}
void Transform_2::State_None::CheckExit(GameObject* object)
{
    Transform_2* unit = static_cast<Transform_2*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Transform_2::State_Attack::Enter(GameObject* object)
{
    Transform_2* unit = static_cast<Transform_2*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Transform_2::State_Attack::Update(GameObject* object, double dt)
{
    Transform_2* unit = static_cast<Transform_2*>(object);

    unit->attack_count += dt;
}
void Transform_2::State_Attack::CheckExit(GameObject* object)
{
    Transform_2* unit = static_cast<Transform_2*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}


bool Transform_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_4:
        return true;
    default:
        return false;
    }
}
void Transform_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_4)
    {
        new Transform_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Transform_4::State_None::Enter(GameObject* object)
{
    Transform_4* unit = static_cast<Transform_4*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Transform_4::State_None::Update(GameObject* object, double dt)
{
    Transform_4* unit = static_cast<Transform_4*>(object);

    unit->attack_count += dt;
}
void Transform_4::State_None::CheckExit(GameObject* object)
{
    Transform_4* unit = static_cast<Transform_4*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Transform_4::State_Attack::Enter(GameObject* object)
{
    Transform_4* unit = static_cast<Transform_4*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Transform_4::State_Attack::Update(GameObject* object, double dt)
{
    Transform_4* unit = static_cast<Transform_4*>(object);

    unit->attack_count += dt;
}
void Transform_4::State_Attack::CheckExit(GameObject* object)
{
    Transform_4* unit = static_cast<Transform_4*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}


bool Transform_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
    case GameObjectTypes::Transform_8:
        return true;
    default:
        return false;
    }
}
void Transform_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Transform_8)
    {
        new Transform_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}
void Transform_8::State_None::Enter(GameObject* object)
{
    Transform_8* unit = static_cast<Transform_8*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Transform_8::State_None::Update(GameObject* object, double dt)
{
    Transform_8* unit = static_cast<Transform_8*>(object);

    unit->attack_count += dt;
}
void Transform_8::State_None::CheckExit(GameObject* object)
{
    Transform_8* unit = static_cast<Transform_8*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Transform_8::State_Attack::Enter(GameObject* object)
{
    Transform_8* unit = static_cast<Transform_8*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Transform_8::State_Attack::Update(GameObject* object, double dt)
{
    Transform_8* unit = static_cast<Transform_8*>(object);

    unit->attack_count += dt;
}
void Transform_8::State_Attack::CheckExit(GameObject* object)
{
    Transform_8* unit = static_cast<Transform_8*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}


bool Transform_16::CanMergeWith(GameObjectTypes type)
{
    /*switch (type)
    {
    default:
        return false;
    }*/
    return false;
}
void Transform_16::ResolveMerge(GameObject* other_object)
{

}
void Transform_16::State_None::Enter(GameObject* object)
{
    Transform_16* unit = static_cast<Transform_16*>(object);
    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    unit->attack_count = 0;

}
void Transform_16::State_None::Update(GameObject* object, double dt)
{
    Transform_16* unit = static_cast<Transform_16*>(object);

    unit->attack_count += dt;
}
void Transform_16::State_None::CheckExit(GameObject* object)
{
    Transform_16* unit = static_cast<Transform_16*>(object);

    if (unit->attack_count >= unit->attack_time)
    {
        unit->change_state(&unit->state_attacking);
    }
}
void Transform_16::State_Attack::Enter(GameObject* object)
{
    Transform_16* unit = static_cast<Transform_16*>(object);

    unit->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::attack));
}
void Transform_16::State_Attack::Update(GameObject* object, double dt)
{
    Transform_16* unit = static_cast<Transform_16*>(object);

    unit->attack_count += dt;
}
void Transform_16::State_Attack::CheckExit(GameObject* object)
{
    Transform_16* unit = static_cast<Transform_16*>(object);

    if (unit->attack_count < unit->attack_time)
    {
        unit->change_state(&unit->state_none);
    }
}