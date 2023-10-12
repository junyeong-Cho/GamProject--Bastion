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

	static constexpr int size = 100;

protected:

private:

};