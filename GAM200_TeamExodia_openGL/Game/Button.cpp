#include "../Engine/GameObjectManager.h"

#include "Button.h"
#include "Map.h"

#include "../Engine/DrawShape.h"
#include "BuildMode.h"
#include "Wave.h"

Button::Button(Math::vec2 position, Math::vec2 size) : GameObject(position), position(position), size(size)
{
	tile_size = Map::GetInstance().GetSize();
}
void Button::Update(double dt)
{
	mouse_position = Engine::GetInput().GetMousePosition();
	mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size.x), static_cast<int>(mouse_position.y / tile_size.y));

	is_on = mouse_position.x >= position.x && mouse_position.x <= position.x + size.x && mouse_position.y >= position.y && mouse_position.y <= position.y + size.y;

	if (is_on == false)
		return;

	if (Engine::GetInput().MouseJustReleased(GAM200::Input::MouseButtons::LEFT))
	{
		func(mouse_tile_position);
	}
}
void Button::func(Math::ivec2 pos)
{

}

void Button::Draw(Math::TransformationMatrix camera_matrix)
{
	GAM200::DrawShape shape;

	if (is_on)
	{
		shape.SetColor(0, 1, 0, 1);
	}
	else
	{
		shape.SetColor(0, 0, 1, 1);
	}
	shape.DrawRectangle(position.x, position.y, size.x, size.y);
}


Wave_Start_Button::Wave_Start_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Wave_Start_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<Wave>()->Start();
}


Basic_Tower_Button::Basic_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Basic_Tower_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Basic_Tower);
}


Double_Tower_Button::Double_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Double_Tower_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Double_Tower);
}


Triple_Tower_Button::Triple_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Triple_Tower_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Triple_Tower);
}


Delete_Tower_Button::Delete_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Delete_Tower_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->DeleteTower();
}


Pass_Tile_Button::Pass_Tile_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Pass_Tile_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Pass__Tile);
}


Block_Tile_Button::Block_Tile_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Block_Tile_Button::func(Math::ivec2 pos)
{
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Block_Tile);
}




/*

Basic_Monster_Button::Basic_Monster_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}
void Basic_Monster_Button::func(Math::ivec2 pos)
{

}


Fast_Monster_Button::Fast_Monster_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}
void Fast_Monster_Button::func(Math::ivec2 pos)
{

}



Slow_Monster_Button::Slow_Monster_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

}
void Slow_Monster_Button::func(Math::ivec2 pos)
{

}

*/