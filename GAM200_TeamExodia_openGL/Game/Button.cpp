#include "../Engine/GameObjectManager.h"

#include "Button.h"
#include "Map.h"

#include "../Engine/DrawShape.h"
#include "BuildMode.h"
#include "Wave.h"
#include "Tower.h"

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
		//shape.SetColor(0, 1, 0, 1);
		if (tower_type[0] == true)
		{
			basic_selected.Draw(1120, 720 - 150, 140, 70);
		}
		if (tower_type[1] == true)
		{
			double_tower_selected.Draw(1120, 720 - 230, 140, 70);
		}
		if (tower_type[2] == true)
		{
			triple_selected.Draw(1120, 720 - 310, 140, 70);
		}
		if (tower_type[3] == true)
		{
			delete_tower_selected.Draw(1120, 720 - 390, 140, 70);
		}
		if (tower_type[4] == true)
		{
			change_t_P_selected.Draw(1120, 720 - 470, 140, 70);
		}
		if (tower_type[5] == true)
		{
			change_t_b_selected.Draw(1120, 720 - 550, 140, 70);
		}
		if (tower_type[6] == true)
		{
			next_wave_selected.Draw(1120 - 40, 720 - 630, 180, 60);
		}
	}
	else
	{
		if (tower_type[0] == true)
		{
			basic.Draw(1120, 720 - 150, 140, 70);
		}
		if (tower_type[1] == true)
		{
			double_tower.Draw(1120, 720 - 230, 140, 70);
		}
		if (tower_type[2] == true)
		{
			triple.Draw(1120, 720 - 310, 140, 70);
		}
		if (tower_type[3] == true)
		{
			delete_tower.Draw(1120, 720 - 390, 140, 70);
		}
		if (tower_type[4] == true)
		{
			change_t_P.Draw(1120, 720 - 470, 140, 70);
		}
		if (tower_type[5] == true)
		{
			change_t_b.Draw(1120, 720 - 550, 140, 70);
		}
		if (tower_type[6] == true)
		{
			next_wave.Draw(1120 - 40, 720 - 630, 180, 60);
		}

	}
	//side.Draw(1060, 720 - 629, 40, 550);


}


Wave_Start_Button::Wave_Start_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{

	tower_type[6] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Wave_Start_Button::func(Math::ivec2 pos)
{

	GAM200::SoundEffect::Wave_Start().play();

	Engine::GetGameStateManager().GetGSComponent<Wave>()->Start();
}


Basic_Tower_Button::Basic_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Basic_Tower_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Basic_Tower);
}


Double_Tower_Button::Double_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[1] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Double_Tower_Button::func(Math::ivec2 pos)
{
	//Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Double_Tower);
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Push_Tower);
}


Triple_Tower_Button::Triple_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[2] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Triple_Tower_Button::func(Math::ivec2 pos)
{
	//Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Triple_Tower);
	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Wide_Tower);
}


Delete_Tower_Button::Delete_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[3] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Delete_Tower_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	//Engine::GetGameStateManager().GetGSComponent<BuildMode>()->DeleteTower();
	Tower_Adopter::GetInstance().Delete();
}


Pass_Tile_Button::Pass_Tile_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[4] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Pass_Tile_Button::func(Math::ivec2 pos)
{
	//Engine::GetGameStateManager().GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Pass__Tile);
	GAM200::SoundEffect::Button_1().Big_play();

	Tower_Adopter::GetInstance().Upgrade();
}


Block_Tile_Button::Block_Tile_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	tower_type[5] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Block_Tile_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Obstacle);
}


Push_Tower_Button::Push_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Push_Tower_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Push_Tower);
}


Wide_Tower_Button::Wide_Tower_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Wide_Tower_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Build(GameObjectTypes::Wide_Tower);
}


Upgrade_Button::Upgrade_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Upgrade_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Tower_Adopter::GetInstance().Upgrade();
}


Delete_Button::Delete_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Delete_Button::func(Math::ivec2 pos)
{
	GAM200::SoundEffect::Button_1().Big_play();

	Tower_Adopter::GetInstance().Delete();
}


Choice_1_Button::Choice_1_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Choice_1_Button::func(Math::ivec2 pos)
{
	Engine::GetLogger().LogDebug("Choice 1 Button func!");
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::SoundEffect::Button_3().play();
		Engine::GetGameStateManager().GetGSComponent<Wave>()->Choice(1);
	}
}
void Choice_1_Button::Draw(Math::TransformationMatrix camera_matrix)
{
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::DrawShape shape;

		shape.DrawRectangle(50, 100, 300, 500);
	}
}


Choice_2_Button::Choice_2_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Choice_2_Button::func(Math::ivec2 pos)
{
	Engine::GetLogger().LogDebug("Choice 2 Button func!");
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::SoundEffect::Button_3().play();

		Engine::GetGameStateManager().GetGSComponent<Wave>()->Choice(2);
	}
}
void Choice_2_Button::Draw(Math::TransformationMatrix camera_matrix)
{
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::DrawShape shape;

		shape.DrawRectangle(400, 100, 300, 500);
	}
}


Choice_3_Button::Choice_3_Button(Math::vec2 position, Math::vec2 size) : Button(position, size)
{
	//tower_type[0] = true;
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Choice_3_Button::func(Math::ivec2 pos)
{
	Engine::GetLogger().LogDebug("Choice 3 Button func!");
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::SoundEffect::Button_3().play();

		Engine::GetGameStateManager().GetGSComponent<Wave>()->Choice(3);
	}
}
void Choice_3_Button::Draw(Math::TransformationMatrix camera_matrix)
{
	if (Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState() == Wave::Wave_State::Upgrade)
	{
		GAM200::DrawShape shape;

		shape.DrawRectangle(750, 100, 300, 500);
	}
}