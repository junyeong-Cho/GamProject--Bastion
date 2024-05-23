#include "Setting.h"
#include "Engine/Audio.h"
#include "Engine/Drawing.h" // Include your drawing functions

Setting::Setting() : bgmVolume(50.0f), sfxVolume(50.0f), isBlurComplete(false), blurProgress(0.0f)
{
}

void Setting::Load()
{
    // Initialization code if needed
}

void Setting::Update(double dt)
{
    if (!isBlurComplete)
    {
        blurProgress += static_cast<float>(dt) / 10;
        if (blurProgress >= 0.5f)
        {
            isBlurComplete = true;
            blurProgress   = 0.5f;
        }
    }

    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Right))
    {
        bgmVolume = std::min(bgmVolume + 5.0f, 100.0f);
        Engine::Instance().GetAudioManager().SetMusicVolume(bgmVolume / 100.0f);
    }
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Left))
    {
        bgmVolume = std::max(bgmVolume - 5.0f, 0.0f);
        Engine::Instance().GetAudioManager().SetMusicVolume(bgmVolume / 100.0f);
    }

    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void Setting::Unload()
{
    // Cleanup code if needed
}

void Setting::Draw()
{
    // Draw the blur effect
    if (!isBlurComplete)
    {
        // Assuming applyMatrix and other drawing functions for blur are available
        ShaderDrawing::set_color(0, 0, 0, static_cast<int>(255 * blurProgress));
        ShaderDrawing::draw_box(Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2, Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y); // Fullscreen blur
    }

    // Draw UI elements for volume control
    // ShaderDrawing::set_color(255, 255, 255, 255);
    ShaderDrawing::draw_text("Main BGM Volume: " + std::to_string(bgmVolume), 500, 500, 40, 1.0f, 1.0f, 1.0f);
}

void Setting::ImguiDraw()
{
    // If you are using ImGui for additional debug UI or settings
}

void Setting::HandleEvent(SDL_Event& event)
{
    // Handle other events if necessary
}