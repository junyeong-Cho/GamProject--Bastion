/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Audio.h
Project:    GAM200_TeamExodia_openGL
Author:     Jaeyong Lee
Created:    December	15, 2023
Updated:    December	15, 2023
*/

#pragma once



#include "SFML/Audio.hpp"
#include <list>

namespace GAM200
{
    class SoundEffect
    {
    public:

        float effectVolume = 25;
        float musicVolume = 20;
        float BigVolume = 80;

        //static SoundEffect Gem();
        static SoundEffect& Button_1();
        static SoundEffect& Button_2();
        static SoundEffect& Button_3();
        static SoundEffect& Dash_1();
        static SoundEffect& Dash_2();
        static SoundEffect& GameClear();
        static SoundEffect& GameOver();
        static SoundEffect& cannot_select();
        static SoundEffect& Monster_Die_1();
        static SoundEffect& Monster_Die_2();
        static SoundEffect& Monster_Die_3();
        static SoundEffect& Reload();
        static SoundEffect& Select_MainMenu();
        static SoundEffect& Select_Map();
        static SoundEffect& Shotgun();
        static SoundEffect& Tower_Delete();
        static SoundEffect& Tower_Placing();
        static SoundEffect& Tower_Upgrade();
        static SoundEffect& Wave_Start();
        static SoundEffect& Attack();
        static SoundEffect& MainMenu_BGM();
        static SoundEffect& Game_BGM();




        SoundEffect(const std::string& path);
        void play();
        void SeBGMVolume(float volume);
        float GetBGMVolume() { return musicVolume; }
        void Big_play();
        void loopplay();
        void stopAll();

    private:
        sf::SoundBuffer buffer;
        std::list<sf::Sound> sounds;
    };
}