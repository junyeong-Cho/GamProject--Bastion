/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Tile.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		11, 2023
Updated:    October		11, 2023
*/


#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"

#include "../Game/Tile.h"

Tile::Tile(Math::irect boundary) : GameObject(static_cast<Math::vec2>(boundary.point1)) {
	size = boundary.Size();
	AddGOComponent(new GAM200::RectCollision({ Math::ivec2{0, 0}, boundary.Size() }, this));

}

void Tile::Update(double dt) {

}
void Tile::Draw(Math::TransformationMatrix camera_matrix) {
	

	if (passing_tile_bool == true)
	{
	   /* GAM200::DrawShape tile;
		tile.SetColor(0.431f, 0.282f, 0.067f, 1.0f);
		tile.SetColor(color.r, color.g, color.b, 1.0f);
		tile.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size, size);*/
		block_tile.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size.x, size.y);
	}

}


Pass__Tile::Pass__Tile(Math::irect boundary) : Tile(boundary) {
	color.r = 0.157f;
	color.g = 0.631f;
	color.b = 0.235f;

	passing_tile_bool = true;
}

void Pass__Tile::Update(double dt) {

}


Block_Tile::Block_Tile(Math::irect boundary) : Tile(boundary) {
	color.r = 0.431f;
	color.g = 0.282f;
	color.b = 0.067f;

	block_tile_bool = true;
}

void Block_Tile::Update(double dt) {

}