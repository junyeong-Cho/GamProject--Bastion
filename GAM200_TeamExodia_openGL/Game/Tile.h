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
#include "../Engine/Texture.h"


// Virtual class for tiles
class Tile :public GAM200::GameObject {
public:
	Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Tile; }
	std::string TypeName() override { return "Tile"; }

	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;

	const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

	Math::ivec2 size;

	void Tile_Destroy();

protected:

	GAM200::Texture block_tile = GAM200::Texture("assets/images/b_tile.png", GAM200::Texture::TextureType::RECTANGLE);
	GAM200::Texture obs_title = GAM200::Texture("assets/images/obs_block.png", GAM200::Texture::TextureType::RECTANGLE);
	struct Color {
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
	} color;
	
	bool passing_tile_bool = false;
	bool block_tile_bool = false;
	bool obs_tile_bool = false;
	bool pit_tile_bool = false;

private:

};

// Passable Tile
class Pass__Tile : public Tile {
public:
	Pass__Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Pass__Tile; }
	std::string TypeName() override { return "Pass__Tile"; }

	void Update(double dt) override;

private:

};

// Block Tile
class Block_Tile : public Tile {
public:
	Block_Tile(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Block_Tile; }
	std::string TypeName() override { return "Block_Tile"; }

	void Update(double dt) override;

private:

};

// Obstacle Tile
class Obstacle : public Tile
{
public:
	Obstacle(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Obstacle; }
	std::string TypeName() override { return "Obstacle"; }

	void Update(double dt) override;

private:

};

// Pit Tile
class Pit : public Tile
{
public:
	Pit(Math::irect boundary);

	GameObjectTypes Type() override { return GameObjectTypes::Pit; }
	std::string TypeName() override { return "Pit"; }

	void Update(double dt) override;

private:

};