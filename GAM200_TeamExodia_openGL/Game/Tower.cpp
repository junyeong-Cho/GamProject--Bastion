

#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

#include "Bullet.h"
#include "Tower.h"
#include "Gold.h"
#include "Map.h"
#include "Monster.h"

Tower::Tower(Math::vec2 position, int direction) : GameObject(position, 0, { 0.5, 0.5 }), direction(direction),
single_tower("assets/towers/single_tower.spt", (this)),//add parts
double_tower("assets/towers/double_tower.spt", (this)),//add parts
triple_tower("assets/towers/triple_tower.spt", (this)),//add parts
push_tower("assets/towers/push_tower.spt", (this)),//add parts
wide_tower("assets/towers/wide_tower.spt", (this))//add parts
{
	charging_color = { 0.0f, 0.0f, 1.0f };
	attack_color = { 0.0f, 0.0f, 0.0f };
	color = charging_color;

	SetPosition(position);

	//add parts
	AddGOComponent(new GAM200::Sprite("assets/towers/tower_base.spt", (this)));
	//add parts

	//add parts
	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		bullet_direction = Math::vec2(1, 0);//right

		UpdateRotation(90 * (3.14 / 180));
		four_way[1] = true;
		break;
	case 1:
		bullet_direction = Math::vec2(-1, 0);//left
		UpdateRotation(270 * (3.14 / 180));
		four_way[3] = true;
		break;
	case 2:
		bullet_direction = Math::vec2(0, 1);//front
		UpdateRotation(180 * (3.14 / 180));
		four_way[0] = true;
		break;
	case 3:
		bullet_direction = Math::vec2(0, -1);//back
		UpdateRotation(360 * (3.14 / 180));
		four_way[2] = true;
		break;

	}
	//add parts

	hp = max_hp;


	Math::vec2 mouse_position = Math::vec2(Engine::GetInput().GetMousePosition().x - 1, Engine::GetInput().GetMousePosition().y - 1);
	Math::ivec2 mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size.x), static_cast<int>(mouse_position.y / tile_size.y));
	tile_position = Math::ivec2(static_cast<int>(position.x) / tile_size.x, static_cast<int>(position.y) / tile_size.y);
	//tile_position = mouse_tile_position;
}
void Tower::Update(double dt)
{
	GameObject::Update(dt);

	//add parts
	GetGOComponent<GAM200::Sprite>()->Update(dt);
	single_tower.Update(dt);
	double_tower.Update(dt);
	triple_tower.Update(dt);
	push_tower.Update(dt);
	wide_tower.Update(dt);
	//add parts

	IsClicked();
	check_supplied();
}
void Tower::Tower_Destroy()
{
	Destroy();
	RemoveGOComponent<GAM200::RectCollision>();
}
void Tower::Draw(Math::TransformationMatrix camera_matrix) {




}

bool Tower::IsOn() const
{
	Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();
	Math::vec2 position = GetPosition();

	return mouse_position.x >= position.x && mouse_position.x <= position.x + size.x && mouse_position.y >= position.y && mouse_position.y <= position.y + size.y;
}
bool Tower::IsClicked()
{
	if (IsOn())
	{
		if (Engine::GetInput().MouseJustReleased(GAM200::Input::MouseButtons::LEFT))
		{
			Tower_Adopter::GetInstance().Set_Tower(this);
			Tower_Adopter::GetInstance().Show_Info();
			return true;
		}
	}
	return false;
}
void Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
	Engine::GetLogger().LogDebug("???");
	std::cout << "\n\n";
}
Tower* Tower::Upgrade() { return this; }
void Tower::check_supplied()
{

	Math::vec2 player_position = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetPlayer()->GetPosition();
	Math::vec2 player_size{ 160.0 / 3, 160.0 / 3 };

	Math::vec2 tower_position{ GetPosition() };
	Math::vec2 tower_size{ static_cast<double>(size.x), static_cast<double>(size.y) };

	if (player_position.x + player_size.x >= tower_position.x &&
		player_position.x <= tower_position.x + tower_size.x &&

		player_position.y + player_size.y >= tower_position.y &&
		player_position.y <= tower_position.y + tower_size.y
		)
	{
		supply_ammo();
	}
}

