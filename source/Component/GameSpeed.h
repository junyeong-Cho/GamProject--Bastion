#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

#include "../Engine/Input.h"

#include "Game/Objects/Units/Unit.h"

class GameSpeed : public GAM200::Component
{
public:
    GameSpeed() : speed(1.0) { }

    ~GameSpeed()
    {
        Engine::Instance().SetSpeed(1.0);
    }


    double GetSpeed() const { return speed; }

    void NextSpeed()
    {
        if (speed == 1.0)
        {
            speed = 2.0;
        }
        else if (speed == 2.0)
        {
            speed = 4.0;
        }
        else if (speed == 4.0)
        {
            speed = 1.0;
        }

        Engine::Instance().SetSpeed(speed);
    }

    virtual void Update(double) override
    {
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

private:
    double speed = 1.0;
};
