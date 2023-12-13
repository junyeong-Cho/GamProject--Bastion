/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Audio.h
Project:    GAM200 Engine
Author:     Junyeong cho
Created:    November 8, 2023
Updated:    November 8, 2023
*/

#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <vector>
#include <memory>
#include "../Engine/ComponentManager.h"
#include "../Engine/Engine.h"

namespace GAM200
{
	class MusicEffect : public GAM200::Component
	{
	public:
		MusicEffect();
		void AddMusicFile(const std::string& filename);
		void LoadFile(const std::string& filename);

		void Play(int index);
		void Stop();

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

		std::vector<std::unique_ptr<sf::Music>> musicList;
		bool isMusicPlaying = false;
	};


	class SoundEffect : public GAM200::Component
	{
	public:
		SoundEffect();
		void AddSoundFile(const std::string& filename);
		void LoadFile(const std::string& filename);

		void Play(int index);

	private:

		float defaultVolume = 70.f;

		std::vector<sf::SoundBuffer> buffers;
		std::vector<sf::Sound> sounds;

		bool isSoundPlaying = false;
	};
}
