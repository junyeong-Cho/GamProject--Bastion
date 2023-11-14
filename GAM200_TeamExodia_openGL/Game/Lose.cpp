
#include "Lose.h"

#include "Fonts.h"
#include "../Engine/Engine.h"

Lose::Lose()
{

}

void Lose::Load()
{
	message.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Lose... Press Esc to go back", 0xFFFFFFFF));
}

void Lose::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
	}
}

void Lose::Unload()
{
	message.reset();
}

void Lose::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);

	message->Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));
}

void Lose::ImguiDraw()
{

}

void Lose::HandleEvent(SDL_Event& event)
{

}
