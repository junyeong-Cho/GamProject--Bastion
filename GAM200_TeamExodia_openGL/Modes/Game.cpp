
#include "Game.h"

#include "../Engine/ShowCollision.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Font.h"
#include "../Engine/Texture.h"

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

Game::Game()
{

}

void Game::Load()
{
	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// No Camera

	// No Map??		TODO



	// Components
	AddGSComponent(new GameSpeed());
	AddGSComponent(new MonsterLimit(40));	// Max Limit of Monster
	AddGSComponent(new Gold(100));			// Initial Gold
	AddGSComponent(new Diamond(100));		// Initial Diamond
	AddGSComponent(new Map());
	AddGSComponent(new Wave());
	GetGSComponent<Wave>()->SetWave("assets/maps/Wave1.txt");


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
	if (monster_limit->GetCurrentMonster() > monster_limit->GetLimit())
	{

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


	time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next wave: " + std::to_string(GetGSComponent<Wave>()->GetRestTime() - GetGSComponent<Wave>()->GetCurTime()), 0xFFFFFFFF));

}


void Game::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}


void Game::Draw()
{
	GetGSComponent<Map>()->Draw();
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

	if(GetGSComponent<Wave>()->IsResting())
		time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 770 }));
}

void Game::ImguiDraw()
{

}

void Game::HandleEvent(SDL_Event& event)
{

}