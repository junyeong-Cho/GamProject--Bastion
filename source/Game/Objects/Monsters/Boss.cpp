#include "Boss.h"
#include "Engine/GameObjectManager.h"

void Boss::Draw(Math::TransformationMatrix camera_matrix)
{
    Math::vec2 position = GetPosition();

    Monster::Draw(camera_matrix);


    if (stun_count >= stun_pattern_cool_time - stun_pattern_delay)
    {
        Engine::GetLogger().LogDebug("Drawing Stun Range: " + std::to_string(stun_pattern_cool_time - stun_count));
        double stun_scale_gap = stun_pattern_cool_time - stun_count + 1.0;
        double stun_scale     = 1.0 / stun_scale_gap * 0.7;
        ShaderDrawing::push();
        ShaderDrawing::set_color(255 * stun_scale, 0, 0, 255 * stun_scale);
        ShaderDrawing::draw_circle(GetPosition().x, GetPosition().y, stun_range * stun_scale, stun_range * stun_scale);
        ShaderDrawing::pop();
    }
}

void Boss::State_None::Enter(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    Engine::GetLogger().LogDebug("Boss None Enter");
}
void Boss::State_None::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->pattern_time_count += dt;

    if (boss->IsInside(Map::outer_lower_left))
    {
        boss->SetVelocity({ speed * boss->info.speed_scale, 0 });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_lower_right))
    {
        boss->SetVelocity({ 0, speed * boss->info.speed_scale });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_right))
    {
        boss->SetVelocity({ -speed * boss->info.speed_scale, 0 });
        boss->SetScale({ -1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_left))
    {
        boss->SetVelocity({ 0, -speed * boss->info.speed_scale });
        boss->SetScale({ -1, 1 });
    }

    if (boss->tilt_count > 0.0)
    {
        boss->tilt_count -= dt;
        boss->tilt_amount -= boss->tilt_decrease * dt;
        boss->SetRotation(boss->tilt_amount);
    }
}
void Boss::State_None::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    if (boss->next_pattern == Summon)
    {
        if (boss->pattern_time_count >= boss->summon_pattern_cool_time)
        {
            boss->change_state(&boss->state_summon);
            boss->pattern_time_count = 0;
        }
    }
    else if (boss->next_pattern == Stun)
    {
        if (boss->pattern_time_count >= boss->stun_pattern_cool_time)
        {
            boss->change_state(&boss->state_stun);
            boss->pattern_time_count = 0;
        }
    }

    if (boss->info.life <= 0)
    {
        boss->change_state(&boss->state_dead);
        #if !defined(__EMSCRIPTEN__)
        Engine::GetAudioManager().PlaySound(GAM200::AudioID::Monster_Die_2);
        #endif
    }
}
void Boss::State_Summon::Enter(GameObject* object)
{
    Boss* boss        = static_cast<Boss*>(object);
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));

    boss->summon_time_count = 0;
    boss->summon_num_count  = 0;

    Engine::GetLogger().LogDebug("Boss Summon Enter");
}
void Boss::State_Summon::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->summon_time_count += dt;
    
    if (boss->IsInside(Map::outer_lower_left))
    {
        boss->SetVelocity({ speed * boss->info.speed_scale, 0 });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_lower_right))
    {
        boss->SetVelocity({ 0, speed * boss->info.speed_scale });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_right))
    {
        boss->SetVelocity({ -speed * boss->info.speed_scale, 0 });
        boss->SetScale({ -1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_left))
    {
        boss->SetVelocity({ 0, -speed * boss->info.speed_scale });
        boss->SetScale({ -1, 1 });
    }

    if (boss->tilt_count > 0.0)
    {
        boss->tilt_count -= dt;
        boss->tilt_amount -= boss->tilt_decrease * dt;
        boss->SetRotation(boss->tilt_amount);
    }

    if (boss->summon_time_count >= boss->summon_time / boss->summon_num)
    {
        Engine::GetLogger().LogDebug("Monster Summon!");
        Engine::GetLogger().LogDebug("Position: " + std::to_string(boss->GetPosition().x) + std::to_string(boss->GetPosition().y));
        new Monster_10(boss->GetPosition(), boss->GetVelocity());
        //new Monster_10();
        boss->summon_time_count = 0;
        ++boss->summon_num_count;
    }
}
void Boss::State_Summon::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    if (boss->summon_num_count >= boss->summon_num)
    {
        boss->next_pattern = Stun;
        
        boss->change_state(&boss->state_none);
    }
}
void Boss::State_Stun::Enter(GameObject* object)
{
    Boss* boss        = static_cast<Boss*>(object);
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    boss->stun_count = 0;
    Engine::GetLogger().LogDebug("Boss Stun Enter");
}
void Boss::State_Stun::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->stun_count += dt;

    if (boss->IsInside(Map::outer_lower_left))
    {
        boss->SetVelocity({ speed * boss->info.speed_scale, 0 });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_lower_right))
    {
        boss->SetVelocity({ 0, speed * boss->info.speed_scale });
        boss->SetScale({ 1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_right))
    {
        boss->SetVelocity({ -speed * boss->info.speed_scale, 0 });
        boss->SetScale({ -1, 1 });
    }
    else if (boss->IsInside(Map::outer_upper_left))
    {
        boss->SetVelocity({ 0, -speed * boss->info.speed_scale });
        boss->SetScale({ -1, 1 });
    }

    if (boss->tilt_count > 0.0)
    {
        boss->tilt_count -= dt;
        boss->tilt_amount -= boss->tilt_decrease * dt;
        boss->SetRotation(boss->tilt_amount);
    }
}
void Boss::State_Stun::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    if (boss->stun_count >= boss->stun_pattern_cool_time)
    {
        Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->StunUnits(boss->GetPosition(), boss->stun_range);
        boss->next_pattern = Summon;

        boss->stun_count = 0;
        boss->change_state(&boss->state_none);
    }
}
void Boss::State_Dead::Enter(GameObject* object)
{
    Boss* boss     = static_cast<Boss*>(object);
    boss->death_count = boss->death_time;
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::dead));
    Engine::GetLogger().LogDebug("Boss Dead Enter");
}
void Boss::State_Dead::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->death_count -= dt;
}
void Boss::State_Dead::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);
    if (boss->death_count <= 0.0)
    {
        boss->Destroy();
    }
}