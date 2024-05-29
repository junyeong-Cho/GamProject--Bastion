#include "Editor.h"

#include <backends/imgui_impl_sdl2.h>
#include <imgui.h>
#include <stb_image.h>

#include "Engine/Audio.h"
#include "Engine/Camera.h"
#include "Engine/DrawShape.h"
#include "Engine/Font.h"
#include "Engine/Particle.h"
#include "Engine/ShowCollision.h"
#include "Engine/Texture.h"

#include "Component/Diamond.h"
#include "Component/GameSpeed.h"
#include "Component/Gold.h"
#include "Component/Map.h"
#include "Component/MonsterLimit.h"
#include "Component/Time.h"
#include "Component/Wave.h"

#include "Game/Objects/Units/MagicUnit.h"
#include "Game/Objects/Units/MeleeUnit.h"
#include "Game/Objects/Units/RangedUnit.h"
#include "Game/Objects/Units/Unit.h"

#include "Game/Objects/Units/BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Game/Fonts.h"
#include "Game/Objects/Button.h"
#include "Game/Particles.h"

//int        startGold    = 110;

extern int diamond;
extern int unit_cost;

Editor::Editor()
{

}

void Editor::Load()
{
    AddGSComponent(new GAM200::GameObjectManager());

    AddGSComponent(new GAM200::Camera({}));

    AddGSComponent(new GameSpeed());

    AddGSComponent(new Gold(110000));
    AddGSComponent(new Diamond(100));
    AddGSComponent(new MonsterLimit(monsterLimit));
    AddGSComponent(new Map());
    AddGSComponent(new Wave());
    AddGSComponent(new Time());
    AddGSComponent(new GAM200::ParticleManager<Particles::Hit>());
    AddGSComponent(new GAM200::ParticleManager<Particles::FontParticle>());

    GAM200::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>();
    if (Button::random == false)
    {
        gameobjectmanager->Add(new tower1_Button({ 530.918, 31.5268 }, { 88, 88 }));
        gameobjectmanager->Add(new tower2_Button({ 658.918, 31.5268 }, { 88, 88 }));
        gameobjectmanager->Add(new tower3_Button({ 786.918, 31.5268 }, { 88, 88 }));
        // tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
    }
    else
    {
        gameobjectmanager->Add(new random_tower_Button({ 490 + 102, 35 }, { 78, 78 }));
        // tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
    }
    gameobjectmanager->Add(new GameSpeed_Button({ 1016.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Skip_Button({ 1144.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Setting_Button({ 61.3611, 688.3434 }, { 74.1758, 74.1758 }));

    in_game_state = InProgress;

    GetGSComponent<Wave>()->SetWave("assets/maps/Wave_Editor.txt");

    Engine::GetAudioManager().StopMusic(GAM200::AudioID::MainMenu_BGM);
    Engine::GetAudioManager().PlayMusic(GAM200::AudioID::Game_BGM);
}

void Editor::Update(double dt)
{
    count += dt;

    GetGSComponent<GameSpeed>()->Update(dt);
    GetGSComponent<Time>()->Update(dt);
    GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<GAM200::GameObjectManager>()->MergeTest();
    GetGSComponent<Wave>()->Update(dt);

    Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

#if IfWantShader

#else
    trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("A", 0xFFFFFFFF));
    if (GetGSComponent<Wave>()->IsResting() || Button::difficult == 4)
        time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                       .PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));
    currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                          .PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xFFFFFFFF));
    gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
    speed.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));

    if (Button::difficult != 4)
        monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                           .PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));
#endif
    switch (in_game_state)
    {
        case (InProgress):
            break;
        case (Win):
            //if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
            //{
            //    diamond += (GetGSComponent<Wave>()->GetCurWave() + 1) * 5;
            //    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
            //}
            break;
        case (Lose): 
            if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space))
            {
                //Monster::SetRemainingMonster(0);
            }
            break;
        default: break;
    }


    if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
    }
    if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit() && Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Space))
    {
        Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->DeleteAllMonster();
    }

}

void Editor::Unload()
{
    GetGSComponent<GAM200::GameObjectManager>()->Unload();
    ClearGSComponent();
}

