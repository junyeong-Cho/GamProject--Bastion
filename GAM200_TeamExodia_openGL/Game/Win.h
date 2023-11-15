
#pragma once

#include "../Game/States.h"
#include "../Game/Background.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/TextureManager.h"

#include "../Engine/Texture.h"
#include "../Engine/Font.h"

#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"


class Win : public GAM200::GameState
{
public:
	Win();

	void Load()				override;
	void Update(double dt)  override;
	void Unload()	        override;
	void Draw()				override;

	void ImguiDraw() override;
	void HandleEvent(SDL_Event& event) override;


	std::string GetName() override { return "Win"; }


private:
	std::unique_ptr<GAM200::Texture> message;

	GAM200::Texture victory = GAM200::Texture("assets/images/ui/splash/victory.png", GAM200::Texture::TextureType::RECTANGLE);
};