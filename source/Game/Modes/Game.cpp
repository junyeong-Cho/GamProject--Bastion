
#include "Game.h"

#include <imgui.h>
#include <stb_image.h>
#include <backends/imgui_impl_sdl2.h>

#include "Engine/ShowCollision.h"
#include "Engine/DrawShape.h"
#include "Engine/Font.h"
#include "Engine/Texture.h"
#include "Engine/Audio.h"
#include "Engine/Particle.h"
#include "Engine/Camera.h"

#include "Component/MonsterLimit.h"
#include "Component/Gold.h"
#include "Component/GameSpeed.h"
#include "Component/Diamond.h"
#include "Component/Map.h"
#include "Component/Interface.h"
#include "Component/Wave.h"
#include "Component/Time.h"
#include "Component/Timer.h"

#include "Game/Objects/Units/Unit.h"
#include "Game/Objects/Units/MeleeUnit.h"
#include "Game/Objects/Units/RangedUnit.h"
#include "Game/Objects/Units/MagicUnit.h"
#include "Game/Objects/Units/BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Game/Fonts.h"
#include "Game/Objects/Button.h"
#include "Game/Particles.h"

#include "Engine/Camera.h"
#include "Engine/GameObject.h"

int startGold = 110;
int monsterLimit = 40;
extern int diamond;
extern int unit_cost;
extern int selected_map;
bool       isended = false;

Game::Game()
{
}

void Game::Load()
{
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
    AddGSComponent(new Timer());

    GAM200::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>();
	if (Button::random == false)
    {
        gameobjectmanager->Add(new random_tower_Button({ 530.918 -128, 31.5268 }, { 88, 88 }));
        gameobjectmanager->Add(new tower1_Button({ 530.918, 31.5268 }, { 88, 88 }));
        gameobjectmanager->Add(new tower2_Button({ 658.918, 31.5268 }, { 88, 88 }));
        gameobjectmanager->Add(new tower3_Button({ 786.918, 31.5268 }, { 88, 88 }));
	}
	else
	{
        gameobjectmanager->Add(new random_tower_Button({ 594.918, 31.5268 }, { 88, 88 }));
	}
    gameobjectmanager->Add(new GameSpeed_Button({ 1016.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Skip_Button({ 1144.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Setting_Button({ 108.7507 - 153/2, 800 - 43.44- 43/2 }, { 153, 43 }));

	in_game_state = InProgress;

	GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");

    Engine::GetAudioManager().StopMusic(GAM200::AudioID::MainMenu_BGM);
    Engine::GetAudioManager().PlayMusic(GAM200::AudioID::Game_BGM);
}

void Game::Update(double dt)
{
    count += dt;
    if (!GetGSComponent<Wave>()->IsResting())
    {
        wave_signal_count += dt;
    }
    if (GetGSComponent<Wave>()->IsResting())
    {
        wave_signal_count = 0;
    }

    std::cout << wave_signal_count << std::endl;

	GetGSComponent<GameSpeed>()->Update(dt);
	GetGSComponent<Time>()->Update(dt);
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::GameObjectManager>()->MergeTest();
	GetGSComponent<Wave>()->Update(dt);
    GetGSComponent<MonsterLimit>()->GetCurrentMonster();
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

#if IfWantShader

#else
    trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("A", 0xFFFFFFFF));
    if (GetGSComponent<Wave>()->IsResting())
        time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                       .PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));
    currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                          .PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xFFFFFFFF));
    gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
    speed.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));
    monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined))
                       .PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));
#endif

    if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit())
    {
        in_game_state = Lose;
    }
    switch (in_game_state)
    {
        case InProgress:
            if (GetGSComponent<Wave>()->GetState() == Wave::End)
            {
                in_game_state == Boss;
                GetGSComponent<Timer>()->SetTime();
            }
            break;

        case Boss:
            GetGSComponent<Timer>()->Update(dt);
            if (Monster::GetRemainingMonster() == 0)
            {
                in_game_state = Win;
            }
            break;

        case Win:
        case Lose:
            if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
            {
                diamond += (GetGSComponent<Wave>()->GetCurWave() + 1) * 5;
                Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
            }
            break;
    }
}

void Game::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
    Engine::GetAudioManager().StopAllMusic();
	ClearGSComponent();

}


void Game::Draw()
{
    Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();
  
    GetGSComponent<Map>()->Draw(camera_matrix, selected_map);
    if (selected_map > 2)
    {
        lefttrain.Draw(37.802, wave_signal_count * 400 - 3809, 304, 3809);
        righttrain.Draw(939.6, wave_signal_count * 400 - 3809, 304, 3809);
    }

    switch (rand() % 3)
    {
        case 0: cloud1.Draw(0, wave_signal_count * 100 - 4000, 2294, 3997); break;
        case 1: cloud2.Draw(0, wave_signal_count * 100 - 4000, 2294, 3997); break;
        case 2: cloud3.Draw(0, wave_signal_count * 100 - 4000, 2294, 3997); break;
        default: break;
    }
    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(camera_matrix);
    GetGSComponent<Interface>()->Draw(camera_matrix);

    Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (unit != nullptr)
    {
        unit->ShowInfo();
        unit->DrawMergeList();
    }
    if (Button::random)
    {
    }
    else
    {
    }
#if IfWantShader
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


    if (!Button::random)
    {
        ShaderDrawing::draw_text(std::to_string(unit_cost), 575.4382, 36.0547, 20, 0.196f, 0.196f, 0.196f);
        ShaderDrawing::draw_text(std::to_string(unit_cost), 702.918, 36.0547, 20, 0.196f, 0.196f, 0.196f);
        ShaderDrawing::draw_text(std::to_string(unit_cost), 830.917, 36.0547, 20, 0.196f, 0.196f, 0.196f);

    }

    if (GetGSComponent<Wave>()->IsResting() &&
        (GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()) <= 2 &&
        (GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()) >= 0)
    {
        if ((GetGSComponent<Wave>()->GetCurWave() + 1 > 9))
        {
            ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1), 715.377, 340.6201, 127.01, 1.0f, 0.423529f, 0.0f, 0.392157f);
        }
}
#else

	trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 700 }));
	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	//speed->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	monsters->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 560 }));
	currentwave->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 490 }));
#endif

#if !defined(__EMSCRIPTEN__)
	if (count < 3.0)
	{
		Engine::Instance().push();
		GAM200::DrawShape shape;
		Math::ivec2 window_size = Engine::GetWindow().GetSize();
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

    if (!GetGSComponent<Wave>()->IsResting() && wave_signal_count < 2.0)
    {
        if ((GetGSComponent<Wave>()->GetCurWave() + 1 > 9)) {
            wave2.Draw(1280 * wave_signal_count - 1280, 302.3333, 1280, 200);
            ShaderDrawing::ShaderDraw::setFont("assets/font/Eina01-Bold.ttf");
            ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1), 1280 * wave_signal_count + 715.377 + 70- 1280, 340.6201 + 20, 127.01, 1.0f, 0.423529f, 0.0f, 0.392157);
        }
        else {
            wave1.Draw(1280 * wave_signal_count - 1280, 302.3333, 1280, 200);
            ShaderDrawing::ShaderDraw::setFont("assets/font/Eina01-Bold.ttf");
            ShaderDrawing::draw_text(std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1), 1280 * wave_signal_count + 715.377 + 70-1280, 340.6201 + 20, 127.01, 1.0f, 0.423529f, 0.0f, 0.392157);
        }
    }
}

void Game::ImguiDraw()
{

}

void Game::HandleEvent(SDL_Event& event)
{

}