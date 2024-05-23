
#include "BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Engine/Audio.h"
#include "Engine/DrawShape.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"

DmgBuffUnit::DmgBuffUnit(double buff_amount, Math::vec2 position, double range) : Unit(0.0, 0, range, position), buff_amount(buff_amount)
{
    // Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}

void DmgBuffUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}
bool DmgBuffUnit::CanCollideWith(GameObjectTypes type)
{
    return type > GameObjectTypes::Unit && type < GameObjectTypes::UnitEnd;
}
void DmgBuffUnit::ResolveCollision(GameObject* other_object)
{
    if (is_moving)
        return;

    Unit* unit = static_cast<Unit*>(other_object);
    unit->BuffDmg(buff_amount);
}
void DmgBuffUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}
bool DmgBuffUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void DmgBuffUnit::ResolveMerge(GameObject* other_object)
{
}


bool DmgBuff_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::DmgBuff_4: return true;

        default: return false;
    }
}
void DmgBuff_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::DmgBuff_4)
    {
        new DmgBuff_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool DmgBuff_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::DmgBuff_8: return true;

        default: return false;
    }
}
void DmgBuff_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::DmgBuff_8)
    {
        new DmgBuff_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool DmgBuff_16::CanMergeWith(GameObjectTypes type)
{
    return false;
}
void DmgBuff_16::ResolveMerge(GameObject* other_object)
{
    
}


AtkspdBuffUnit::AtkspdBuffUnit(double buff_amount, Math::vec2 position, double range) : Unit(0.0, 0, range, position), buff_amount(buff_amount)
{
    // Sound
    Engine::GetAudioManager().PlaySound(GAM200::AudioID::Tower_Placing);
}

void AtkspdBuffUnit::Update(double dt)
{
    // Update GameObject
    Unit::Update(dt);
}

bool AtkspdBuffUnit::CanCollideWith(GameObjectTypes type)
{
    return type >= GameObjectTypes::Unit && type < GameObjectTypes::Button;
}

void AtkspdBuffUnit::ResolveCollision(GameObject* other_object)
{
    if (is_moving)
        return;

    Unit* unit = static_cast<Unit*>(other_object);
    unit->BuffAtkspd(buff_amount);
}

void AtkspdBuffUnit::Draw(Math::TransformationMatrix camera_matrix)
{
    Unit::Draw(camera_matrix);
    GameObject::Draw(camera_matrix);
}

bool AtkspdBuffUnit::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void AtkspdBuffUnit::ResolveMerge(GameObject* other_object)
{
}


bool AtkspdBuff_4::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::AtkspdBuff_4: return true;

        default: return false;
    }
}

void AtkspdBuff_4::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::AtkspdBuff_4)
    {
        new AtkspdBuff_8(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool AtkspdBuff_8::CanMergeWith(GameObjectTypes type)
{
    switch (type)
    {
        case GameObjectTypes::AtkspdBuff_8: return true;

        default: return false;
    }
}

void AtkspdBuff_8::ResolveMerge(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::AtkspdBuff_8)
    {
        new AtkspdBuff_16(GetPosition());
        other_object->Destroy();
        Destroy();
    }
}

bool AtkspdBuff_16::CanMergeWith(GameObjectTypes type)
{
    return false;
}

void AtkspdBuff_16::ResolveMerge(GameObject* other_object)
{
}