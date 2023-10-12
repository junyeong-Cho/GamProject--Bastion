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
	AddGOComponent(new GAM200::RectCollision({ boundary }, this));
}

void Tile::Update(double dt) {

}
void Tile::Draw(Math::TransformationMatrix camera_matrix) {
	GAM200::DrawShape tile;
	tile.SetColor(0.431f, 0.282f, 0.067f, 1.0f);
	tile.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size, size);
}