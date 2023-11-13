#include "BuildMode.h"
#include "../Engine/DrawShape.h"

#include "Map.h"
#include "Tower.h"
#include "Gold.h"
#include "Monster.h"

BuildMode::BuildMode() : build_mode(false), direction(Direction::RIGHT)
{

	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	int tile_col = Map::GetInstance().GetSize().x;
	int tile_row = Map::GetInstance().GetSize().y;

	tile_size.x = window_size.x / tile_row;
	tile_size.y = window_size.y / tile_col;

	mode = Mode::BUILD_TOWER;
	type = GameObjectTypes::Basic_Tower;
}

void BuildMode::Update()
{

	if (build_mode)
	{
		Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();
		mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size.x), static_cast<int>(mouse_position.y / tile_size.y));

		switch (mode)
		{
		case Mode::CHANGE_TILE:

			if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
			{
				build_mode = false;
				Map::GetInstance().ChangeTile(mouse_tile_position, type);
			}

			break;

		case Mode::BUILD_TOWER:
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
				Map::GetInstance().BuildTower(mouse_tile_position, type, direction);
			}

			break;

		case Mode::DELETE_TOWER:

			if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
			{
				build_mode = false;
				Map::GetInstance().DeleteTower(mouse_tile_position);
			}

			break;
		}

		


		if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::RIGHT))
		{
			build_mode = false;
		}
	}




}
void BuildMode::Draw() {
	if (build_mode == false)
		return;

	GAM200::DrawShape shape;

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
	this->type = type; 
	mode = Mode::BUILD_TOWER;

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


void BuildMode::DeleteTower()
{
	build_mode = true;

	mode = Mode::DELETE_TOWER;

}


void BuildMode::ChangeTile(GameObjectTypes type)
{
	if (Monster::GetRemainMonster() != 0)
	{
		Engine::GetLogger().LogDebug("You are not able to change the tile while the monsters are remaining!");
		return;
	}
	build_mode = true;
	this->type = type;

	mode = Mode::CHANGE_TILE;
}

