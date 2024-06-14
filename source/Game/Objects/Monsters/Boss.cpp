#include "Boss.h"
#include "Engine/GameObjectManager.h"

void Boss::State_None::Enter(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
}
void Boss::State_None::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);

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

    if (boss->info.life <= 0)
    {
        boss->change_state(&boss->state_dead);
        Engine::GetAudioManager().PlaySound(GAM200::AudioID::Monster_Die_2);
    }
}
void Boss::State_Summon::Enter(GameObject* object)
{
    Boss* boss        = static_cast<Boss*>(object);
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));

    boss->summon_time_count = 0;
    boss->summon_num_count  = 0;
}
void Boss::State_Summon::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->summon_time_count += dt;

    if (boss->summon_time_count >= boss->summon_time)
    {
        new Monster_10(boss->GetPosition(), boss->GetVelocity());
        
        boss->summon_time_count = 0;
        ++boss->summon_num_count;
    }
}
void Boss::State_Summon::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    if (boss->summon_num_count >= boss->summon_num)
    {
        boss->change_state(&boss->state_none);
    }
}
void Boss::State_Stun::Enter(GameObject* object)
{
    Boss* boss        = static_cast<Boss*>(object);
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::none));
    boss->stun_count = 0;
}
void Boss::State_Stun::Update(GameObject* object, double dt)
{
    Boss* boss = static_cast<Boss*>(object);
    boss->stun_count += dt;
}
void Boss::State_Stun::CheckExit(GameObject* object)
{
    Boss* boss = static_cast<Boss*>(object);

    if (boss->stun_count >= boss->stun_time)
    {
        Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->StunUnits(boss->GetPosition(), boss->stun_range);

        boss->change_state(&boss->state_none);
    }
}
void Boss::State_Dead::Enter(GameObject* object)
{
    Boss* boss     = static_cast<Boss*>(object);
    boss->death_count = boss->death_time;
    boss->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(anm::dead));
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