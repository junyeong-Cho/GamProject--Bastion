
#include <iostream>

#include "../Engine/ComponentManager.h"
#include "../Engine/GameState.h"
#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"


#include "../Game/AStar.h"


class ShowPath : public GAM200::Component	
{
public:
	void LoadPath();
	
	void Update();

	void DrawPath();


private:
	std::vector<Math::ivec2> get_local_path;

	GAM200::DrawShape path_line;

};