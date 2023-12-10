#include "ShowPath.h"
#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"  // Include the header for drawing functions
#include "../Game/Wave.h"
#include "../Game/Monster.h"

void ShowPath::LoadPath() 
{
    get_local_path = Engine::GetGameStateManager().GetGSComponent<Astar>()->GetPath();
}

void ShowPath::Update() 
{
    auto wave_state = Engine::GetGameStateManager().GetGSComponent<Wave>()->GetCurrentWave();

    if (wave_state == Wave::Wave_State::NotInProgress) 
    {
        LoadPath();
        DrawPath();  // Call to draw the path
    }
}

void ShowPath::DrawPath() {
    // Assuming tile size and offset are available
    const int tileSize = 32;  // Example tile size, adjust to your game's needs
    const Math::ivec2 offset(0, 0);  // Adjust if your grid is offset on the screen



    for (size_t i = 0; i < get_local_path.size() - 1; ++i) 
    {
        // Calculate screen coordinates from grid coordinates
        Math::ivec2 start = get_local_path[i] * tileSize + offset;
        Math::ivec2 end = get_local_path[i + 1] * tileSize + offset;



        // Set line color and width
        path_line.SetColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red color (example)
        path_line.SetLineWidth(2.0f);  // Line width

        // Draw line between points
        path_line.DrawLine(start, end);
    }
}
