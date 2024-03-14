#pragma once

#include "../Engine/GameObject.h"
#include "../Game/GameObjectTypes.h"



class Monster : public GAM200::GameObject
{
public:
	// Basic constructor (Spawn at the given position)
	Monster(int life, double speed_scale);
	// Constructor with position, directoin (Spawn at the certain position, maybe boss)
	Monster(int life, double speed_scale, Math::vec2 position, Math::vec2 direction);

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

	virtual void Update(double dt) override;
	virtual void Draw(Math::TransformationMatrix camera_matrix) override;

	bool IsInside(Math::vec2 target_position) const;

protected:
	int life;

	static inline double size = 50;

	static inline double speed = 100;
	double speed_scale;

	static inline double offset = 80;

	static inline Math::vec2 outer_lower_left { 360,   0 };
	static inline Math::vec2 outer_lower_right{ 920,   0 };
	static inline Math::vec2 outer_upper_right{ 920, 720 };
	static inline Math::vec2 outer_upper_left { 360, 720 };

	static inline Math::vec2 inner_lower_left { 440,  80 };
	static inline Math::vec2 inner_lower_right{ 840,  80 };
	static inline Math::vec2 inner_upper_right{ 840, 640 };
	static inline Math::vec2 inner_upper_left { 440, 640 };

	static inline Math::vec2 middle_lower_left { 400,  40 };
	static inline Math::vec2 middle_lower_right{ 880,  40 };
	static inline Math::vec2 middle_upper_right{ 880, 680 };
	static inline Math::vec2 middle_upper_left { 400, 680 };
};

class TestMonster : public Monster
{
public:
	TestMonster() : Monster(5, 1.0) { }

private:


};