#pragma once

#include "../Engine/Component.h"
#include "../Engine/Matrix.h"
#include "../Engine/DrawShape.h"

#include "vec2.h"

class Map : public GAM200::Component
{
public:
	void Draw()
	{
		GAM200::DrawShape shape;
		shape.SetColor(0.0f, 0.0f, 0.0f, 1.0f);

		shape.DrawRectangle_NoFill_WithPoints(static_cast<int>(Map::inner_left_end), static_cast<int>(Map::inner_bottom_end), static_cast<int>(Map::inner_rigiht_end), static_cast<int>(Map::inner_top_end));
		shape.DrawRectangle_NoFill_WithPoints(static_cast<int>(Map::outer_left_end), static_cast<int>(Map::outer_bottom_end), static_cast<int>(Map::outer_rigiht_end), static_cast<int>(Map::outer_top_end));
	}

public:
	static inline double basic_size = 80;

	static inline double outer_left_end = 360;
	static inline double outer_rigiht_end = 920;
	static inline double outer_top_end = 720;
	static inline double outer_bottom_end = 0;

	static inline double inner_left_end = outer_left_end + basic_size;
	static inline double inner_rigiht_end = outer_rigiht_end - basic_size;
	static inline double inner_top_end = outer_top_end - basic_size;
	static inline double inner_bottom_end = outer_bottom_end + basic_size;

	static inline double middle_left_end = outer_left_end + basic_size / 2;
	static inline double middle_rigiht_end = outer_rigiht_end - basic_size / 2;
	static inline double middle_top_end = outer_top_end - basic_size / 2;
	static inline double middle_bottom_end = outer_bottom_end + basic_size / 2;


	static inline Math::vec2 middle_point{ 640,360 };

	static inline Math::vec2 outer_lower_left{ 360,   0 };
	static inline Math::vec2 outer_lower_right{ 920,   0 };
	static inline Math::vec2 outer_upper_right{ 920, 720 };
	static inline Math::vec2 outer_upper_left{ 360, 720 };

	static inline Math::vec2 inner_lower_left{ 440,  80 };
	static inline Math::vec2 inner_lower_right{ 840,  80 };
	static inline Math::vec2 inner_upper_right{ 840, 640 };
	static inline Math::vec2 inner_upper_left{ 440, 640 };

	static inline Math::vec2 middle_lower_left{ 400,  40 };
	static inline Math::vec2 middle_lower_right{ 880,  40 };
	static inline Math::vec2 middle_upper_right{ 880, 680 };
	static inline Math::vec2 middle_upper_left{ 400, 680 };
};