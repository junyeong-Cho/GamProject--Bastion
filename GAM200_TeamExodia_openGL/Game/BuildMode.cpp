#include "BuildMode.h"
#include "../Engine/DrawShape.h"

#include "Map.h"
#include "Tower.h"
#include "Gold.h"

BuildMode::BuildMode() : build_mode(false), direction(Direction::RIGHT)
{

	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	int tile_col = Map::GetInstance().GetSize().x;
	int tile_row = Map::GetInstance().GetSize().y;

	tile_size.x = window_size.x / tile_row;
	tile_size.y = window_size.y / tile_col;

	
}

void BuildMode::Update()
{
	/*if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::B))
	{
		build_mode = true;
	}*/

	if (build_mode)
	{
		Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();
		mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size.x), static_cast<int>(mouse_position.y / tile_size.y));

		if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Q))
		{
			switch (direction)
			{
			case Direction::RIGHT:
				direction = Direction::UP;
				break;
			case Direction::UP:
				direction = Direction::LEFT;
				break;
			case Direction::LEFT:
				direction = Direction::DOWN;
				break;
			case Direction::DOWN:
				direction = Direction::RIGHT;
				break;
			}
		}
		else if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::E))
		{
			switch (direction)
			{
			case Direction::RIGHT:
				direction = Direction::DOWN;
				break;
			case Direction::DOWN:
				direction = Direction::LEFT;
				break;
			case Direction::LEFT:
				direction = Direction::UP;
				break;
			case Direction::UP:
				direction = Direction::RIGHT;
				break;
			}
		}

		if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
		{
			build_mode = false;
			if (Map::GetInstance().GetType(Math::ivec2(mouse_tile_position.x, mouse_tile_position.y)) != "Block_Tile")
			{
				Engine::GetLogger().LogDebug("Not able here!  It is " + Map::GetInstance().GetType(Math::ivec2(mouse_tile_position.x, mouse_tile_position.y)));
				return;
			}
			else if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Basic_Tower::GetCost())
			{
				Engine::GetLogger().LogDebug("Not enough gold!");
			}
			else
			{
				if(tower_type == GameObjectTypes::Basic_Tower)
					Engine::GetGameStateManager().GetGSComponent <GAM200::GameObjectManager>()->Add(new Basic_Tower({ static_cast<double>(mouse_tile_position.x * static_cast<double>(tile_size.x)), (mouse_tile_position.y * static_cast<double>(tile_size.y)) }, static_cast<int>(direction)));
				else if(tower_type == GameObjectTypes::Double_Tower)
					Engine::GetGameStateManager().GetGSComponent <GAM200::GameObjectManager>()->Add(new Double_Tower({ static_cast<double>(mouse_tile_position.x * static_cast<double>(tile_size.x)), (mouse_tile_position.y * static_cast<double>(tile_size.y)) }, static_cast<int>(direction)));
				else if(tower_type == GameObjectTypes::Triple_Tower)
					Engine::GetGameStateManager().GetGSComponent <GAM200::GameObjectManager>()->Add(new Triple_Tower({ static_cast<double>(mouse_tile_position.x * static_cast<double>(tile_size.x)), (mouse_tile_position.y * static_cast<double>(tile_size.y)) }, static_cast<int>(direction)));

			}
		}
		else if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::RIGHT))
		{
			build_mode = false;
		}
	}




}
void BuildMode::Draw() {
	if (build_mode == false)
		return;

	GAM200::DrawShape shape;

	/*shape.DrawRectangle_NoFill_WithBoundaries(Math::rect(Math::vec2(mouse_tile_position.x * tile_size_x, mouse_tile_position.y * tile_size_y),
														 Math::vec2(mouse_tile_position.x * (tile_size_x + 1), mouse_tile_position.y * (tile_size_y + 1))), camera_matrix);*/

	Math::ivec2 point1 = Math::ivec2(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y);
	Math::ivec2 point2 = Math::ivec2(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y);
	Math::ivec2 point3 = Math::ivec2(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y);

	switch (direction)
	{
	case Direction::RIGHT:
		point2 += Math::ivec2(0, tile_size.y);
		point3 += Math::ivec2(tile_size.x, tile_size.y / 2);
		break;
	case Direction::LEFT:
		point1 += Math::ivec2(0, tile_size.y / 2);
		point2 += Math::ivec2(tile_size.x, 0);
		point3 += Math::ivec2(tile_size.x, tile_size.y);
		break;
	case Direction::UP:
		point2 += Math::ivec2(tile_size.x / 2, tile_size.y);
		point3 += Math::ivec2(tile_size.x, 0);
		break;
	case Direction::DOWN:
		point1 += Math::ivec2(0, tile_size.y);
		point2 += Math::ivec2(tile_size.x, tile_size.y);
		point3 += Math::ivec2(tile_size.x / 2, 0);
		break;

	}
	//shape.DrawRectangle(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y, tile_size.x, tile_size.y);
	shape.DrawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
}

void BuildMode::Build(GameObjectTypes type)
{ 
	build_mode = true;  
	tower_type = type; 

	if (type == GameObjectTypes::Basic_Tower)
	{
		cost = Basic_Tower::GetCost();
	}
	if (type == GameObjectTypes::Double_Tower)
	{
		cost = Double_Tower::GetCost();
	}
	if (type == GameObjectTypes::Triple_Tower)
	{
		cost = Triple_Tower::GetCost();
	}
}