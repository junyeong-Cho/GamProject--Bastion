
#include "Game.h"

#include "../Engine/ShowCollision.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Font.h"
#include "../Engine/Texture.h"
#include "../Engine/Audio.h"

#include "../Component/MonsterLimit.h"
#include "../Component/Gold.h"
#include "../Component/GameSpeed.h"
#include "../Component/Diamond.h"
#include "../Component/Map.h"
#include "../Component/Wave.h"

#include "../Game/Unit.h"

#include "../Game/Monster.h"
#include "../Game/MeleeUnit.h"
#include "../Game/RangedUnit.h"
#include "../Game/MagicUnit.h"
#include "../Game/Fonts.h"
#include "../Game/Button.h"

#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>
#include <imgui_impl_sdl.h>

#include "../Engine/Particle.h"
#include "../Game/Particles.h"

Game::Game()
{

}

void Game::Load()
{
	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// No Camera

	// No Map??		TODO
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower1_Button	 ({ 490,35 }, { 78, 78 }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new tower2_Button	 ({ 490 +102,35 }, { 78, 78 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower3_Button	 ({ 490 +102*2,35 }, { 78, 78 }));

	AddGSComponent(new GAM200::ParticleManager<Particles::Hit>());
	AddGSComponent(new GAM200::ParticleManager<Particles::MeteorBit>());


	// Components
	AddGSComponent(new GameSpeed());
	AddGSComponent(new MonsterLimit(40));	// Max Limit of Monster
	AddGSComponent(new Gold(110));			// Initial Gold
	AddGSComponent(new Diamond(100));		// Initial Diamond
	AddGSComponent(new Map());
	AddGSComponent(new Wave());

	GetGSComponent<GAM200::GameObjectManager>()->Add(new GameSpeed_Button({ 490 + 102 * 3 + 330, 748 }, { 55, 55 }));


	// In Game State
	in_game_state = InProgress;


	switch (Button::difficult) {
	case 1:
		GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");
		break;
	case 2:
		GetGSComponent<Wave>()->SetWave("assets/maps/Wave2.txt");
		break;
	case 3:
		GetGSComponent<Wave>()->SetWave("assets/maps/Wave3.txt");
		break;
	case 4:
		break;
	}

	//BGM
	GAM200::SoundEffect::MainMenu_BGM().stopAll();
	GAM200::SoundEffect::Game_BGM().loopplay();


#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
#endif
}

void Game::Update(double dt)
{
	count += dt;



	// TODO ?
	GetGSComponent<GameSpeed>()->Update(dt);
	//dt *= GetGSComponent<GameSpeed>()->GetSpeed();

	if (GetGSComponent<GameSpeed>()->IsChanged())
	{
		GetGSComponent<GAM200::GameObjectManager>()->Add(new GameSpeed_Button({ 490 + 102 * 3 + 330, 748 }, { 55, 55 }));
	}


	// Update things
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();
	GetGSComponent<GAM200::GameObjectManager>()->MergeTest();

	GetGSComponent<Wave>()->Update(dt);


#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
#endif

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::K))
	{
		GetGSComponent<Wave>()->Skip();
	}

	// Words
	trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("A", 0xFFFFFFFF));
	if (!GetGSComponent<Wave>()->IsResting() &&	Button::difficult != 4)
		time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next wave: ", 0xFFFFFFFF));
	else
		time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));
	currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xFFFFFFFF));
	gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
	speed.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));
	
	if (Button::difficult == 4)
		monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()), 0xFFFFFFFF));
	else
		monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));
		

	// Win State
	if (in_game_state == InProgress)
	{
		if (GetGSComponent<Wave>()->GetCurWave() >= GetGSComponent<Wave>()->GetMaxWave() && Monster::GetRemainingMonster() == 0)
		{
			in_game_state = Win;
		}
		// Lose State
		if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit())
		{
			in_game_state = Lose;
		}
	}

	// Change State
	if (in_game_state != InProgress)
	{
		if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}


void Game::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}


void Game::Draw()
{
	// Draw map
	GetGSComponent<Map>()->Draw();
	// Draw objects
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
	// Draw particles later
	GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(Math::TransformationMatrix());

	// UIs
	trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 770 }));
	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 700 }));
	speed->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	monsters->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 560 }));

	tower_ui.Draw(380, 35, 514, 108);


	// Door effect
	GAM200::DrawShape shape;
	if(count < 3.0)
	{
		Engine::Instance().push();
		GAM200::DrawShape shape;
		Math::ivec2 window_size = Engine::GetWindow().GetSize();
		shape.SetColor(0.f, 0.f, 0.f, 1.f);
		shape.DrawRectangle(static_cast<int>(-count * 500), 0, window_size.x / 2, window_size.y);
		shape.DrawRectangle(window_size.x / 2 + static_cast<int>(count * 500), 0, window_size.x / 2, window_size.y);
		Engine::Instance().pop();
	}
	
	if (in_game_state == Win)
	{
		win.Draw(0, 0, 1280, 800);
	}
	if (in_game_state == Lose)
	{
		lose.Draw(0, 0, 1280, 800);
	}
}

void Game::ImguiDraw()
{
	if (Button::difficult == 4) {

		ImGui::Begin("Information");
		{
			int gold = GetGSComponent<Gold>()->GetCurrentGold();

			ImGui::Text("Gold : %d", gold);

			if (ImGui::SliderInt("Adjust Gold", &gold, 0, 50000, "%d")) {
				GetGSComponent<Gold>()->SetCurrentGold(gold);
			}

		}
		ImGui::End();
	}
}

void Game::HandleEvent(SDL_Event& event)
{

}