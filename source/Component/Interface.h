#pragma once

#include "Engine/Component.h"
#include "Engine/DrawShape.h"
#include "Engine/Matrix.h"
#include "Engine/Sprite.h"
#include "Engine/Texture.h"
#include "Engine/Vec2.h"

#include "Game/Objects/Button.h"
//sed
class Interface : public GAM200::Component
{
public:
    Interface()
        : ui("assets/Background/ingame_ui_base.png"), enemy_wave("assets/Background/enemy_wave_ui.png"), next_wave("assets/Background/next_wave.png"),
          gameSpeedButton({ 1016.4631, 688.3434 }, { 74.1758, 74.1758 }), 
          skipButton({ 1144.4631, 688.3434 }, { 74.1758, 74.1758 }),
          settingButton({ 61.3611, 688.3434 }, { 74.1758, 74.1758 })
    {
    }
 

    void Draw(Math::TransformationMatrix camera_matrix,bool in_rest)
    {

        ui.Draw(0, 0, 1280, 800);
        if (in_rest == false)
        {
         enemy_wave.Draw(477.3428, 723.9637, 328, 50);
        }
       
        else if(in_rest == true)
        {
        next_wave.Draw(0, 0, 1280, 800);
        }
        
        gameSpeedButton.Draw(camera_matrix);
        skipButton.Draw(camera_matrix);
        settingButton.Draw(camera_matrix);
    }

public:
    GAM200::Texture ui;
    GAM200::Texture enemy_wave;
    GAM200::Texture next_wave;
    GameSpeed_Button gameSpeedButton;
    Skip_Button      skipButton;
    Setting_Button   settingButton;
};