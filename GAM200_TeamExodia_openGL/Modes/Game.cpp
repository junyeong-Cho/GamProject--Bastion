
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

Game::Game()
{

}

void Game::Load()
{
	condition[0] = false;
	condition[1] = false;
	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// No Camera

	// No Map??		TODO
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower1_Button({ 490,35 }, { 78, 78 }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new tower2_Button({ 490 +102,35 }, { 78, 78 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower3_Button({ 490 +102*2,35 }, { 78, 78 }));


	// Components
	AddGSComponent(new GameSpeed());
	AddGSComponent(new MonsterLimit(40));	// Max Limit of Monster
	AddGSComponent(new Gold(100));			// Initial Gold
	AddGSComponent(new Diamond(100));		// Initial Diamond
	AddGSComponent(new Map());
	AddGSComponent(new Wave());

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


#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
#endif
}

void Game::Update(double dt)
{
	// TODO ?
	GetGSComponent<GameSpeed>()->Update(dt);
	dt *= GetGSComponent<GameSpeed>()->GetSpeed();

	// Update things
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();
	GetGSComponent<GAM200::GameObjectManager>()->MergeTest();

	GetGSComponent<Wave>()->Update(dt);


#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
#endif

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	// Go to "Lose Scene" TODO
	/*MonsterLimit* monster_limit = GetGSComponent<MonsterLimit>();
	if (monster_limit->GameOver())
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Lose));
	}*/

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::M))
	{
		new TestMonster();
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::U))
	{
		new TestUnit();
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::K))
	{
		GetGSComponent<Wave>()->Skip();
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::_1))
	{
		new Sword_1();
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::_2))
	{
		new Bow_1();
	}
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::_3))
	{
		new Bomb_1();
	}

	trash.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("A", 0xFFFFFFFF));

	if (!GetGSComponent<Wave>()->IsResting() &&	Button::difficult != 4)
		time.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Next wave: ", 0xFFFFFFFF));
	else
		time.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));
	
	currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurWave() + 1) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xFFFFFFFF));
	gold.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
	speed.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));
	
	if (Button::difficult == 4)
		monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()), 0xFFFFFFFF));
	else
		
		monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));
		



	if (condition[0] || condition[1] && Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT)) {

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

	GAM200::DrawShape shape;
	GetGSComponent<Map>()->Draw();
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());


	trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));

	currentwave->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 770 }));
	time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 700 }));
	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	speed->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 560 }));
	monsters->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 490 }));
	
	tower_ui.Draw(380, 35, 514, 108);
	if (GetGSComponent<Wave>()->GetCurWave() > GetGSComponent<Wave>()->GetMaxWave()) { //win
		condition[0] = true;
		win.Draw(0, 0, 1280, 800);

	}
	if (Monster::GetRemainingMonster() >= GetGSComponent<MonsterLimit>()->GetLimit()) { //lose
		condition[1] = true;
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