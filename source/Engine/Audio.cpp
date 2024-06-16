#include "Audio.h"

namespace GAM200
{
    MusicEffect::MusicEffect()
    {
    }

    void MusicEffect::AddMusicFile(const std::string& filename, AudioID id)
    {
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
        if (music->openFromFile(filename))
        {
            music->setLoop(true);
            musicMap[id] = std::move(music);
        }
    }

    void MusicEffect::LoadFile(const std::string& filename)
    { 

    }

    void MusicEffect::Play(AudioID id)
    {
        if (musicMap.find(id) != musicMap.end())
        {
            if (musicMap[id]->getStatus() != sf::Music::Playing) 
            {
                musicMap[id]->play();
                isMusicPlaying = true;
            }
        }
    }

    void MusicEffect::Stop(AudioID id)
    {
        if (musicMap.find(id) != musicMap.end())
        {
            if (musicMap[id]->getStatus() == sf::Music::Playing)
            {
                musicMap[id]->stop();
            }
        }
    }

    void MusicEffect::StopAll()
    {
        for (auto& musicPair : musicMap)
        {
            if (musicPair.second->getStatus() == sf::Music::Playing)
            {
                musicPair.second->stop();
            }
        }
        isMusicPlaying = false;
    }

    void MusicEffect::SetVolume(float volume)
    {
        defaultVolume = volume;
        for (auto& musicPair : musicMap)
        {
            musicPair.second->setVolume(volume);
        }
    }

    SoundEffect::SoundEffect()
    {
    }

    void SoundEffect::AddSoundFile(const std::string& filename, AudioID id)
    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filename))
        {
            bufferMap[id] = buffer;
            soundMap[id]  = sf::Sound(bufferMap[id]);
        }
    }

    void SoundEffect::LoadFile(const std::string& filename)
    { 

    }

    void SoundEffect::SetVolume(float volume)
    {
        defaultVolume = volume;
        for (auto& soundPair : soundMap)
        {
			soundPair.second.setVolume(volume);
		}
    }

    void SoundEffect::Play(AudioID id)
    {
        if (soundMap.find(id) != soundMap.end())
        {
            soundMap[id].play();
            isSoundPlaying = true;
        }
    }

    void AudioManager::AddMusicFile(AudioID id)
    {
        if (AudioFiles.find(id) != AudioFiles.end())
        {
            musicEffect.AddMusicFile(AudioFiles.at(id), id);
        }
    }

    void AudioManager::AddSoundFile(AudioID id)
    {
        if (AudioFiles.find(id) != AudioFiles.end())
        {
            soundEffect.AddSoundFile(AudioFiles.at(id), id);
        }
    }

    void AudioManager::PlayMusic(AudioID id)
    {
        musicEffect.Play(id);
    }

    void AudioManager::StopMusic(AudioID id)
    {
        musicEffect.Stop(id);
    }

    void AudioManager::StopAllMusic()
    {
        musicEffect.StopAll();
    }

    void AudioManager::SetSoundVolume(float volume)
    {
        soundEffect.SetVolume(volume);
    }

    void AudioManager::SetMusicVolume(float volume)
    {
        musicEffect.SetVolume(volume);
    }

    void AudioManager::PlaySound(AudioID id)
    {
        soundEffect.Play(id);
    }

    void AudioManager::PreloadAudioFiles()
    {
        for (const auto& pair : AudioFiles)
        {
            if (pair.first == AudioID::MainMenu_BGM || pair.first == AudioID::Game_BGM)
            {
                AddMusicFile(pair.first);
            }
            else
            {
                AddSoundFile(pair.first);
            }
        }
    }
}
