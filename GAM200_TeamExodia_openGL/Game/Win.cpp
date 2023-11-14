
#include "Win.h"

#include "Fonts.h"
#include "../Engine/Engine.h"

Win::Win()
{

}

void Win::Load()
{
	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Win! Press Esc to go back", 0xFFFFFFFF));
}

void Win::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
	}
}

void Win::Unload()
{
	message.reset();
}

void Win::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);

	message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
}

void Win::ImguiDraw()
{

}

void Win::HandleEvent(SDL_Event& event)
{

}