// Constructors
Basic_Tower::Basic_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) * 2 };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x) * 2, (range_y * size.y - static_cast<int>(size.y * offset)) * 2 };
	hp = max_hp;
	ammo = max_ammo;

	// RIGHT, LEFT, UP, DOWN
	//AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{60, 160}, Math::ivec2{100, -320} }, this));

	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 0}, Math::ivec2{90, -480} }, this));
		break;
	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 160}, Math::ivec2{-70, -320} }, this));
		break;
	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 0}, Math::ivec2{-70, -480} }, this));
		break;
	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 160}, Math::ivec2{90, -320} }, this));
		break;
	}
	//AddGOComponent(new GAM200::RectCollision(Math::irect{ point1, point2 }, this));
	/*switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ point1, point2 }, this));
		break;

	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.x - (range_x - 1) * size.x, point1.y - (range_y - 1) * size.y}, Math::ivec2{point2.x - (range_x - 1) * size.x, point2.y - (range_y - 1) * size.y} }, this));
		break;

	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.y , point1.x}, Math::ivec2{point2.y, point2.x} }, this));
		break;

	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.y - (range_y - 1) * size.x , point1.x - (range_x - 1) * size.y}, Math::ivec2{point2.y - (range_y - 1) * size.x, point2.x - size.y - (range_x - 1) * size.y} }, this));
		break;
	}*/



	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Double_Tower::Double_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x), range_y * size.y - static_cast<int>(size.y * offset) };
	hp = max_hp;
	ammo = max_ammo;

	// RIGHT, LEFT, UP, DOWN

	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 0}, Math::ivec2{90, -480} }, this));
		break;
	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 160}, Math::ivec2{-70, -320} }, this));
		break;
	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 0}, Math::ivec2{-70, -480} }, this));
		break;
	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 160}, Math::ivec2{90, -320} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Triple_Tower::Triple_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x), range_y * size.y - static_cast<int>(size.y * offset) };
	hp = max_hp;
	ammo = max_ammo;

	// RIGHT, LEFT, UP, DOWN

	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 0}, Math::ivec2{90, -480} }, this));
		break;
	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 160}, Math::ivec2{-70, -320} }, this));
		break;
	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 0}, Math::ivec2{-70, -480} }, this));
		break;
	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 160}, Math::ivec2{90, -320} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Push_Tower::Push_Tower(Math::vec2 position, int direction) : Tower(position, direction)
{
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x), range_y * size.y - static_cast<int>(size.y * offset) };
	hp = max_hp;
	ammo = max_ammo;
	real_attack_delay = attack_delay;
	// RIGHT, LEFT, UP, DOWN

	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 0}, Math::ivec2{90, -320} }, this));
		break;
	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 160}, Math::ivec2{-70, -160} }, this));
		break;
	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 0}, Math::ivec2{-70, -320} }, this));
		break;
	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 160}, Math::ivec2{90, -160} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Wide_Tower::Wide_Tower(Math::vec2 position, int direction) : Tower(position, direction)
{
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x), range_y * size.y - static_cast<int>(size.y * offset) };
	hp = max_hp;
	ammo = max_ammo;
	real_attack_delay = attack_delay;
	// RIGHT, LEFT, UP, DOWN

	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 0}, Math::ivec2{90, -320} }, this));
		break;
	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 160}, Math::ivec2{-70, -160} }, this));
		break;
	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-90, 0}, Math::ivec2{-70, -320} }, this));
		break;
	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{70, 160}, Math::ivec2{90, -160} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Auto_Tower::Auto_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	double offset = 1.0 / 2 - attack_range / 2;

	Math::ivec2 point1{ 0, static_cast<int>(range_y * offset * size.y) };
	Math::ivec2 point2{ static_cast<int>(range_x * size.x), range_y * size.y - static_cast<int>(size.y * offset) };
	hp = max_hp;
	ammo = max_ammo;

	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ point1, point2 }, this));
		break;

	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.x - (range_x - 1) * size.x, point1.y - (range_y - 1) * size.y}, Math::ivec2{point2.x - (range_x - 1) * size.x, point2.y - (range_y - 1) * size.y} }, this));
		break;

	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.y , point1.x}, Math::ivec2{point2.y, point2.x} }, this));
		break;

	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{point1.y - (range_y - 1) * size.x , point1.x - (range_x - 1) * size.y}, Math::ivec2{point2.y - (range_y - 1) * size.x, point2.x - size.y - (range_x - 1) * size.y} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}


