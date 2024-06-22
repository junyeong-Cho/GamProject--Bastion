#pragma once

#include "Engine/GameObject.h"
#include "Game/GameObjectTypes.h"

#include "Component/Map.h"


class Monster : public GAM200::GameObject
{
public:
	struct MonsterInfo
	{
		double life;
		double defense;

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

    void SetSpeedScale(double scale) { info.speed_scale = scale; }
    double GetSpeedScale() const { return info.speed_scale; }
	void TakeDamage(double damage);

    enum class anm
    {
        none,
        dead
    };

protected:
	MonsterInfo info;
	static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0;
	static inline double speed = Map::basic_size;

	static inline double offset = Map::basic_size;

    static inline double tilt_time = 0.5;
    double               tilt_count = 0.0;
    double               tilt_amount = 0.0;
    double               tilt_decrease = 0.0;

    class State_None : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "None";
        }
    };

    class State_Dead : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "Dead";
        }
    };

    State_None state_none;
    State_Dead state_dead;

    double death_count = 0.0f;
    static inline double death_time  = 0.5;

    int max_life;

private:
	static int remaining_monster;
};

class Monster_1 : public Monster
{
public:
    Monster_1() : Monster({ 3, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel1.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_1(Math::vec2 position, Math::vec2 direction) : Monster({ 3, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel1.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_2 : public Monster
{
public:
    Monster_2() : Monster({ 5, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_2(Math::vec2 position, Math::vec2 direction) : Monster({ 5, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_3 : public Monster
{
public:
    Monster_3() : Monster({ 7, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel3.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_3(Math::vec2 position, Math::vec2 direction) : Monster({ 7, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel3.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_4 : public Monster
{
public:
    Monster_4() : Monster({ 4, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel4.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_4(Math::vec2 position, Math::vec2 direction) : Monster({ 4, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel4.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_5 : public Monster
{
public:
    Monster_5() : Monster({ 7, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel5.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_5(Math::vec2 position, Math::vec2 direction) : Monster({ 7, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel5.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_6 : public Monster
{
public:
    Monster_6() : Monster({ 10, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel6.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_6(Math::vec2 position, Math::vec2 direction) : Monster({ 10, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Jewel6.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_7 : public Monster
{
public:
    Monster_7() : Monster({ 8, 0, 1.2 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot1.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_7(Math::vec2 position, Math::vec2 direction) : Monster({ 8, 0, 1.2 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot1.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_8 : public Monster
{
public:
    Monster_8() : Monster({ 12, 0, 1.2 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_8(Math::vec2 position, Math::vec2 direction) : Monster({ 12, 0, 1.2 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_9 : public Monster
{
public:
    Monster_9() : Monster({ 16, 0, 1.2 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot3.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_9(Math::vec2 position, Math::vec2 direction) : Monster({ 16, 0, 1.2 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Robot3.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_10 : public Monster
{
public:
    Monster_10() : Monster({ 20, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Devil.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_10(Math::vec2 position, Math::vec2 direction) : Monster({ 20, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Devil.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_11 : public Monster
{
public:
    Monster_11() : Monster({ 25, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Devil2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_11(Math::vec2 position, Math::vec2 direction) : Monster({ 25, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Devil2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_12 : public Monster
{
public:
    Monster_12() : Monster({ 30, 0, 1.0 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Akuma.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_12(Math::vec2 position, Math::vec2 direction) : Monster({ 30, 0, 1.0 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Akuma.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_13 : public Monster
{
public:
    Monster_13() : Monster({ 20, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Akuma2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_13(Math::vec2 position, Math::vec2 direction) : Monster({ 20, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Akuma2.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_14 : public Monster
{
public:
    Monster_14() : Monster({ 22, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/mimic.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_14(Math::vec2 position, Math::vec2 direction) : Monster({ 22, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/mimic.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_15 : public Monster
{
public:
    Monster_15() : Monster({ 25, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/BanBanMon.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_15(Math::vec2 position, Math::vec2 direction) : Monster({ 25, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/BanBanMon.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};

class Monster_16 : public Monster
{
public:
    Monster_16() : Monster({ 30, 0, 1.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Boss.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    Monster_16(Math::vec2 position, Math::vec2 direction) : Monster({ 30, 0, 1.5 }, position, direction)
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Boss.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }
};