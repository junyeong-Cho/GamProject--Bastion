
#include "MeleeUnit.h"



void MeleeUnit::Update(double dt)
{
    // Update GameObject
    GameObject::Update(dt);

    // Mouse events
    HandleMouseInput();

    // Logger things to trace state
    if (not_clicked)
    {
        Engine::GetLogger().LogDebug("Not click");
    }
    else if (drop)
    {
        Engine::GetLogger().LogDebug("Drop");
    }
    else if (is_moving)
    {
        Engine::GetLogger().LogDebug("Moving");
    }



}