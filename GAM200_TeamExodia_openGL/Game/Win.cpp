#include "../Engine/Engine.h"
#include "../Game/States.h"
#include "Win.h"

Win::Win()
{

}

void Win::Load()
{
    counter = 0;

    win = GAM200::Texture("assets/win.png", GAM200::Texture::TextureType::RECTANGLE);
}

void Win::Update(double dt)
{
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 1.00)
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt;
}

void Win::Unload()
{

}

void Win::Draw()
{
    
    win.Draw(0, 0, 1280, 800);

}

void Win::ImguiDraw()
{

}

void Win::HandleEvent(SDL_Event& event)
{

}