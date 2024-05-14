
#include "Tutorial.h"

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

extern int startGold;
extern int monsterLimit;
extern int unit_cost;

bool tutorial_merge = false;
bool tower_summoned = false;

Tutorial::CurrentTask Tutorial::currentTask = SummonUnit;

Tutorial::Tutorial()
{
}

void Tutorial::Load()
{
    tutorial_merge = false;
    tower_summoned = false;
    currentTask    = SummonUnit;
    AddGSComponent(new GAM200::GameObjectManager());

    AddGSComponent(new GAM200::Camera({}));

    AddGSComponent(new GameSpeed());
    AddGSComponent(new MonsterLimit(monsterLimit));
    AddGSComponent(new Gold(startGold));
    AddGSComponent(new Diamond(100));
    AddGSComponent(new Map());
    AddGSComponent(new Wave());
    AddGSComponent(new Time());
    AddGSComponent(new GAM200::ParticleManager<Particles::Hit>());
    AddGSComponent(new GAM200::ParticleManager<Particles::FontParticle>());

    GAM200::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>();
    gameobjectmanager->Add(new tower1_Button({ 490, 35 }, { 78, 78 }));
    gameobjectmanager->Add(new tower2_Button({ 490 + 102, 35 }, { 78, 78 }));
    gameobjectmanager->Add(new tower3_Button({ 490 + 102 * 2, 35 }, { 78, 78 }));
    gameobjectmanager->Add(new GameSpeed_Button({ 976, 708 }, { 77, 77 }));
    gameobjectmanager->Add(new Skip_Button({ 1071, 708 }, { 77, 77 }));

    new Bow_1(Math::vec2{ 600, 600 });

    in_game_state = InProgress;

    GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");

    GAM200::SoundEffect::MainMenu_BGM().stopAll();
    GAM200::SoundEffect::Game_BGM().stopAll();
    GAM200::SoundEffect::Game_BGM().loopplay();
}

void Tutorial::Update(double dt)
{
    count += dt;

    switch (currentTask)
    {
        case SummonUnit:
            if (tower_summoned)
            {
                currentTask = Merge;
            }
            break;
        case Merge:
            if (tutorial_merge == true)
            {
                currentTask = Limit;
            }
            break;
        case Limit:
            if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
            {
                currentTask = TabAndClick;
            }
            break;
        case TabAndClick:
            if (Engine::GetGameStateManager().GetGSComponent<GameSpeed>()->GetSpeed() != 1)
            {
                currentTask = Info;
            }
            break;
        case Info:
            if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
            {
                currentTask = Done;
            }
            break;
        case Done: break;
    }

    GetGSComponent<GameSpeed>()->Update(dt);
    GetGSComponent<Time>()->Update(dt);
    GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<GAM200::GameObjectManager>()->MergeTest();
    GetGSComponent<Wave>()->Update(dt);

    Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

#if IfWantShader

#else
    trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("A", 0xFFFFFFFF));
    if (GetGSComponent<Wave>()->IsResting())
        time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));
    currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xFFFFFFFF));
    gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
    speed.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));

    monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));
#endif

    if (in_game_state == InProgress)
    {
        if ((GetGSComponent<Wave>()->GetState() == Wave::End && Monster::GetRemainingMonster() == 0) || currentTask == Done)
        {
            in_game_state = Win;
        }
        if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit())
        {
            in_game_state = Lose;
        }
    }

    if (in_game_state != InProgress)
    {
        if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
        {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
        }
    }
}

void Tutorial::Unload()
{
    GetGSComponent<GAM200::GameObjectManager>()->Unload();
    ClearGSComponent();
}

void Tutorial::Draw()
{
    Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();
    GetGSComponent<Map>()->Draw();
    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(camera_matrix);

    Engine::GetLogger().LogDebug("Current task: " + std::to_string(currentTask));
    switch (currentTask)
    {
        case SummonUnit:
                ShaderDrawing::draw_text("Summon a unit by pressing the button below", 400, 200, 35, 0.0f, 1.0f, 1.0f);
            break;
        case Merge:
                ShaderDrawing::draw_text("Drag your unit to another unit to merge", 400, 500, 35, 0.0f, 1.0f, 1.0f);
            break;
        case Limit:
                ShaderDrawing::draw_text("You can see monster limit on the right side", 400, 500, 35, 0.0f, 1.0f, 1.0f);
            break;
        case TabAndClick:
                ShaderDrawing::draw_text("You can change speed by the button or pressing \"Tab\"", 500, 500, 35, 0.0f, 1.0f, 1.0f);
            break;
        case Info:
                ShaderDrawing::draw_text("You also can see informations on the right side", 450, 500, 35, 0.0f, 1.0f, 1.0f);
            break;
        case Done: 
                ShaderDrawing::draw_text("Done!", 400, 500, 35, 0.0f, 1.0f, 1.0f);
            break;
    }

    Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (unit != nullptr)
        unit->ShowInfo();
    tower_ui.Draw(380, 35, 514, 108);

#if IfWantShader
    if (GetGSComponent<Wave>()->IsResting())
        ShaderDrawing::draw_text("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 1100, 600, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 1100, 530, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 1100, 460, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 1100, 390, 50, 255, 255, 255);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 531, 34, 25, 1.0f, 1.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 638, 34, 25, 1.0f, 1.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 745, 34, 25, 1.0f, 1.0f, 0.0f);
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
    if (in_game_state == Win)
    {
        win.Draw(0, 0, 1280, 800);
    }
    if (in_game_state == Lose)
    {
        lose.Draw(0, 0, 1280, 800);
    }
}


void Tutorial::ImguiDraw()
{

}
void Tutorial::HandleEvent(SDL_Event& event)
{

}