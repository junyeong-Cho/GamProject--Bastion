#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Time : public GAM200::Component {
public:
    Time() : time(0) { }

    void Update(double dt) override
    {
        time += dt;
    }

    double CurrentTime() const { return time; }

private:
    double time;
};