// Collision functions

bool Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		)
	{
		attack_ready = false;
		change_state(&this->state_attacking);
	}
}

bool Basic_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Basic_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	//add parts

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		&& is_fired == false
		)
	{
		attack_ready = false;
		is_fired = true;
		change_state(&this->state_attacking);
		single_tower.PlayAnimation(static_cast<int>(tower_state::Fire));
	}
	else {
		if (is_fired == true)
		{
			change_state(&this->state_charging);

			is_fired = false;
			single_tower.PlayAnimation(static_cast<int>(tower_state::None));
		}
	}

	//add parts


}


//add parts
void Basic_Tower::Draw(Math::TransformationMatrix camera_matrix)
{
	if (four_way[0] == true)//front
	{
		single_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
		//c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)//right//
	{
		//c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		single_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(0)));
	}
	else if (four_way[2] == true)//back//
	{
		//c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		single_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
	}
	else if (four_way[3] == true)
	{
		single_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
		//c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
}
//add parts


bool Double_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Double_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	//add parts
	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		&& is_fired == false
		)
	{
		//attack_ready = false;
		is_fired = true;
		change_state(&this->state_attacking);
		double_tower.PlayAnimation(static_cast<int>(tower_state::Fire));
	}
	else {
		if (is_fired == true)
		{
			is_fired = false;

			double_tower.PlayAnimation(static_cast<int>(tower_state::None));
		}
	}
	//add parts

}


//add parts
void Double_Tower::Draw(Math::TransformationMatrix camera_matrix)
{
	if (four_way[0] == true)//front
	{
		double_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
		//c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)//right//
	{
		//c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		double_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(0)));
	}
	else if (four_way[2] == true)//back//
	{
		//c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		double_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
	}
	else if (four_way[3] == true)
	{
		double_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
		//c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
}
//add parts


bool Triple_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Triple_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	//add parts
	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		)
	{
		attack_ready = false;
		change_state(&this->state_attacking);
		triple_tower.PlayAnimation(static_cast<int>(tower_state::Fire));
	}
	else
	{
		triple_tower.PlayAnimation(static_cast<int>(tower_state::None));
	}
	//add parts


}


//add parts
void Triple_Tower::Draw(Math::TransformationMatrix camera_matrix)
{
	if (four_way[0] == true)//front
	{
		triple_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
		//c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)//right//
	{
		//c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		triple_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(0)));
	}
	else if (four_way[2] == true)//back//
	{
		//c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		triple_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
	}
	else if (four_way[3] == true)
	{
		triple_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
		//c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
}
//add parts


bool Push_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Push_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	//add parts
	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		)
	{
		attack_ready = false;
		change_state(&this->state_attacking);
		push_tower.PlayAnimation(static_cast<int>(tower_state::Fire));
	}
	else
	{
		push_tower.PlayAnimation(static_cast<int>(tower_state::None));
	}
	//add parts


}


