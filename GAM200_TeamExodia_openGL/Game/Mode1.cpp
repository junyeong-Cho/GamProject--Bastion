#include "Mode1.h"

#include "../Engine/Engine.h"

Mode1::Mode1()
{

}


void Mode1::Load()
{
	counter = 0;

}

void Mode1::Update(double dt)
{
	//Engine::GetLogger().LogDebug(std::to_string(counter));
	Engine::GetWindow().Clear(0.2f, 0.1f, 0.4f, 1.0f);
}

void Mode1::Unload()
{

}

void Mode1::Draw()
{

}

void Mode1::ImguiDraw()
{

}

void Mode1::HandleEvent(SDL_Event& event)
{

}