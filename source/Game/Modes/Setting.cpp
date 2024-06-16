#include "Setting.h"
#include "Engine/Audio.h"
#include "Engine/Drawing.h" // Include your drawing functions

#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"
#include "Game/Objects/Button.h"

extern bool mute;

Setting::Setting() : bgmVolume(50.0f), sfxVolume(50.0f)
{
}

void Setting::Load()
{
    AddGSComponent(new GAM200::GameObjectManager());

    GAM200::GameObjectManager* gameobjectmanager = GetGSComponent<GAM200::GameObjectManager>();

    gameobjectmanager->Add(new Mute_ONOFF_Button({ 500.3, 440.493 }, { 99, 27 }));

    sound_background = Engine::Instance().GetTextureManager().Load("assets/Background/sound_background.png");
}

void Setting::Update(double dt)
{
    Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Right))
    {
        bgmVolume = std::min(bgmVolume + 5.0f, 100.0f);
        Engine::Instance().GetAudioManager().SetMusicVolume(bgmVolume);
    }
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Left))
    {
        bgmVolume = std::max(bgmVolume - 5.0f, 0.0f);
        Engine::Instance().GetAudioManager().SetMusicVolume(bgmVolume);
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
    sound_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    ShaderDrawing::draw_text("Main BGM Volume: " + std::to_string(bgmVolume), 500, 500, 40, 1.0f, 1.0f, 1.0f);

    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
}

void Setting::ImguiDraw()
{
    // If you are using ImGui for additional debug UI or settings
}

void Setting::HandleEvent(SDL_Event& event)
{
    // Handle other events if necessary
}