//add parts
void Push_Tower::Draw(Math::TransformationMatrix camera_matrix)
{
	if (four_way[0] == true)//front
	{
		push_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
		//c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)//right//
	{
		//c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		push_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(0)));
	}
	else if (four_way[2] == true)//back//
	{
		//c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		push_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
	}
	else if (four_way[3] == true)
	{
		push_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
		//c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
}
//add parts


bool Wide_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Wide_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	//add parts
	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		)
	{
		attack_ready = false;
		change_state(&this->state_attacking);
		push_tower.PlayAnimation(static_cast<int>(tower_state::Fire));
	}
	else
	{
		wide_tower.PlayAnimation(static_cast<int>(tower_state::None));
	}
	//add parts
}


//add parts
void Wide_Tower::Draw(Math::TransformationMatrix camera_matrix)
{
	if (four_way[0] == true)//front
	{
		wide_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
		//c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)//right//
	{
		//c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		wide_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(0)));
	}
	else if (four_way[2] == true)//back//
	{
		//c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
		wide_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
	}
	else if (four_way[3] == true)
	{
		wide_tower.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)));
		//c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
}
//add parts


bool Auto_Tower::CanCollideWith(GameObjectTypes type)
{
	if ((static_cast<int>(type) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(type) <= static_cast<int>(GameObjectTypes::Monster_End))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Auto_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	if (other_object->Type() == GameObjectTypes::Stealth_Monster)
	{
		Stealth_Monster* temp = static_cast<Stealth_Monster*>(other_object);
		if (temp->IsStealth())
			return;
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)
		)
	{
		attack_ready = false;
		change_state(&this->state_attacking);
	}
}

// Tower Upgrade
Tower* Basic_Tower::Upgrade()
{
	Math::ivec2 tile_position = this->GetTilePosition();

	if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() > Basic_Tower::GetUpgradeCost())
	{
		Map::GetInstance().DeleteTower(tile_position);

		Map::GetInstance().BuildTower(tile_position, GameObjectTypes::Double_Tower, direction);
	}
	return Map::GetInstance().GetTower(tile_position);
}
Tower* Double_Tower::Upgrade()
{
	Math::ivec2 tile_position = this->GetTilePosition();

	if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() > Double_Tower::GetUpgradeCost())
	{
		Map::GetInstance().DeleteTower(tile_position);

		Map::GetInstance().BuildTower(tile_position, GameObjectTypes::Triple_Tower, direction);
	}
	return Map::GetInstance().GetTower(tile_position);
}
Tower* Triple_Tower::Upgrade()
{
	Engine::GetLogger().LogDebug("You cannot upgrade more!");
	return this;
}
Tower* Push_Tower::Upgrade()
{
	if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() > Push_Tower::GetUpgradeCost())
	{
		Engine::GetLogger().LogDebug("Upgrade count: " + std::to_string(upgrade_count));
		switch (upgrade_count)
		{
		case 0:
			Engine::GetGameStateManager().GetGSComponent<Gold>()->Subtract(Push_Tower::GetUpgradeCost());
			real_attack_delay -= 0.75;
			++upgrade_count;
			break;

		case 1:
			Engine::GetGameStateManager().GetGSComponent<Gold>()->Subtract(Push_Tower::GetUpgradeCost());
			real_attack_delay -= 0.75;
			++upgrade_count;
			break;

		default:

			break;
		}
	}
	return this;
}
Tower* Wide_Tower::Upgrade()
{
	if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() > Wide_Tower::GetUpgradeCost())
	{
		Engine::GetLogger().LogDebug("Upgrade count: " + std::to_string(upgrade_count));
		switch (upgrade_count)
		{
		case 0:
			Engine::GetGameStateManager().GetGSComponent<Gold>()->Subtract(Wide_Tower::GetUpgradeCost());
			real_attack_delay -= 0.75;
			++upgrade_count;
			break;

		case 1:
			Engine::GetGameStateManager().GetGSComponent<Gold>()->Subtract(Wide_Tower::GetUpgradeCost());
			real_attack_delay -= 0.75;
			++upgrade_count;
			break;

		default:

			break;
		}
	}
	return this;
}
Tower* Auto_Tower::Upgrade()
{

	return this;
}


