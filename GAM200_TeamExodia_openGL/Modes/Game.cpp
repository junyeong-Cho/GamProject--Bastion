
#include "Game.h"

#include "../Engine/ShowCollision.h"
#include "../Engine/DrawShape.h"

#include "../Component/MonsterLimit.h"
#include "../Component/Gold.h"
#include "../Component/GameSpeed.h"
#include "../Component/Diamond.h"
#include "../Component/Map.h"

#include "../Game/Unit.h"

#include "../Game/Monster.h"
#include "../Game/MeleeUnit.h"
#include "../Game/RangedUnit.h"
#include "../Game/MagicUnit.h"


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
}

void Game::ImguiDraw()
{

}

void Game::HandleEvent(SDL_Event& event)
{

}