/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Tile.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		11, 2023
*/

#pragma once

#include "../Engine/GameObject.h"
#include "../Game/GameObjectTypes.h"

class Tile :public GAM200::GameObject {
public:
	Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Tile; }
	std::string TypeName() override { return "Tile"; }

	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;

	const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

	int size;

protected:
	struct Color {
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
	} color;
private:

};


class Passing_Tile : public Tile {
public:
	Passing_Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Passing_Tile; }
	std::string TypeName() override { return "Passing_Tile"; }

	void Update(double dt) override;
private:

};

class Block_Tile : public Tile {
public:
	Block_Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Block_Tile; }
	std::string TypeName() override { return "Block_Tile"; }

	void Update(double dt) override;
private:
};