// Show Info
void Basic_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}
void Double_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}
void Triple_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}
void Push_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(real_attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}
void Wide_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(real_attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}
void Auto_Tower::ShowInfo()
{
	std::cout << "\n\n";
	Engine::GetLogger().LogDebug("Type: " + TypeName());
	Engine::GetLogger().LogDebug("HP: \t\t" + std::to_string(hp) + " / " + std::to_string(max_hp));
	Engine::GetLogger().LogDebug("attack_delay: \t" + std::to_string(real_attack_delay));
	Engine::GetLogger().LogDebug("Tile Pos: \t" + std::to_string(tile_position.x) + ", " + std::to_string(tile_position.y));
	Engine::GetLogger().LogDebug("Ammo: \t\t" + std::to_string(ammo) + " / " + std::to_string(max_ammo));
}



// State functions charging
void Tower::State_Charging::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Tower::State_Charging::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	// Increment the attack count based on the dt
	tower->attack_count += dt;

	// Attack and change state to state_attacking
	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Tower::State_Charging::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);

}

// State functions for attacking
void Tower::State_Attacking::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Tower::State_Attacking::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size.x / 2, tower->GetPosition().y + tower->size.y / 2 });

	// Create a new bullet at the tower position with specified direction
	new Basic_Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);

	// Change state to state_charging
	tower->change_state(&tower->state_charging);
}
void Tower::State_Attacking::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);

}




// State functions for charging of Basic_Tower
void Basic_Tower::State_Charging::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Basic_Tower::State_Charging::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Basic_Tower::State_Charging::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}

// State functions for Attacking of Basic_Tower
void Basic_Tower::State_Attacking::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Basic_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size.x / 2, tower->GetPosition().y + tower->size.y / 2 });
	--tower->ammo;
	new Basic_Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);
	tower->change_state(&tower->state_charging);
}
void Basic_Tower::State_Attacking::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}




// State functions for charging of Double_Tower
void Double_Tower::State_Charging::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Double_Tower::State_Charging::Update(GameObject* object, double dt) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Double_Tower::State_Charging::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}

// State functions for Attacking of Double_Tower
void Double_Tower::State_Attacking::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Double_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size.x / 2, tower->GetPosition().y + tower->size.y / 2 });
	Math::vec2 point1 = Math::vec2(tower_position.x, tower_position.y);
	Math::vec2 point2 = Math::vec2(tower_position.x, tower_position.y);
	Math::vec2 offset(tower->size.x * 0.1, tower->size.y * 0.1);
	// RIGHT, LEFT, UP, DOWN
	switch (tower->direction)
	{
	case 0:
		point1 += Math::vec2(0, offset.y);
		point2 += Math::vec2(0, -offset.y);
		break;
	case 1:
		point1 += Math::vec2(0, offset.y);
		point2 += Math::vec2(0, -offset.y);
		break;
	case 2:
		point1 += Math::vec2(offset.x, 0);
		point2 += Math::vec2(-offset.x, 0);
		break;
	case 3:
		point1 += Math::vec2(offset.x, 0);
		point2 += Math::vec2(-offset.x, 0);
		break;
	}

	--tower->ammo;
	new Basic_Bullet(point1, tower->bullet_direction * Bullet::DefaultVelocity);
	new Basic_Bullet(point2, tower->bullet_direction * Bullet::DefaultVelocity);

	tower->change_state(&tower->state_charging);
}
void Double_Tower::State_Attacking::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}




// State functions for charging of Triple_Tower
void Triple_Tower::State_Charging::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
}
void Triple_Tower::State_Charging::Update(GameObject* object, double dt) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Triple_Tower::State_Charging::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}

