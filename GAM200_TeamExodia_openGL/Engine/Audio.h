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
#include <SFML/Audio.hpp>
#include <list>
#include <filesystem>
#include <map>


namespace GAM200
{
	class SoundEffect
	{
	private:
		sf::SoundBuffer playsoundBuffer;
		sf::Sound playsound;
		float BGM_volume{ 20 };
		float SE_volume{ 15 };

	public:
		SoundEffect(const std::filesystem::path& filePath, bool bgm_se);
		void Load(const std::filesystem::path& filePath, bool bgm_se);
		void Play();
		void Stop();
		void Settings(float volume, bool loop);
	};

	class SFXManager
	{
	private:
		std::map<std::string, SoundEffect*> pathToSFX_BGM;
		std::map<std::string, SoundEffect*> pathToSFX_SE;

		SoundEffect* SFX_BGM;
		SoundEffect* SFX_SE;

	public:
		SFXManager();
		void PrePareSFX(const std::filesystem::path& filePath);
		SoundEffect* Load(const std::string);
		void LoadFile(std::string filePath); // 파일 로드
		void Stop();						 // 정지
		// void Play_BGM(const std::string filePath); // 재생
		// void Play_SE(const std::string filePath); // 재생
		void Settings(float volume, bool loop); // 음량 및 루프 설정
		void BGMController(float volume, bool loop);
		void SEController(float volume, bool loop);
	};

}