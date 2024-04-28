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
	~Monster();


	virtual bool CanCollideWith(GameObjectTypes other_object_type)
	{
		return false;
	}

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

	virtual void Update(double dt) override;
	virtual void Draw(Math::TransformationMatrix camera_matrix) override;

	bool IsInside(Math::vec2 target_position) const;

	static int GetRemainingMonster() { return remaining_monster; }

	void TakeDamage(int damage);

protected:
	MonsterInfo info;
	GAM200::Texture* image;

	static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0;
	static inline double speed = Map::basic_size;

	static inline double offset = Map::basic_size;

private:
	static int remaining_monster;
};

class Monster_1 : public Monster
{
public:
	Monster_1() : Monster({ 5, 0, 0, 1.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_1.png"); }
private:
};

class Monster_2 : public Monster
{
public:
	Monster_2() : Monster({ 10, 0, 0, 1.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_2.png"); }
private:
};

class Monster_3 : public Monster
{
public:
	Monster_3() : Monster({ 16, 0, 0, 1.2 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_3.png"); }
private:
};

class Monster_4 : public Monster
{
public:
	Monster_4() : Monster({ 24, 0, 0, 1.4 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_4.png"); }
private:
};

class Monster_5 : public Monster
{
public:
	Monster_5() : Monster({ 30, 0, 0, 1.4 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_5.png"); }
private:
};

class Monster_6 : public Monster
{
public:
	Monster_6() : Monster({ 75, 0, 0, 1.3 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_6.png"); }
private:
};

class Monster_7 : public Monster
{
public:
	Monster_7() : Monster({ 100, 0, 0, 1.2 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_7.png"); }
private:
};

class Monster_8 : public Monster
{
public:
	Monster_8() : Monster({ 10, 0, 0, 2.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_8.png"); }
private:
};

class Monster_9 : public Monster
{
public:
	Monster_9() : Monster({ 20, 0, 0, 2.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_9.png"); }
private:
};

class Monster_10 : public Monster
{
public:
	Monster_10() : Monster({ 40, 0, 0, 2.2 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_10.png"); }
private:
};

class Monster_11 : public Monster
{
public:
	Monster_11() : Monster({ 100, 0, 0, 2.4 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_11.png"); }
private:
};

class Monster_12 : public Monster
{
public:
	Monster_12() : Monster({ 160, 0, 0, 2.4 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_12.png"); }
private:
};

class Monster_13 : public Monster
{
public:
	Monster_13() : Monster({ 200, 0, 0, 2.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_13.png"); }
private:
};

class Monster_14 : public Monster
{
public:
	Monster_14() : Monster({ 200, 0, 0, 2.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_14.png"); }
private:
};

class Monster_15 : public Monster
{
public:
	Monster_15() : Monster({ 400, 0, 0, 2.0 }) { image = Engine::Instance().GetTextureManager().Load("assets/enemy_s2/Monster_15.png"); }
private:
};