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

    gameobjectmanager->Add(new Store_Menu_Button({ 18.6646, 745.1167 }, { 153, 43 }));

    setting_background = Engine::Instance().GetTextureManager().Load("assets/Background/setting.jpg");
}

void Setting::Update(double dt)
{

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
    Engine::GetWindow().Clear(0.2f, 0.4f, 0.7f, 1.0f);
    setting_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    ShaderDrawing::draw_text("Main BGM Volume: " + std::to_string(bgmVolume), 600, 430, 40, 0.196f, 0.196f, 0.196f);



}

void Setting::ImguiDraw()
{
    // If you are using ImGui for additional debug UI or settings
}

void Setting::HandleEvent(SDL_Event& event)
{
    // Handle other events if necessary
}
