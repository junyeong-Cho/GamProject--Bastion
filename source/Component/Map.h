#pragma once

#include "Engine/Component.h"
#include "Engine/Matrix.h"
#include "Engine/DrawShape.h"
#include "Engine/Texture.h"
#include "Engine/Sprite.h"
#include "Engine/Vec2.h"

#include "Game/Objects/Button.h"

class Map : public GAM200::Component
{
public:
	Map()
		: game_map1("assets/Background/map1.png"), game_map2("assets/Background/map2.png"), game_map3("assets/Background/map3.png"),
		game_tuto_map("assets/Background/tuto_map.png"), blur("assets/Background/blur.png")
	{

	}

	void Draw(Math::TransformationMatrix camera_matrix,int map_number)
	{
    
		   if (map_number == 0)
		   {
			   game_tuto_map.Draw(0, 0, 1280, 800);
		   }
		   else if (map_number == 1)
		   {
			   game_map1.Draw(0, 0, 1280, 800);
		   }
		   else if(map_number == 2)
		   {
			   game_map2.Draw(0, 0, 1280, 800);
		   }
		   else
		   {
               game_map3.Draw(0, 0, 1280, 800);
		   }
			
	
	

		blur.Draw(0, 0, 1280, 800);
	}

public:
	GAM200::Texture game_map1;
	GAM200::Texture game_map2;
	GAM200::Texture game_map3;
	GAM200::Texture game_tuto_map;
	GAM200::Texture blur;
	//GAM200::Texture ui;

	static inline double basic_size = 80;

	static inline double outer_left_end = 380;
	static inline double outer_rigiht_end = 900;
	static inline double outer_top_end = 740; //700
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