#include "../Engine/Engine.h"
#include "../Game/States.h"
#include "Lose.h"

Lose::Lose()
{

}

void Lose::Load()
{
    counter = 0;

  
  
}

void Lose::Update(double dt)
{
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 1.00)
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt;
}

void Lose::Unload()
{

}

void Lose::Draw()
{
  
    lose.Draw(0, 0, 1280, 800);

}

void Lose::ImguiDraw()
{

}

void Lose::HandleEvent(SDL_Event& event)
{

}


