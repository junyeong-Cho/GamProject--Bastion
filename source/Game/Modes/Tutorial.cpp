
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
#include "Component/Interface.h"
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
    AddGSComponent(new Interface());
    AddGSComponent(new Wave());
    AddGSComponent(new Time());
    AddGSComponent(new GAM200::ParticleManager<Particles::Hit>());
    AddGSComponent(new GAM200::ParticleManager<Particles::FontParticle>());

    GAM200::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>();
    gameobjectmanager->Add(new random_tower_Button({ 530.918 - 128, 31.5268 }, { 88, 88 }));
    gameobjectmanager->Add(new tower1_Button({ 530.918, 31.5268 }, { 88, 88 }));
    gameobjectmanager->Add(new tower2_Button({ 658.918, 31.5268 }, { 88, 88 }));
    gameobjectmanager->Add(new tower3_Button({ 786.918, 31.5268 }, { 88, 88 }));
    gameobjectmanager->Add(new GameSpeed_Button({ 1016.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Skip_Button({ 1144.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Setting_Button({ 61.3611, 688.3434 }, { 74.1758, 74.1758 }));

    new Bow_1(Math::vec2{ 600, 600 });

    in_game_state = InProgress;

    GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");

    Engine::GetAudioManager().StopMusic(GAM200::AudioID::MainMenu_BGM);
    Engine::GetAudioManager().PlayMusic(GAM200::AudioID::Game_BGM);

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
    GetGSComponent<Map>()->Draw(camera_matrix,0);



    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(camera_matrix);
    GetGSComponent<Interface>()->Draw(camera_matrix);
    Engine::GetLogger().LogDebug("Current task: " + std::to_string(currentTask));

    Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (unit != nullptr)
        unit->ShowInfo();
    //tower_ui.Draw(380, 35, 514, 108);
    switch (currentTask)
    {
        case SummonUnit: tutorial1.Draw(0,0,1280,800); break;
        case Merge: tutorial2.Draw(0, 0, 1280, 800); break;
        case Limit: tutorial3.Draw(0, 0, 1280, 800); break;
        case TabAndClick: tutorial4.Draw(0, 0, 1280, 800); break;
        case Info: tutorial5.Draw(0, 0, 1280, 800); break;
        case Done: break;
        default: break;
    }
#if IfWantShader
    //if (GetGSComponent<Wave>()->IsResting())
        //ShaderDrawing::draw_text("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 1100, 600, 50, 255, 255, 255);
    //ShaderDrawing::draw_text(std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 960, 65, 31.36, 255, 255, 255);
    //ShaderDrawing::draw_text(std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 615.9102, 736.3091, 31.36, 50, 50, 50);
    //ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 735, 736.3091, 31.36, 255, 255, 255);


    if (GetGSComponent<Wave>()->IsResting())
    {
        ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 640, 731.8542, 20, 0.71f, 0.0f, 0.0f);
        isended = false;
    }
    else
    {
        if ((Monster::GetRemainingMonster() > GetGSComponent<MonsterLimit>()->GetLimit() * 0.8))
        {
            ShaderDrawing::draw_text(std::to_string(Monster::GetRemainingMonster()), 589.5752 + 13, 736.8542, 31.36, 0.71f, 0.0f, 0.0f); // number_warning_color
        }
        else
        {
            ShaderDrawing::draw_text(std::to_string(Monster::GetRemainingMonster()), 589.5752 + 13, 736.8542, 31.36, 0.196f, 0.196f, 0.196f);
        }
        ShaderDrawing::draw_text("/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 627.394 + 15, 739.1143, 22, 0.196f, 0.196f, 0.196f);
        ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 736, 736.8542, 31.36, 0.196f, 0.196f, 0.196f);
        isended = true;
    }
    ShaderDrawing::draw_text(std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 960, 65, 31.36, 0.196f, 0.196f, 0.196f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 566, 34, 25, 1.0f, 1.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 698, 34, 25, 1.0f, 1.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(unit_cost), 830, 34, 25, 1.0f, 1.0f, 0.0f);
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