#include "BuildMode.h"
#include "../Engine/DrawShape.h"

#include "Map.h"
#include "Tower.h"
#include "Gold.h"
#include "Monster.h"
#include "Wave.h"

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
		//Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();
		Math::vec2 mouse_position = Math::vec2(Engine::GetInput().GetMousePosition().x - 1, Engine::GetInput().GetMousePosition().y - 1);
		mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size.x), static_cast<int>(mouse_position.y / tile_size.y));

		switch (mode)
		{
		case Mode::CHANGE_TILE:

			if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
			{
				build_mode = false;
				Engine::GetLogger().LogDebug("Change Tile!");
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

			
			if (Map::GetInstance().GetType(Math::ivec2(mouse_tile_position.x, mouse_tile_position.y)) != "Block_Tile")
			{
				//Engine::GetLogger().LogDebug("Not able here!  It is " + Map::GetInstance().GetType(Math::ivec2(mouse_tile_position.x, mouse_tile_position.y)));
				tower_set_available = false;
				
			}
			else if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Basic_Tower::GetCost())
			{
				//Engine::GetLogger().LogDebug("Not enough gold!");
				empty_gold = true;
			}
			else
			{
				tower_set_available = true;
				empty_gold = true;
			}

			if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
			{
				build_mode = false;
				Engine::GetLogger().LogDebug("Build Tower!");
				Map::GetInstance().BuildTower(mouse_tile_position, type, direction);
			}

			break;


		case Mode::DELETE_TOWER:

			if (Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT))
			{
				build_mode = false;
				Engine::GetLogger().LogDebug("Delete Tower!");
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
void BuildMode::Draw() 
{
	if (build_mode == false)
		return;

	GAM200::DrawShape shape;


	if (mode == Mode::BUILD_TOWER)
	{
		Math::ivec2 point1 = Math::ivec2(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y);
		
	
		switch (direction)
		{


		case Direction::UP:
			
			four_way[0] = true;
			four_way[1] = false;
			four_way[2] = false;
			four_way[3] = false;

			break;

		case Direction::RIGHT:
			
			four_way[0] = false;
			four_way[1] = true;
			four_way[2] = false;
			four_way[3] = false;

			break;

		case Direction::DOWN:
			

			four_way[0] = false;
			four_way[1] = false;
			four_way[2] = true;
			four_way[3] = false;

			break;

		case Direction::LEFT:
			

			four_way[0] = false;
			four_way[1] = false;
			four_way[2] = false;
			four_way[3] = true;

			break;
		}
		//shape.DrawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);


		////
		if (tower_set_available == false)
		{
			edit_2_unable_place_aim.Draw(point1.x, point1.y, 80, 80);//suddenly_bomb
		}
		else
			if (empty_gold == false)
			{
				edit_2_unable_aim.Draw(point1.x, point1.y, 80, 80);
			}
			else
			{

				if (four_way[0] == true)//up
				{
					edit_2_up_aim.Draw(point1.x - 40, point1.y - 40, 160, 160);
				}
				else if (four_way[1] == true)//right
				{
					edit_2_right_aim.Draw(point1.x - 40, point1.y - 40, 160, 160);
				}
				else if (four_way[2] == true)//right
				{
					edit_2_down_aim.Draw(point1.x - 40, point1.y-40, 160, 160);
				}
				else if (four_way[3] == true)//right
				{
					edit_2_left_aim.Draw(point1.x - 40, point1.y-40, 160, 160);
				}


			}
		////

		return;
	}
	else if (mode == Mode::CHANGE_TILE )//after_image_add
	{
		change_aim.Draw(mouse_tile_position.x * tile_size.x, static_cast<int>(mouse_tile_position.y * tile_size.y - 17.5), tile_size.x, 115);
	}
	else if ( mode == Mode::DELETE_TOWER)//after_image_add
	{
		delete_aim.Draw(mouse_tile_position.x * tile_size.x, mouse_tile_position.y * tile_size.y, tile_size.x, tile_size.y);
		
	}
	
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

	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::InProgress)
	{
		Engine::GetLogger().LogDebug("You are not able to change the tile while wave is in progress!");
		return;
	}

	build_mode = true;
	this->type = type;

	mode = Mode::CHANGE_TILE;
}

