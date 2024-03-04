/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowPath.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    December   11, 2023
Updated:    December   11, 2023
*/

#include <iostream>

#include "../Engine/ComponentManager.h"
#include "../Engine/GameState.h"
#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"


#include "../Game/AStar.h"


class ShowPath : public GAM200::Component	
{
public:

	ShowPath();

	void LoadPath();
	
	void Update();

	void DrawPath();


private:
	std::vector<Math::ivec2> get_local_path;

	GAM200::DrawShape path_line;

	bool enabled;

	bool wave_state;

};