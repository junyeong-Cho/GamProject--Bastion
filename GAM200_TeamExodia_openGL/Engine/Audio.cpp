#include "Audio.h"


GAM200::SoundEffect& GAM200::SoundEffect::Button_1()
{
    static SoundEffect Button_1("assets/Sounds/SoundEffect/Button_1.wav");
    return Button_1;
}

GAM200::SoundEffect& GAM200::SoundEffect::Button_2()
{
    static SoundEffect Button_2("assets/Sounds/SoundEffect/Button_2.wav");
    return Button_2;
}

GAM200::SoundEffect& GAM200::SoundEffect::Button_3()
{
    static SoundEffect Button_3("assets/Sounds/SoundEffect/Button_3.wav");
    return Button_3;
}

GAM200::SoundEffect& GAM200::SoundEffect::Dash_1()
{
    static SoundEffect Dash_1("assets/Sounds/SoundEffect/Dash_1.wav");
    return Dash_1;
}

GAM200::SoundEffect& GAM200::SoundEffect::Dash_2()
{
    static SoundEffect Dash_2("assets/Sounds/SoundEffect/Dash_2.wav");
    return Dash_2;
}

GAM200::SoundEffect& GAM200::SoundEffect::GameClear()
{
    static SoundEffect GameClear("assets/Sounds/SoundEffect/GameClear.wav");
    return GameClear;
}

GAM200::SoundEffect& GAM200::SoundEffect::GameOver()
{
    static SoundEffect GameOver("assets/Sounds/SoundEffect/GameOver.wav");
    return GameOver;
}

GAM200::SoundEffect& GAM200::SoundEffect::cannot_select()
{
    static SoundEffect cannot_select("assets/Sounds/SoundEffect/cannot_select.wav");
    return cannot_select;
}

GAM200::SoundEffect& GAM200::SoundEffect::Monster_Die_1()
{
    static SoundEffect Monster_Die_1("assets/Sounds/SoundEffect/Monster_Die_1.wav");
    return Monster_Die_1;
}

GAM200::SoundEffect& GAM200::SoundEffect::Monster_Die_2()
{
    static SoundEffect Monster_Die_2("assets/Sounds/SoundEffect/Monster_Die_2.wav");
    return Monster_Die_2;
}

GAM200::SoundEffect& GAM200::SoundEffect::Monster_Die_3()
{
    static SoundEffect Monster_Die_3("assets/Sounds/SoundEffect/Monster_Die_3.wav");
    return Monster_Die_3;
}

GAM200::SoundEffect& GAM200::SoundEffect::Reload()
{
    static SoundEffect Reload("assets/Sounds/SoundEffect/Reload.wav");
    return Reload;
}

GAM200::SoundEffect& GAM200::SoundEffect::Select_MainMenu()
{
    static SoundEffect Select_MainMenu("assets/Sounds/SoundEffect/Select_MainMenu.wav");
    return Select_MainMenu;
}

GAM200::SoundEffect& GAM200::SoundEffect::Select_Map()
{
    static SoundEffect Select_Map("assets/Sounds/SoundEffect/Select_Map.wav");
    return Select_Map;
}

GAM200::SoundEffect& GAM200::SoundEffect::Shotgun()
{
    static SoundEffect Shotgun("assets/Sounds/SoundEffect/Shotgun.wav");
    return Shotgun;
}

GAM200::SoundEffect& GAM200::SoundEffect::Tower_Delete()
{
    static SoundEffect Tower_Delete("assets/Sounds/SoundEffect/Tower_Delete.wav");
    return Tower_Delete;
}

GAM200::SoundEffect& GAM200::SoundEffect::Tower_Placing()
{
    static SoundEffect Tower_Placing("assets/Sounds/SoundEffect/Tower_Placing.wav");
    return Tower_Placing;
}

GAM200::SoundEffect& GAM200::SoundEffect::Tower_Upgrade()
{
    static SoundEffect Tower_Upgrade("assets/Sounds/SoundEffect/Tower_Upgrade.wav");
    return Tower_Upgrade;
}

GAM200::SoundEffect& GAM200::SoundEffect::Attack()
{
    static SoundEffect Attack("assets/Sounds/SoundEffect/gun_sound_meca.wav");
    return Attack;
}

GAM200::SoundEffect& GAM200::SoundEffect::MainMenu_BGM()
{
    static SoundEffect MainMenu_BGM("assets/Sounds/Theme/Hihi.wav");
    return MainMenu_BGM;
}

GAM200::SoundEffect& GAM200::SoundEffect::Wave_Start()
{
    static SoundEffect Wave_Start("assets/Sounds/SoundEffect/Wave_Start.wav");
    return Wave_Start;
}


GAM200::SoundEffect::SoundEffect(const std::string& path)
{
    if (!buffer.loadFromFile(path))
        throw std::runtime_error("Failed to load sound file " + path);
}

void GAM200::SoundEffect::play()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(effectVolume);
    sounds.back().play();
}

void GAM200::SoundEffect::SeBGMVolume(float volume)
{
    musicVolume = volume;
}

void GAM200::SoundEffect::Big_play()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(BigVolume);
    sounds.back().play();
}

void GAM200::SoundEffect::loopplay()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(musicVolume);
    sounds.back().play();

    // 재생이 끝나면 다시 재생
    sounds.back().setLoop(true);
}

void GAM200::SoundEffect::stopAll()
{
    for (auto& sound : sounds)
    {
        sound.stop();
    }
}