#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"

#include "../Game/States.h"
#include "../Game/Splash.h"

Splash::Splash()
{
    
}

void Splash::Load()
{
    counter = 0;


}

void Splash::Update(double dt)
{
    Engine::GetLogger().LogDebug(std::to_string(counter));


    counter += dt;

    x += (int)(dt * velocity);
}

void Splash::Unload()
{

}

void Splash::Draw()
{
    //Engine::GetWindow().Clear(UINT_MAX);

    Engine::GetWindow().Clear(0.392f, 0.584f, 0.929f, 1.0f);

    GAM200::DrawShape shape;

    shape.DrawLine(0, 0, 500, 500);


    shape.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

    shape.DrawRectangle(0, 0, 600, 400);



    shape.SetColor(0.0f, 1.0f, 0.0f, 1.0f);

    shape.DrawTriangle(x, 0, 500, 400);

}


