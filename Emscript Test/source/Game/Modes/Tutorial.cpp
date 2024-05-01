
#include "Tutorial.h"

#include "Engine/ShowCollision.h"
#include "Engine/DrawShape.h"
#include "Engine/Font.h"
#include "Engine/Texture.h"
//#include "../Engine/Audio.h"

#include "Component/MonsterLimit.h"
#include "Component/Gold.h"
#include "Component/GameSpeed.h"
#include "Component/Diamond.h"
#include "Component/Map.h"
#include "Component/Wave.h"
#include "Component/Time.h"

#include "Game/Objects/Units/Unit.h"

#include "Game/Objects/Monsters/Monster.h"

#include "Game/Objects/Units/MeleeUnit.h"
#include "Game/Objects/Units/RangedUnit.h"
#include "Game/Objects/Units/MagicUnit.h"
#include "Game/Objects/Button.h"

#include "Game/Fonts.h"


#include <imgui.h>
#include <stb_image.h>
#include <backends/imgui_impl_sdl2.h>

#include "Engine/Particle.h"
#include "Game/Particles.h"

bool tutorial_merge = false;
bool tower_summoned = false;

Tutorial::Tutorial()
{

}

void Tutorial::Load()
{
	tutorial_merge = false;
	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// No Camera

	// No Map??		TODO
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower1_Button({ 490,35 }, { 78, 78 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower2_Button({ 490 + 102,35 }, { 78, 78 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new tower3_Button({ 490 + 102 * 2,35 }, { 78, 78 }));

	AddGSComponent(new GAM200::ParticleManager<Particles::Hit>());
	AddGSComponent(new GAM200::ParticleManager<Particles::MeteorBit>());


	// Components
	AddGSComponent(new GameSpeed());
	AddGSComponent(new MonsterLimit(40));	// Max Limit of Monster
	AddGSComponent(new Gold(110));			// Initial Gold
	AddGSComponent(new Diamond(100));		// Initial Diamond
	AddGSComponent(new Map());
	AddGSComponent(new Wave());
	AddGSComponent(new Time());

	new Bow_1({ 500,600 });

	// TODO
	game_speed_button = new GameSpeed_Button({ 976, 708 }, { 77, 77 });
	skip_button = new Skip_Button({ 1071, 708 }, { 77, 77 });

	// In Game State
	in_game_state = InProgress;

	//BGM
	/*GAM200::SoundEffect::MainMenu_BGM().stopAll();
	GAM200::SoundEffect::Game_BGM().stopAll();
	GAM200::SoundEffect::Game_BGM().loopplay();*/

	helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
	helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Click the button below ", 0xFF7878FF));
	helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("to summon a unit", 0xFF7878FF));

#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
#endif
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
			helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
			helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Drag your unit to the ", 0xFF7878FF));
			helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("another unit to merge", 0xFF7878FF));
		}
		break;
	case Merge:
		if (tutorial_merge == true)
		{
			currentTask = Limit;
			helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
			helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("You can see your monster limit ", 0xFF7878FF));
			helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("on your right", 0xFF7878FF));
		}
		break;
	case Limit:
		if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
		{
			currentTask = TabAndClick;
			helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
			helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("You can change speed by press", 0xFF7878FF));
			helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("\"Tab\" or click the speed button", 0xFF7878FF));
		}
		break;
	case TabAndClick:
		if (Engine::GetGameStateManager().GetGSComponent<GameSpeed>()->GetSpeed() != 1)
		{
			currentTask = Info;
			helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
			helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("You can also see informations", 0xFF7878FF));
			helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("on the right side", 0xFF7878FF));
		}
		break;
	case Info:
		if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
		{
			currentTask = Done;
			helper_trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(".", 0xFF7878FF));
			helper.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Done!", 0xFF7878FF));
			helper_nextLine.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("", 0xFF7878FF));
		}
		break;
	case Done:

		break;
	}

	// Update things
	GetGSComponent<GameSpeed>()->Update(dt);
	GetGSComponent<Time>()->Update(dt);
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();
	GetGSComponent<GAM200::GameObjectManager>()->MergeTest();
	//if(GetGSComponent<UnitInfo>() != nullptr) GetGSComponent<UnitInfo>()->ShowInfo();

	game_speed_button->Update(dt);
	skip_button->Update(dt);

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Store));
	}

	// Words
	trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("A", 0xFFFFFFFF));
	time.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Next wave: ", 0xFFFFFFFF));
	currentwave.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Wave:  /  ", 0xFFFFFFFF));
	gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold: " + std::to_string(GetGSComponent<Gold>()->GetCurrentGold()), 0xFFFFFFFF));
	speed.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Speed: " + std::to_string(static_cast<int>(GetGSComponent<GameSpeed>()->GetSpeed())), 0xFFFFFFFF));

	monsters.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Monster: " + std::to_string(Monster::GetRemainingMonster()) + "/" + std::to_string(GetGSComponent<MonsterLimit>()->GetLimit()), 0xFFFFFFFF));

	// Win State
	if (currentTask == CurrentTask::Done)
	{
		in_game_state = Win;
	}

	// Change State
	if (in_game_state == Win)
	{
		if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}


void Tutorial::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}


void Tutorial::Draw()
{
	// Draw map
	GetGSComponent<Map>()->Draw();
	// Draw objects
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
	// Draw particles later
	GetGSComponent<GAM200::GameObjectManager>()->DrawParticle(Math::TransformationMatrix());



	// UIs
	trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	time->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 700 }));
	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	//speed->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 630 }));
	monsters->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 560 }));
	currentwave->Draw(Math::TranslationMatrix(Math::ivec2{ 910, 490 }));
	Unit* unit = GetGSComponent<GAM200::GameObjectManager>()->GetCurrentUnit(); if (unit != nullptr) unit->ShowInfo();
	tower_ui.Draw(380, 35, 514, 108);
	helper_trash->Draw(Math::TranslationMatrix(Math::ivec2{ -100, -100 }));
	helper->Draw(Math::TranslationMatrix(Math::ivec2{ 20, 550 }));
	helper_nextLine->Draw(Math::TranslationMatrix(Math::ivec2{ 20, 500 }));

	game_speed_button->Draw(Math::TranslationMatrix(game_speed_button->GetPosition()));
	skip_button->Draw(Math::TranslationMatrix(skip_button->GetPosition()));
	// Door effect

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
}

void Tutorial::ImguiDraw()
{

}

void Tutorial::HandleEvent(SDL_Event& event)
{

}