void Editor::Draw()
{
    Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();
    GetGSComponent<Map>()->Draw(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(camera_matrix);

    Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (unit != nullptr)
        unit->ShowInfo();
    //tower_ui.Draw(380, 35, 514, 108);

#if IfWantShader
    //if (GetGSComponent<Wave>()->IsResting())
        //ShaderDrawing::draw_text("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 1100, 600, 50, 255, 255, 255);
    if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit())
    {
        ShaderDrawing::draw_text("Excessive monster", 1100, 600, 25, 255, 255, 255);
    }
    ShaderDrawing::draw_text("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 1100, 530, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 1100, 460, 50, 255, 255, 255);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 563.2783, 31.0342, 20, 0.196f, 0.196f, 0.196f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 691.2783, 31.0342, 20, 0.196f, 0.196f, 0.196f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 819.2773, 31.0342, 20, 0.196f, 0.196f, 0.196f);
#else
    trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
    time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 700 }));
    gold->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
    // speed->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
    monsters->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 560 }));
    currentwave->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 490 }));
#endif

#if !defined(__EMSCRIPTEN__)
    if (count < 3.0)
    {
        Engine::Instance().push();
        GAM200::DrawShape shape;
        Math::ivec2       window_size = Engine::GetWindow().GetSize();
        shape.SetColor(0.f, 0.f, 0.f, 1.f);
        shape.DrawRectangle(static_cast<int>(-count * 500), 0, window_size.x / 2, window_size.y);
        shape.DrawRectangle(window_size.x / 2 + static_cast<int>(count * 500), 0, window_size.x / 2, window_size.y);
        Engine::Instance().pop();
    }
#endif
}

void Editor::ImguiDraw()
{
    if (ImGui::Button("Jewel1"))
    {
        new Monster_1();
    }
    ImGui::SameLine();
    if (ImGui::Button("Jewel2"))
    {
        new Monster_2();
    }
    ImGui::SameLine();
    if (ImGui::Button("Jewel3"))
    {
        new Monster_3();
    }
    ImGui::SameLine();
    if (ImGui::Button("Jewel4"))
    {
        new Monster_4();
    }
    ImGui::SameLine();
    if (ImGui::Button("Jewel5"))
    {
        new Monster_5();
    }
    ImGui::SameLine();
    if (ImGui::Button("Jewel6"))
    {
        new Monster_6();
    }
    if (ImGui::Button("Robot1"))
    {
        new Monster_7();
    }
    ImGui::SameLine();
    if (ImGui::Button("Robot2"))
    {
        new Monster_8();
    }
    ImGui::SameLine();
    if (ImGui::Button("Robot3"))
    {
        new Monster_9();
    }
    if (ImGui::Button("Devil"))
    {
        new Monster_10();
    }
    ImGui::SameLine();
    if (ImGui::Button("Devil2"))
    {
        new Monster_11();
    }
    ImGui::SameLine();
    if (ImGui::Button("Akuma"))
    {
        new Monster_12();
    }
    ImGui::SameLine();
    if (ImGui::Button("Akuma2"))
    {
        new Monster_13();
    }
    if (ImGui::Button("mimic"))
    {
        new Monster_14();
    }
    ImGui::SameLine();
    if (ImGui::Button("BanBanMon"))
    {
        new Monster_15();
    }
    ImGui::SameLine();
    if (ImGui::Button("Boss"))
    {
        new Monster_16();
    }
    if (ImGui::SliderInt("Adjust Limit", &adjusted_monsterLimit, 40, 100, "%d"))
    {
        monsterLimit = adjusted_monsterLimit;
    }
    if (ImGui::Button("Enable Speed Reduction"))
    {
        ShaderDrawing::draw_box(640, 200, 1280, 400);
        Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->ReduceSpeedAndAttackRateIfBottom(true, 400, 0.5);
    }
    if (ImGui::Button("Disable Speed Reduction"))
    {
        Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->ReduceSpeedAndAttackRateIfBottom(false, 400, 0.5);
    }
}

void Editor::HandleEvent(SDL_Event& event)
{
}