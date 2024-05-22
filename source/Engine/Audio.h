#pragma once

#include "../Engine/ComponentManager.h"
#include "AudioList.h"
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace GAM200
{
    class MusicEffect : public GAM200::Component
    {
    public:
        MusicEffect();
        void AddMusicFile(const std::string& filename, AudioID id);
        void LoadFile(const std::string& filename);
        void Play(AudioID id);

        void Stop(AudioID id);
        void StopAll();

        void SetVolume(float volume);

        float* GetMusicVolume()
        {
            return &defaultVolume;
        }

        bool IsMusicPlaying(AudioID id) const
        {
            auto it = musicMap.find(id);
            if (it != musicMap.end())
            {
                return it->second->getStatus() == sf::Music::Playing;
            }
            return false;
        }

    private:
        float                                                   defaultVolume = 0.f;
        std::unordered_map<AudioID, std::unique_ptr<sf::Music>> musicMap;
        bool                                                    isMusicPlaying = false;
    };

    class SoundEffect : public GAM200::Component
    {
    public:
        SoundEffect();
        void AddSoundFile(const std::string& filename, AudioID id);
        void LoadFile(const std::string& filename);
        void SetVolume(float volume);
        void Play(AudioID id);

    private:
        float                                        defaultVolume = 40.f;
        std::unordered_map<AudioID, sf::SoundBuffer> bufferMap;
        std::unordered_map<AudioID, sf::Sound>       soundMap;
        bool                                         isSoundPlaying = false;
    };

    class AudioManager
    {
    public:
        AudioManager()
        {
            PreloadAudioFiles();
        }

        ~AudioManager() = default;


        void AddMusicFile(AudioID id);
        void AddSoundFile(AudioID id);
        
        void PlayMusic(AudioID id);

        void StopMusic(AudioID id);
        void StopAllMusic();

        void SetSoundVolume(float volume);
        void SetMusicVolume(float volume);
        void PlaySound(AudioID id);

        bool IsMusicPlaying(AudioID id) const
        {
            return musicEffect.IsMusicPlaying(id);
        }

        static AudioManager& Instance()
        {
            static AudioManager instance;
            return instance;
        }

        void PreloadAudioFiles();

    private:
        
        
        MusicEffect musicEffect;
        SoundEffect soundEffect;
    };
}
