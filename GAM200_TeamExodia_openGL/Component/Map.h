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
		shape.SetColor(0.5f, 0.5f, 0.5f, 0.5f);
		shape.DrawRectangle(static_cast<int>(Map::middle_point.x) - static_cast<int>(basic_size) * 3 / 8, static_cast<int>(Map::middle_point.y) - static_cast<int>(basic_size) * 3 / 8, static_cast<int>(basic_size) * 3 / 4, static_cast<int>(basic_size) * 3 / 4);

		shape.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		shape.DrawRectangle_NoFill_WithPoints(static_cast<int>(Map::inner_left_end), static_cast<int>(Map::inner_bottom_end), static_cast<int>(Map::inner_rigiht_end), static_cast<int>(Map::inner_top_end));
		shape.DrawRectangle_NoFill_WithPoints(static_cast<int>(Map::outer_left_end), static_cast<int>(Map::outer_bottom_end), static_cast<int>(Map::outer_rigiht_end), static_cast<int>(Map::outer_top_end));
	}

public:
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


	static inline Math::vec2 middle_point{ (inner_left_end + inner_rigiht_end) / 2.0, (inner_top_end + inner_bottom_end) / 2.0};

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