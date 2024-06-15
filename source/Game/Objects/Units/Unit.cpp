


#include "Unit.h"

#include<string>

#include "Engine/GameObjectManager.h"
#include "Engine/DrawShape.h"

#include "Engine/MergeCollision.h"
#include "Engine/Collision.h"

#include "Component/Time.h"

Unit::Unit(double attack_time, int damage, double range, Math::vec2 position) : attack_time(attack_time), damage(damage), GameObject(position), range(range)
{
    AddGOComponent(new GAM200::MergeCircleCollision(radius, this));
    AddGOComponent(new GAM200::CircleCollision(range, this));

    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);

#if !IfWantShader
    dmg.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Damage: " + std::to_string(damage), 0xFFFFFFFF));
    attackSpd.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Atk Spd: " + std::to_string(attack_time), 0xFFFFFFFF));
    dps.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("DPS: " + std::to_string(GetDPS()), 0xFFFFFFFF));
#endif
}

Unit::~Unit()
{
    RemoveGOComponent<GAM200::MergeCircleCollision>();
    RemoveGOComponent<GAM200::CircleCollision>();
    RemoveGOComponent<GAM200::Sprite>();

    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->ResetCurrentUnit();
    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->ResetInfoTarget();
}

void Unit::Update(double dt)
{
    ResetBuff();
    GameObject::Update(dt);
    GetGOComponent<GAM200::Sprite>()->Update(dt);
    attack_animation_count -= dt;

    HandleMouseInput();
}

void Unit::Draw(Math::TransformationMatrix camera_matrix)
{
#if !IfWantShader
#if !defined(__EMSCRIPTEN__)

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
#endif
#else
    Math::vec2 position = GetPosition();

 
    if (is_moving)
	{
        ShaderDrawing::set_color(249, 40, 145, 76);
        ShaderDrawing::draw_circle(static_cast<int>(previous_position.x), static_cast<int>(previous_position.y), static_cast<int>(radius), static_cast<int>(radius));

        ShaderDrawing::set_color(25, 25, 25, 153);
        ShaderDrawing::draw_circle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(range), static_cast<int>(range));
    }
#endif
}

void Unit::DrawMergeList()
{
    float initial_x_value = 200;
    float initial_y_value = 600;

    for (const auto& pair : merge_list)
    {
        GameObjectTypes target = pair.first;
        GameObjectTypes result = pair.second;

        std::string string = TypeName() + " + " + toString(target) + " = " + toString(result);

        ShaderDrawing::draw_text(string, initial_x_value, initial_y_value, 20, 0.0, 0.0, 0.0);
        //Engine::GetLogger().LogDebug(TypeName() + " + " + toString(target) + " = " + toString(result));
        initial_y_value -= 30;
    }
}

void Unit::ShowInfo()
{
#if !IfWantShader
    name->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 350 }));

    dmg->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 280 }));

    attackSpd->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 210 }));

    dps->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 140 }));
#else
    ShaderDrawing::draw_text(TypeName(), 1100, 340, 40, 255, 255, 255);
    std::ostringstream stream1;
    stream1 << std::fixed << std::setprecision(2) << GetDamage();
    std::string result1 = stream1.str();
    ShaderDrawing::draw_text("Damage: " + result1, 1100, 280, 40, 255, 255, 255);
    std::ostringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << GetAtkSpd();
    std::string result2 = stream2.str();
    ShaderDrawing::draw_text("Atk Spd: " + result2, 1100, 210, 40, 255, 255, 255);
    std::ostringstream stream3;
    stream3 << std::fixed << std::setprecision(2) << GetDPS();
    std::string result3 = stream3.str();
    ShaderDrawing::draw_text("DPS: " + result3, 1100, 140, 40, 255, 255, 255);
#endif
}

void Unit::HandleMouseInput()
{
    Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();

    // Mouse is not being clicked
    if (!Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::LEFT))
    {
        if (Engine::GetInput().MouseDown(GAM200::Input::MouseButtons::RIGHT))
        {
            if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestUnit(mouse_position) == this)
            {
                Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->SetInfoTarget(this);
            }
        }


        if (is_moving) // Drop
        {
            if (is_colliding)
            {
                SetPosition(previous_position);
            }
        }
        not_clicked = true;
        is_moving = false;
        return;
    }

    // Clicked moment
    if (not_clicked && Engine::GetInput().MouseJustPressed(GAM200::Input::MouseButtons::LEFT) && (IsMouseOverUnit()))
    {
        if (Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestUnit(mouse_position) != this)
            return;

        is_moving = true;
        previous_position = GetPosition();
        position_gap = mouse_position - previous_position;
        drop = false;
        not_clicked = false;
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

#if !IfWantShader
    dps.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("DPS: " + std::to_string(GetDPS()), 0xFFFFFFFF));
#else
    ShaderDrawing::draw_text("DPS: " + std::to_string(GetDPS()), 1100, 140, 50, 255, 255, 255);
#endif
}


double Unit::GetDPS()
{
    if (damageHolder.size() == 0)
        return 0;

    double totalDamage = 0;

    std::queue<std::pair<double, double>>temp = damageHolder;

    while(!temp.empty())
    {
        totalDamage += temp.front().second;
        temp.pop();
    }

    return totalDamage / 10.0;
}

void Unit::InsertDPS(double damage)
{
    double currentTime = Engine::GetGameStateManager().GetGSComponent<Time>()->CurrentTime();

    damageHolder.push(std::make_pair(currentTime, damage));

    UpdateDPS();
}

void Unit::BuffDmg(double dmg)
{
    damage_buff *= dmg;
}

void Unit::BuffAtkspd(double atkspd)
{
    atkspd_buff *= atkspd;
}

void Unit::ResetBuff()
{
    damage_buff = 1.0;
    atkspd_buff = 1.0;
}