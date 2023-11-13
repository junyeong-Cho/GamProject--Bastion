
#pragma once

#include "../Engine/GameStateManager.h"
#include <tuple>

class Wave : public GAM200::Component
{
public:
    Wave() : wave_state(Wave_State::NotInProgress), current_time(0) {}

    bool GetState() const { return wave_state; }

    void SetWave();
    int GetMaxWave() const { return total_wave_num; }
    int GetCurrentWave() const { return current_wave + 1; }
    void Start();
    void Update(double dt) override;

    enum Wave_State
    {
        NotInProgress = 0,
        InProgress = 1
    };

private:
    bool wave_state;

    double current_time;

    int total_wave_num = 0;
    int current_wave = -1;

    int total_wave_of_wave = 0;
    int current_wave_of_wave = 0;
    double wave_time = 0;
    std::string monster_name;
    int monster_num = 0;
    double time_offset = 0;
    double monster_produce_time_count = 0;

    std::vector<std::vector<std::tuple<int, std::string, int>>> wave_info;
};