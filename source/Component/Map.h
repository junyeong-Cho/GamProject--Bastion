#pragma once

#include "Engine/Component.h"
#include "Engine/Matrix.h"
#include "Engine/DrawShape.h"
#include "Engine/Texture.h"
#include "Engine/Sprite.h"

#include "Engine/Vec2.h"

class Map : public GAM200::Component
{
public:
	Map() : game_background("assets/Background/game_tile.spt", nullptr)
	{

	}

	void Draw(Math::TransformationMatrix camera_matrix)
	{
        //game_background.Draw(0, 0, 1280, 800);
        game_background.Draw(/*Math::TranslationMatrix(middle_point) * */camera_matrix);
	}

public:
	GAM200::Sprite game_background;

	static inline double basic_size = 80;

	static inline double outer_left_end = 380;
	static inline double outer_rigiht_end = 900;
	static inline double outer_top_end = 740;
	static inline double outer_bottom_end = 100;

	static inline double inner_left_end = outer_left_end + basic_size;
	static inline double inner_rigiht_end = outer_rigiht_end - basic_size;
	static inline double inner_top_end = outer_top_end - basic_size;
	static inline double inner_bottom_end = outer_bottom_end + basic_size;

	static inline double middle_left_end = outer_left_end + basic_size / 2;
	static inline double middle_rigiht_end = outer_rigiht_end - basic_size / 2;
	static inline double middle_top_end = outer_top_end - basic_size / 2;
	static inline double middle_bottom_end = outer_bottom_end + basic_size / 2;


	static inline Math::vec2 middle_point{ (inner_left_end + inner_rigiht_end) / 2.0, (inner_top_end + inner_bottom_end) / 2.0 };

	static inline Math::vec2 outer_lower_left{ outer_left_end, outer_bottom_end };
	static inline Math::vec2 outer_lower_right{ outer_rigiht_end, outer_bottom_end };
	static inline Math::vec2 outer_upper_right{ outer_rigiht_end, outer_top_end };
	static inline Math::vec2 outer_upper_left{ outer_left_end, outer_top_end };

	static inline Math::vec2 inner_lower_left{ inner_left_end,  inner_bottom_end };
	static inline Math::vec2 inner_lower_right{ inner_rigiht_end,  inner_bottom_end };
	static inline Math::vec2 inner_upper_right{ inner_rigiht_end, inner_top_end };
	static inline Math::vec2 inner_upper_left{ inner_left_end, inner_top_end };

	static inline Math::vec2 middle_lower_left{ middle_left_end, middle_bottom_end };
	static inline Math::vec2 middle_lower_right{ middle_rigiht_end, middle_bottom_end };
	static inline Math::vec2 middle_upper_right{ middle_rigiht_end, middle_top_end };
	static inline Math::vec2 middle_upper_left{ middle_left_end, middle_top_end };
};