/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowPath.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    December   11, 2023
Updated:    December   11, 2023
*/


#include "ShowPath.h"
#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"  // Include the header for drawing functions
#include "../Game/Wave.h"
#include "../Game/Monster.h"
#include "../Game/Map.h"

ShowPath::ShowPath()
{
    LoadPath();
}

void ShowPath::LoadPath()
{
    get_local_path = Astar::GetInstance().GetPath();
    Map::GetInstance().GetMap();
}


void ShowPath::Update() 
{
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tidle)) 
    {
        enabled = !(enabled);
    }

    wave_state = Engine::GetGameStateManager().GetGSComponent<Wave>()->GetState();

    LoadPath();
    DrawPath();  // Call to draw the path    
}


void ShowPath::DrawPath() 
{
    // Assuming tile size and offset are available
    const int tileSize = 80;           // Example tile size, adjust to your game's needs
    const Math::ivec2 offset(40, 40);  // Adjust if your grid is offset on the screen


    if (enabled == true)
    {
        return;
    }

    for (size_t i = 0; i < get_local_path.size() - 1; ++i) 
    {
        // Calculate screen coordinates from grid coordinates
        Math::ivec2 start = get_local_path[i]     * tileSize + offset;
        Math::ivec2 end   = get_local_path[i + 1] * tileSize + offset;


        Engine::Instance().push();
        // Set line color and width

        if (wave_state == Engine::GetGameStateManager().GetGSComponent<Wave>()->Wave_State::InProgress)
        {
            path_line.SetColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red color (example)
        }
        else
        {
            path_line.SetColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green color (example)
        }
        
        path_line.SetLineWidth(6.0f);  // Line width

        // Draw line between points
        path_line.DrawLine(start, end);

        Engine::Instance().pop();
    }
}
