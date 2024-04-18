


#include "Unit.h"


#include "../Engine/GameObjectManager.h"
#include "../Engine/DrawShape.h"

#include "../Engine/MergeCollision.h"
#include "../Engine/Collision.h"

#include "../Component/Time.h"

Unit::Unit(double attack_time, int damage, double range, Math::vec2 position) : attack_time(attack_time), damage(damage), GameObject(position), range(range)
{
    AddGOComponent(new GAM200::MergeCircleCollision(radius, this));
    AddGOComponent(new GAM200::CircleCollision(range, this));

    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);

    dmg.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Damage: " + std::to_string(damage), 0xFFFFFFFF));
    attackSpd.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Atk Spd: " + std::to_string(attack_time), 0xFFFFFFFF));
    dps.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("DPS: " + std::to_string(GetDPS()), 0xFFFFFFFF));
}

Unit::~Unit()
{
    RemoveGOComponent<GAM200::MergeCircleCollision>();
    RemoveGOComponent<GAM200::CircleCollision>();
}

void Unit::Update(double dt)
{
    GameObject::Update(dt);

    attack_animation_count -= dt;

    HandleMouseInput();
}

void Unit::Draw(Math::TransformationMatrix camera_matrix)
{
    GAM200::DrawShape shape;

    Math::vec2 position = GetPosition();

    // Merge range
    Engine::Instance().push();
    shape.SetColor(0.0f, 0.0f, 0.0f, 0.2f);
    shape.DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius), static_cast<int>(radius));
    Engine::Instance().pop();

    if (is_moving)
    {
        // Attack range
        Engine::Instance().push();
        shape.SetColor(0.977f, 0.157f, 0.569f, 0.3f);
        shape.DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(range), static_cast<int>(range));
        Engine::Instance().pop();

        // Previous position
        Engine::Instance().push();
        shape.SetColor(0.1f, 0.1f, 0.1f, 0.6f);
        shape.DrawCircle(static_cast<int>(previous_position.x), static_cast<int>(previous_position.y), static_cast<int>(radius), static_cast<int>(radius));
        Engine::Instance().pop();

        //ShowInfo();
    }
}

void Unit::ShowInfo()
{
    name->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 350 }));

    dmg->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 280 }));

    attackSpd->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 210 }));

    dps->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 140 }));
}

void Unit::HandleMouseInput()
{
    Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();

    // Mouse is not being clicked
    if (!Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::LEFT))
    {
        if (is_moving) // Drop
        {
            Engine::GetLogger().LogDebug("Drop!");

            /*if (!IsInMap(mouse_position))
            {
                Engine::GetLogger().LogDebug("The position is not on the map");
                SetPosition(previous_position);
            }
            else */if (is_colliding)
            {
                Engine::GetLogger().LogDebug("Can not merge!");
                SetPosition(previous_position);
            }
            else
            {
                Engine::GetLogger().LogDebug("Changed Position!");
                //SetPosition(mouse_position - position_gap);
            }
        }
        //Engine::GetLogger().LogDebug("Not clicking!");
        not_clicked = true;
        is_moving = false;
        return;
    }

    // Clicked moment
    if (not_clicked && Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT) && (IsMouseOverUnit()))
    {
        if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestUnit(mouse_position) != this)
            return;


        Engine::GetLogger().LogDebug("Clicked! Saved previous position! Started moving");
        is_moving = true;
        previous_position = GetPosition();
        position_gap = mouse_position - previous_position;
        drop = false;
        not_clicked = false;

        //Engine::GetGameStateManager().GetGSComponent<UnitInfo>()->Change(this);
    }

    if (is_moving)
    {
        Math::vec2 position = mouse_position - position_gap;

        if (!IsInMap(position))
        {
            position =  LimitInMap(position);
        }
        SetPosition(position);
    }
}


bool Unit::IsInMap(Math::vec2 position) const
{
    position -= position_gap;
    if (position.x >= Map::inner_left_end + radius &&
        position.x <= Map::inner_rigiht_end - radius &&
        position.y >= Map::inner_bottom_end + radius &&
        position.y <= Map::inner_top_end - radius
        )
        return true;
    else
        return false;
}

Math::vec2 Unit::LimitInMap(Math::vec2 position)
{
    if (position.x < Map::inner_left_end + radius)
    {
        position.x = Map::inner_left_end + radius;
    }
    else if (position.x > Map::inner_rigiht_end - radius)
    {
        position.x = Map::inner_rigiht_end - radius;
    }

    if (position.y > Map::inner_top_end - radius)
    {
        position.y = Map::inner_top_end - radius;
    }
    else if (position.y < Map::inner_bottom_end + radius)
    {
        position.y = Map::inner_bottom_end + radius;
    }

    return position;
}

bool Unit::IsMouseOverUnit() const
{
    return ((Engine::GetInput().GetMousePosition() - GetPosition()).GetSquaredLength() <= radius * radius);
}

void Unit::UpdateDPS()
{
    //std::queue<std::pair<double, int>>temp = damageHolder;


    while (!damageHolder.empty())
    {
        double currentTime = Engine::GetGameStateManager().GetGSComponent<Time>()->CurrentTime();
        if (damageHolder.front().first + 10.0 < currentTime)
        {
            damageHolder.pop();
        }
        else
        {
            break;
        }
    }

    dps.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("DPS: " + std::to_string(GetDPS()), 0xFFFFFFFF));
}


double Unit::GetDPS()
{
    if (damageHolder.size() == 0)
        return 0;

    double totalDamage = 0;

    std::queue<std::pair<double, int>>temp = damageHolder;

    while(!temp.empty())
    {
        totalDamage += temp.front().second;
        temp.pop();
    }

    return totalDamage / 10.0;
}

void Unit::InsertDPS(int damage)
{
    double currentTime = Engine::GetGameStateManager().GetGSComponent<Time>()->CurrentTime();

    damageHolder.push(std::make_pair(currentTime, damage));

    UpdateDPS();
}