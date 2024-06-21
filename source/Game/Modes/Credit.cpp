#include "Engine/Engine.h"
#include "Game/States.h"

#include "Game/Modes/Credit.h"

Credit::Credit()
{
}

void Credit::Load()
{
}

void Credit::Update(double dt)
{
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void Credit::Unload()
{
}

void Credit::Draw()
{
    credit.Draw(271, 125, 738, 550);
}

void Credit::ImguiDraw()
{
}

void Credit::HandleEvent(SDL_Event& event)
{
}
