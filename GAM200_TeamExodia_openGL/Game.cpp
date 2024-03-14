
#include "Game.h"

#include "../Engine/ShowCollision.h"
#include "../Engine/DrawShape.h"

#include "MonsterLimit.h"
#include "Gold.h"
#include "GameSpeed.h"
#include "Diamond.h"

#include "Monster.h"
#include "MeleeUnit.h"
#include "RangedUnit.h"
#include "MagicUnit.h"


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



#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
#endif
}

void Game::Update(double dt)
{
	// Update GameSpeed
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tab))
	{
		GetGSComponent<GameSpeed>()->NextSpeed();
	}

	// Update things
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();




#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
#endif

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	// Go to "Lose Scene" TODO
	/*MonsterLimit* monster_limit = GetGSComponent<MonsterLimit>();
	if (monster_limit->GetCurrentMonster() > monster_limit->GetLimit())
	{

	}*/


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Space))
	{
		new Monster(3, 3.0);
	}




}


void Game::Unload()
{


	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}


void Game::Draw()
{

	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
}

void Game::ImguiDraw()
{

}

void Game::HandleEvent(SDL_Event& event)
{

}