// State functions for Attacking of Triple_Tower
void Triple_Tower::State_Attacking::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_count = 0;
}
void Triple_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size.x / 2, tower->GetPosition().y + tower->size.y / 2 });

	Math::vec2 offset(tower->size.x * 0.1, tower->size.y * 0.1);

	Math::vec2 bullet_direction_left;
	Math::vec2 bullet_direction_right;
	Math::vec2 bullet_direction_middle = tower->bullet_direction;

	// RIGHT, LEFT, UP, DOWN
	switch (tower->direction)
	{
	case 0:
		bullet_direction_left = Math::vec2(tower->size.x, offset.y);
		bullet_direction_right = Math::vec2(tower->size.x, -offset.y);
		break;
	case 1:
		bullet_direction_left = Math::vec2(-tower->size.x, offset.y);
		bullet_direction_right = Math::vec2(-tower->size.x, -offset.y);
		break;
	case 2:
		bullet_direction_left = Math::vec2(offset.x, tower->size.y);
		bullet_direction_right = Math::vec2(-offset.x, tower->size.y);
		break;
	case 3:
		bullet_direction_left = Math::vec2(offset.x, -tower->size.y);
		bullet_direction_right = Math::vec2(-offset.x, -tower->size.y);
		break;
	}

	bullet_direction_left.Normalize();
	bullet_direction_right.Normalize();

	--tower->ammo;
	new Basic_Bullet(tower_position, bullet_direction_left * Bullet::DefaultVelocity);
	new Basic_Bullet(tower_position, bullet_direction_middle * Bullet::DefaultVelocity);
	new Basic_Bullet(tower_position, bullet_direction_right * Bullet::DefaultVelocity);

	tower->change_state(&tower->state_charging);
}
void Triple_Tower::State_Attacking::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}




// State functions for charging of Push_Tower
void Push_Tower::State_Charging::Enter(GameObject* object) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
}
void Push_Tower::State_Charging::Update(GameObject* object, double dt) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Push_Tower::State_Charging::CheckExit(GameObject* object) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);

}

// State functions for Attacking of Push_Tower
void Push_Tower::State_Attacking::Enter(GameObject* object) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_count = 0;
}
void Push_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x , tower->GetPosition().y });

	Math::vec2 offset(tower->size.x * 0.1, tower->size.y * 0.1);

	Math::vec2 bullet_direction = tower->bullet_direction;

	--tower->ammo;
	new Pushing_Bullet(tower_position, bullet_direction * Pushing_Bullet::DefaultVelocity);

	tower->change_state(&tower->state_charging);
}
void Push_Tower::State_Attacking::CheckExit(GameObject* object) {
	Push_Tower* tower = static_cast<Push_Tower*>(object);

}




// State functions for charging of Wide_Tower
void Wide_Tower::State_Charging::Enter(GameObject* object) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
}
void Wide_Tower::State_Charging::Update(GameObject* object, double dt) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Wide_Tower::State_Charging::CheckExit(GameObject* object) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);

}

// State functions for Attacking of Wide_Tower
void Wide_Tower::State_Attacking::Enter(GameObject* object) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_count = 0;
}
void Wide_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x , tower->GetPosition().y });

	Math::vec2 offset(tower->size.x * 0.1, tower->size.y * 0.1);

	Math::vec2 bullet_direction = tower->bullet_direction;

	--tower->ammo;
	// RIGHT, LEFT, UP, DOWN
	switch (tower->direction)
	{
	case 0:
		new Wide_Range_Bullet(Math::vec2{ tower_position.x + tower->size.x, tower_position.y - tower->size.y }, bullet_direction * Wide_Range_Bullet::DefaultVelocity);
		break;
	case 1:
		new Wide_Range_Bullet(Math::vec2{ tower_position.x - tower->size.x, tower_position.y - tower->size.y }, bullet_direction * Wide_Range_Bullet::DefaultVelocity);
		break;
	case 2:
		new Wide_Range_Bullet(Math::vec2{ tower_position.x - tower->size.x, tower_position.y + tower->size.y }, bullet_direction * Wide_Range_Bullet::DefaultVelocity);
		break;
	case 3:
		new Wide_Range_Bullet(Math::vec2{ tower_position.x - tower->size.x, tower_position.y - tower->size.y }, bullet_direction * Wide_Range_Bullet::DefaultVelocity);
		break;
	}
	//new Wide_Range_Bullet(tower_position, bullet_direction * Wide_Range_Bullet::DefaultVelocity);
	//new Basic_Bullet(tower_position, bullet_direction * Pushing_Bullet::DefaultVelocity);
	tower->change_state(&tower->state_charging);
}
void Wide_Tower::State_Attacking::CheckExit(GameObject* object) {
	Wide_Tower* tower = static_cast<Wide_Tower*>(object);

}




