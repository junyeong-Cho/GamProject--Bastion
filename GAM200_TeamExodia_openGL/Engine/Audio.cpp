/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Audio.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Jaeyong Lee
Created:    December	15, 2023
Updated:    December	15, 2023
*/


#include "Audio.h"
#include "Engine.h"

namespace GAM200
{
	SoundEffect::SoundEffect(const std::filesystem::path& filePath, bool bgm_se)
	{
		Load(filePath, bgm_se);
	}

	void SoundEffect::Load(const std::filesystem::path& filePath, bool bgm_se)
	{
		playsoundBuffer.loadFromFile(filePath.generic_string());
		playsound.setBuffer(playsoundBuffer);
		if (bgm_se)
		{
			playsound.setVolume(BGM_volume);
			playsound.setLoop(true);
		}
		else
		{
			playsound.setVolume(SE_volume);
		}
	}

	void SoundEffect::Play()
	{
		playsound.play();
	}

	void SoundEffect::Settings(float volume, bool loop)
	{
		playsound.setVolume(volume);
		playsound.setLoop(loop);
	}

	void SoundEffect::Stop()
	{
		playsound.stop();
	}

	SFXManager::SFXManager()
	{
	}

	void SFXManager::PrePareSFX(const std::filesystem::path& filePath)
	{
		if (filePath.extension() != ".sdat")
		{
			throw std::runtime_error("Bad FileType.   " + filePath.generic_string() + " not a data info file(.sdat)");
		}
		std::ifstream inFile(filePath);

		if (!inFile.is_open())
		{
			throw std::runtime_error("Failed to load data file!");
		}

		while (!inFile.eof())
		{
			std::string SFXType;
			getline(inFile, SFXType);
			if (SFXType == "BGM")
			{
				std::string real_filePath;
				getline(inFile, real_filePath);
				pathToSFX_BGM[real_filePath] = new SoundEffect(real_filePath, true);
			}
			else if (SFXType == "SE")
			{
				std::string real_filePath;
				getline(inFile, real_filePath);
				pathToSFX_SE[real_filePath] = new SoundEffect(real_filePath, false);
			}
		}
	}

	SoundEffect* SFXManager::Load(const std::string filePath)
	{
		if (pathToSFX_BGM.find(filePath) != pathToSFX_BGM.end())
		{
			SFX_BGM = pathToSFX_BGM[filePath];
			// SFX_BGM->Settings(BGM_volume, true);
			return SFX_BGM;
		}
		else
		{
			SFX_SE = pathToSFX_SE[filePath];
			// SFX_SE->Settings(SE_volume, false);
			return SFX_SE;
		}
	}

	void SFXManager::BGMController(float volume, bool loop)
	{
		SFX_BGM->Settings(volume, loop);
	}

	void SFXManager::SEController(float volume, bool loop)
	{
		for (auto& t : pathToSFX_SE)
		{
			t.second->Settings(volume, loop);
		}
	}
}