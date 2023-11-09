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

		void SetVolume(float volume);


		float* GetMusicVolume() { return &defaultVolume; }

	private:

		float defaultVolume = 0.f;

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

		float defaultVolume = 40.f;

		std::vector<sf::SoundBuffer> buffers;
		std::vector<sf::Sound> sounds;

		bool isSoundPlaying = false;
	};
}