// State functions for charging of Triple_Tower
void Auto_Tower::State_Charging::Enter(GameObject* object) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
}
void Auto_Tower::State_Charging::Update(GameObject* object, double dt) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);

	tower->attack_count += dt;

	if ((tower->attack_count >= tower->attack_delay) && tower->ammo > 0) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Auto_Tower::State_Charging::CheckExit(GameObject* object) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);

}

// State functions for Attacking of Triple_Tower
void Auto_Tower::State_Attacking::Enter(GameObject* object) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_count = 0;
}
void Auto_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size.x / 2, tower->GetPosition().y + tower->size.y / 2 });

	Math::vec2 offset(tower->size.x * 0.1, tower->size.y * 0.1);

	Monster* closest_monster = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestMonster(tower);
	if (closest_monster != nullptr)
	{
		Math::vec2 monster_pos = closest_monster->GetPosition();
		Math::vec2 tower_pos = tower->GetPosition();

		Math::vec2 dir = Math::vec2({ monster_pos.x - tower_pos.x, monster_pos.y - tower_pos.y });;
		dir /= dir.GetLength();

		--tower->ammo;
		new Bullet(tower_pos, dir * Bullet::DefaultVelocity);
	}

	tower->change_state(&tower->state_charging);
}
void Auto_Tower::State_Attacking::CheckExit(GameObject* object) {
	Auto_Tower* tower = static_cast<Auto_Tower*>(object);

}






bool Tower::enable_supply = false;

int Tower::cost = 0;
double Tower::attack_delay = 0.0;
int Tower::max_hp = 0;
int Tower::max_ammo = 0;

int Basic_Tower::cost = 0;
int Basic_Tower::upgrade_cost = 0;
double Basic_Tower::attack_delay = 0.0;
int Basic_Tower::max_hp = 0;
int Basic_Tower::range_x = 0;
int Basic_Tower::range_y = 0;
double Basic_Tower::attack_range = 0;
int Basic_Tower::max_ammo = 0;


int Double_Tower::cost = 0;
int Double_Tower::upgrade_cost = 0;
double Double_Tower::attack_delay = 0.0;
int Double_Tower::max_hp = 0;
int Double_Tower::range_x = 0;
int Double_Tower::range_y = 0;
double Double_Tower::attack_range = 0;
int Double_Tower::max_ammo = 0;

int Triple_Tower::cost = 0;
int Triple_Tower::upgrade_cost = 0;
double Triple_Tower::attack_delay = 0.0;
int Triple_Tower::max_hp = 0;
int Triple_Tower::range_x = 0;
int Triple_Tower::range_y = 0;
double Triple_Tower::attack_range = 0;
int Triple_Tower::max_ammo = 0;

int Push_Tower::cost = 0;
int Push_Tower::upgrade_cost = 0;
double Push_Tower::attack_delay = 0.0;
int Push_Tower::max_hp = 0;
int Push_Tower::range_x = 0;
int Push_Tower::range_y = 0;
double Push_Tower::attack_range = 0;
int Push_Tower::max_ammo = 0;

