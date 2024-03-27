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

    void NextSpeed() 
    { 
        (speed == 4) ? (speed = 1) : (++speed); 

        is_changed = true;
        Engine::GetLogger().LogDebug("Speed Changed to " + std::to_string(speed));
        Engine::Instance().SetSpeed(speed);

    }

    void SetSpeedFlag()   { is_changed = true; }
    void UnsetSpeedFlag() { is_changed = false; }

    virtual void Update(double) override
    {
        is_changed = false;

        if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Tab))
        {
            NextSpeed();

        }
        if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetCurrentUnit() != nullptr)
        {
            if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetCurrentUnit()->is_moving && Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::LEFT))
            {
                Engine::Instance().SetSpeed(0.5);
            }
            else
            {
                Engine::Instance().SetSpeed(speed);
            }
        }
    }

    bool IsChanged() const { return is_changed; }

private:
    double speed = 1.0;
    bool   is_changed = false;
};
