
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
#include "Component/Wave.h"
#include "Component/Time.h"

#include "Game/Objects/Units/Unit.h"
#include "Game/Objects/Units/MeleeUnit.h"
#include "Game/Objects/Units/RangedUnit.h"
#include "Game/Objects/Units/MagicUnit.h"

#include "Game/Objects/Units/BuffUnit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Game/Fonts.h"
#include "Game/Objects/Button.h"
#include "Game/Particles.h"

int startGold = 110;
int monsterLimit = 40;
extern int diamond;
extern int unit_cost;

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
        //tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
	}
	else
	{
        gameobjectmanager->Add(new random_tower_Button({ 402.9181, 31.5268 }, { 88, 88 }));
        //tower_ui = GAM200::Texture("assets/buttons/tower_ui.png");
	}
    gameobjectmanager->Add(new GameSpeed_Button({ 1016.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Skip_Button({ 1144.4631, 688.3434 }, { 74.1758, 74.1758 }));
    gameobjectmanager->Add(new Setting_Button({ 61.3611, 688.3434 }, { 74.1758, 74.1758 }));

	in_game_state = InProgress;

	GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");

    Engine::GetAudioManager().StopMusic(GAM200::AudioID::MainMenu_BGM);
    Engine::GetAudioManager().PlayMusic(GAM200::AudioID::Game_BGM);
}

void Game::Update(double dt)
{
    count += dt;

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

    if (in_game_state == InProgress)
    {
        if (GetGSComponent<Wave>()->GetState() == Wave::End && Monster::GetRemainingMonster() == 0)
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
            diamond += (GetGSComponent<Wave>()->GetCurWave() + 1) * 5;
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
        }
    }

    GAM200::Camera* camera = GetGSComponent<GAM200::Camera>();
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Right))
    {
        camera->SetPosition({ camera->GetPosition().x - 1 * camera->GetScale().x, camera->GetPosition().y });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Left))
    {
        camera->SetPosition({ camera->GetPosition().x + 1 * camera->GetScale().x, camera->GetPosition().y });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Up))
    {
        camera->SetPosition({ camera->GetPosition().x, camera->GetPosition().y - 1 * camera->GetScale().x });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::Down))
    {
        camera->SetPosition({ camera->GetPosition().x, camera->GetPosition().y + 1 * camera->GetScale().x });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::I))
    {
        camera->SetScale({ camera->GetScale().x * 1.01, camera->GetScale().y * 1.01 });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetScale().x) + ", " + std::to_string(camera->GetScale().y));
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }
    if (Engine::GetInput().keyDown(GAM200::Input::Keys::O))
    {
        camera->SetScale({ camera->GetScale().x * 0.99, camera->GetScale().y * 0.99 });
        Engine::GetLogger().LogDebug("Camera: ");
        Engine::GetLogger().LogDebug(std::to_string(camera->GetScale().x) + ", " + std::to_string(camera->GetScale().y));
        Engine::GetLogger().LogDebug(std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }

    Unit* target = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Z) && target != nullptr)
    {
        camera->SetPosition(target->GetPosition());
        camera->SetScale({ 3, 3 });

        Engine::GetLogger().LogDebug("Object: " + std::to_string(target->GetPosition().x) + ", " + std::to_string(target->GetPosition().y));
        Engine::GetLogger().LogDebug("Camera: " + std::to_string(camera->GetPosition().x) + ", " + std::to_string(camera->GetPosition().y));
    }


    if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::R))
    {
        camera->Reset();
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
    GetGSComponent<Map>()->Draw(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
    GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(camera_matrix);

    Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetInfoTarget();
    if (unit != nullptr)
    {
        unit->ShowInfo();
        unit->DrawMergeList();
    }
    if (Button::random)
    {
        //tower_ui_random.Draw(380, 35, 514, 108);
    }
    else
    {
        //tower_ui_no_random.Draw(380, 35, 514, 108);
    }
#if IfWantShader
	if (GetGSComponent<Wave>()->IsResting())
        ShaderDrawing::draw_text("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 1100, 600, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 1100, 530, 50, 255, 255, 255);
    ShaderDrawing::draw_text("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 1100, 460, 50, 255, 255, 255);
	ShaderDrawing::draw_text("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 1100, 390, 50, 255, 255, 255);
    if (!Button::random)
    {
        ShaderDrawing::draw_text(std::to_string(unit_cost), 531, 34, 25, 1.0f, 1.0f, 0.0f);
        ShaderDrawing::draw_text(std::to_string(unit_cost), 745, 34, 25, 1.0f, 1.0f, 0.0f);
    }
    ShaderDrawing::draw_text(std::to_string(unit_cost), 638, 34, 25, 1.0f, 1.0f, 0.0f);
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

    GAM200::DrawShape shape;
    shape.DrawCircle(Map::middle_point.x, Map::middle_point.y, 10, 10);
}

void Game::ImguiDraw()
{

}

void Game::HandleEvent(SDL_Event& event)
{

}