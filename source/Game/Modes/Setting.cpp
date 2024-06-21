#include "Setting.h"
#include "Engine/Audio.h"
#include "Engine/Drawing.h" // Include your drawing functions

#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"
#include "Game/Objects/Button.h"

extern bool mute;
extern float bgmVolume;

Setting::Setting()
{
}

void Setting::Load()
{
    AddGSComponent(new GAM200::GameObjectManager());

    GAM200::GameObjectManager* gameobjectmanager = GetGSComponent<GAM200::GameObjectManager>();

    gameobjectmanager->Add(new Store_Menu_Button({ 18.6646, 745.1167 }, { 153, 43 }));
    gameobjectmanager->Add(new Sound_reset_Button({ 873.5556, 582.5 }, { 100, 25 }));
    
    setting_background = Engine::Instance().GetTextureManager().Load("assets/Background/setting.jpg");
    sound_box          = Engine::Instance().GetTextureManager().Load("assets/Background/sound_box.png");
    sound_bar          = Engine::Instance().GetTextureManager().Load("assets/buttons/sound_bar.png");
}

void Setting::Update(double dt)
{
    GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

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
    GetGSComponent<GAM200::GameObjectManager>()->Unload();
    ClearGSComponent();
}

void Setting::Draw()
{
    Engine::GetWindow().Clear(0.2f, 0.4f, 0.7f, 1.0f);
    setting_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    sound_box->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    ShaderDrawing::draw_text(std::to_string(static_cast<int>(bgmVolume)), 500.3, 440.493, 40, 0.196f, 0.196f, 0.196f);
    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
    sound_bar->Draw(645.6834 + bgmVolume * 2 - 29.5, 407.693, 117, 95);

}

void Setting::ImguiDraw()
{
    // If you are using ImGui for additional debug UI or settings
}

void Setting::HandleEvent(SDL_Event& event)
{
    // Handle other events if necessary
}
