
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
    // Wave info, get from the Map
    std::vector<std::vector<std::tuple<int, std::string, int>>> wave_info;

    // Wave state ( NotInProgress or InProgress )
    bool wave_state;
    bool wave_of_wave_ended;

    // Current Time
    double current_time;
    
    // Total wave of map, current wave count
    int total_wave_num = 0;
    int current_wave = -1;
    
    // The number of waves in the current wave, current wave of the current wave
    int total_wave_of_wave = 0;
    int current_wave_of_wave = 0;
    
    // Wave time, the number of monsters in the wave
    double wave_time = 0;
    int monster_num = 0;
    
    // Monsters are produced every (time_offset), count for it
    double time_offset = 0;
    double monster_produce_time_count = 0;
    
    // Name of monster
    std::string monster_name;
};