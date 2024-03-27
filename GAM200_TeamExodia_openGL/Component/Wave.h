#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Wave : public GAM200::Component
{
public:
	Wave() : wave_state(Rest) { }
	
	enum WaveState
	{
		Battle,
		Rest,
		End,
	} wave_state;

	WaveState GetState() const { return wave_state; }

	void SetWave(std::string file_name);
	int GetMaxWave() const { return total_wave; }
	int GetCurWave() const { return current_wave; }
	int GetCurTime() const { return static_cast<int>(current_time); }
	int GetRestTime() const { return static_cast<int>(rest_time); }
	bool IsResting() const { return wave_state == Rest ? true : false; }
	void Skip();
	void Update(double dt) override;


private:
	// Wave info
	std::vector<std::tuple<double, double, std::string, int>> wave_info;

	// Other stuffs
	bool wave_ended = true;

	int total_wave = 0;
	int current_wave = -1;


	// For update
	std::string monster_name;
	int monster_num = 0;

	double current_time = 0.0;

	double wave_time = 20.0;
	double rest_time = 10.0;

	double monster_spawn_time_offset = 0.0;
	double monster_spawn_time_count = 0.0;
};

