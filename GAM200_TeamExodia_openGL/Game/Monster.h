#pragma once

#include "../Engine/GameObject.h"
#include "../Game/GameObjectTypes.h"

#include "../Component/Map.h"


class Monster : public GAM200::GameObject
{
public:
	struct MonsterInfo
	{
		int life;
		int physicalDefence;
		int magicDefence;

		double speed_scale;
	};


public:
	// Basic constructor (Spawn at the given position)
	Monster(MonsterInfo info);
	// Constructor with position, directoin (Spawn at the certain position, maybe boss)
	Monster(MonsterInfo info, Math::vec2 position, Math::vec2 direction);

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

	virtual void Update(double dt) override;
	virtual void Draw(Math::TransformationMatrix camera_matrix) override;

	bool IsInside(Math::vec2 target_position) const;

protected:
	MonsterInfo info;

	static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0;
	static inline double speed = Map::basic_size;

	static inline double offset = Map::basic_size;
};

class TestMonster : public Monster
{
public:
	TestMonster() : Monster({ 5, 0, 0, 3.0 }) { }
private:
};