int Wide_Tower::cost = 0;
int Wide_Tower::upgrade_cost = 0;
double Wide_Tower::attack_delay = 0.0;
int Wide_Tower::max_hp = 0;
int Wide_Tower::range_x = 0;
int Wide_Tower::range_y = 0;
double Wide_Tower::attack_range = 0;
int Wide_Tower::max_ammo = 0;

int Auto_Tower::cost = 0;
int Auto_Tower::upgrade_cost = 0;
double Auto_Tower::attack_delay = 0.0;
int Auto_Tower::max_hp = 0;
int Auto_Tower::range_x = 0;
int Auto_Tower::range_y = 0;
double Auto_Tower::attack_range = 0;
int Auto_Tower::max_ammo = 0;


// File parsing from the txt file
void TowerFactory::InitBasicTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Basic_Tower::cost;

		file >> Basic_Tower::upgrade_cost;

		file >> Basic_Tower::attack_delay;

		file >> Basic_Tower::max_hp;

		file >> Basic_Tower::range_x;

		file >> Basic_Tower::range_y;

		file >> Basic_Tower::attack_range;

		file >> Basic_Tower::max_ammo;
	}

}
void TowerFactory::InitDoubleTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Double_Tower::cost;

		file >> Double_Tower::upgrade_cost;

		file >> Double_Tower::attack_delay;

		file >> Double_Tower::max_hp;

		file >> Double_Tower::range_x;

		file >> Double_Tower::range_y;

		file >> Double_Tower::attack_range;

		file >> Double_Tower::max_ammo;
	}

}
void TowerFactory::InitTripleTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Triple_Tower::cost;

		file >> Triple_Tower::upgrade_cost;

		file >> Triple_Tower::attack_delay;

		file >> Triple_Tower::max_hp;

		file >> Triple_Tower::range_x;

		file >> Triple_Tower::range_y;

		file >> Triple_Tower::attack_range;

		file >> Triple_Tower::max_ammo;
	}

}
void TowerFactory::InitPushTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Push_Tower::cost;

		file >> Push_Tower::upgrade_cost;

		file >> Push_Tower::attack_delay;

		file >> Push_Tower::max_hp;

		file >> Push_Tower::range_x;

		file >> Push_Tower::range_y;

		file >> Push_Tower::attack_range;

		file >> Push_Tower::max_ammo;
	}

}
void TowerFactory::InitWideTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Wide_Tower::cost;

		file >> Wide_Tower::upgrade_cost;

		file >> Wide_Tower::attack_delay;

		file >> Wide_Tower::max_hp;

		file >> Wide_Tower::range_x;

		file >> Wide_Tower::range_y;

		file >> Wide_Tower::attack_range;

		file >> Wide_Tower::max_ammo;
	}

}
void TowerFactory::InitAutoTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Auto_Tower::cost;

		file >> Auto_Tower::upgrade_cost;

		file >> Auto_Tower::attack_delay;

		file >> Auto_Tower::max_hp;

		file >> Auto_Tower::range_x;

		file >> Auto_Tower::range_y;

		file >> Auto_Tower::attack_range;

		file >> Auto_Tower::max_ammo;
	}

}








void Tower_Adopter::Set_Tower(Tower* tower)
{
	GAM200::SoundEffect::Tower_Placing().play();

	current_tower = tower;
}
void Tower_Adopter::Show_Info()
{
	if (current_tower == nullptr)
	{
		Engine::GetLogger().LogDebug("nullptr!");
		return;
	}

	current_tower->ShowInfo();
}
void Tower_Adopter::Upgrade()
{
	if (current_tower == nullptr)
	{
		Engine::GetLogger().LogDebug("nullptr!");
		return;
	}

	GAM200::SoundEffect::Tower_Upgrade().play();

	current_tower = current_tower->Upgrade();
}
void Tower_Adopter::Delete()
{


	if (current_tower == nullptr)
		return;

	GAM200::SoundEffect::Tower_Delete().play();


	Map::GetInstance().DeleteTower(current_tower->GetTilePosition());
	current_tower = nullptr;
}