#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

#include "../Engine/Input.h"

#include "../Game/Unit.h"

class GameSpeed : public GAM200::Component
{
public:
    GameSpeed() { }

    double GetSpeed() const { return speed; }

    void NextSpeed() { (speed == 4) ? (speed = 1) : (++speed); }

    virtual void Update(double) override
    {
        if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Tab))
        {
            NextSpeed();
            Engine::GetLogger().LogDebug("Speed Changed to " + std::to_string(speed));
            Engine::Instance().SetSpeed(speed);
        }
        if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetCurrentUnit() != nullptr)
        {
            if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetCurrentUnit()->is_moving)
            {
                Engine::Instance().SetSpeed(0.5);
            }
            else
            {
                Engine::Instance().SetSpeed(speed);
            }
        }
    }

private:
    double speed = 1.0;
};
