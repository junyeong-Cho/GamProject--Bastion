#pragma once

#include "Engine/Component.h"
#include "Engine/Texture.h"

class Timer : public GAM200::Component
{
public:
    Timer() : time(0)
    {
    }

    void Update(double dt) override
    {
        time -= dt;
    }

    void SetTime()
    {
        time = time_limit;
    }

    double CurrentTime() const
    {
        return time;
    }

    int CurrentTimeInt() const
    {
        return static_cast<int>(time);
    }

    bool IsOver() const
    {
        return time < 0;
    }

private:
    double time;

    static inline const double time_limit = 120;
};