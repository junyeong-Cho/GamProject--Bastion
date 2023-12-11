#include "Audio.h"


GAM200::SoundEffect& GAM200::SoundEffect::Landing()
{
    static SoundEffect Landing("Assets/Sound/Landing.wav");
    return Landing;
}

GAM200::SoundEffect& GAM200::SoundEffect::Jump()
{
    static SoundEffect Jump("Assets/Sound/JumpJump.wav");
    return Jump;
}

GAM200::SoundEffect& GAM200::SoundEffect::Portal()
{
    static SoundEffect Portal("Assets/Sound/Portal.wav");
    return Portal;
}

GAM200::SoundEffect& GAM200::SoundEffect::MeleeAttack()
{
    static SoundEffect MeleeAttack("Assets/Sound/sword_swing.wav");
    return MeleeAttack;
}

GAM200::SoundEffect& GAM200::SoundEffect::Item()
{
    static SoundEffect Item("Assets/Sound/Item.wav");
    return Item;
}

GAM200::SoundEffect& GAM200::SoundEffect::Attacked()
{
    static SoundEffect Attacked("assets/Sounds/SoundEffect/Attacked.wav");
    return Attacked;
}
GAM200::SoundEffect& GAM200::SoundEffect::Attack()
{
    static SoundEffect Attack("assets/Sounds/SoundEffect/gun_sound_meca.wav");
    return Attack;
}

GAM200::SoundEffect& GAM200::SoundEffect::Dash()
{
    static SoundEffect Dash("Assets/Sound/Dash.wav");
    return Dash;
}

GAM200::SoundEffect& GAM200::SoundEffect::cannot_select()
{
    static SoundEffect cannot_select("Assets/Sound/cannot_select.wav");
    return cannot_select;
}

GAM200::SoundEffect& GAM200::SoundEffect::recovery2()
{
    static SoundEffect recovery2("Assets/Sound/recovery2.wav");
    return recovery2;
}

GAM200::SoundEffect& GAM200::SoundEffect::Weapon_change()
{
    static SoundEffect Weapon_change("Assets/Sound/Weapon_change.wav");
    return Weapon_change;
}

GAM200::SoundEffect& GAM200::SoundEffect::FeildBGM()
{
    static SoundEffect FeildBGM("assets/Sounds/Theme/Hihi.wav");
    return FeildBGM;
}

GAM200::SoundEffect& GAM200::SoundEffect::BossBGM()
{
    static SoundEffect BossBGM("assets/Sounds/Theme/BossBGM.wav");
    return BossBGM;
}

////////////////////////Boss1
GAM200::SoundEffect& GAM200::SoundEffect::B1_swing()
{
    static SoundEffect B1_swing("Assets/Sound/Batswing.wav");
    return B1_swing;
}

GAM200::SoundEffect& GAM200::SoundEffect::B1_JumpAttack()
{
    static SoundEffect B1_JumpAttack("Assets/Sound/Stun.wav");
    return B1_JumpAttack;
}


////////////////////////Boss2   
GAM200::SoundEffect& GAM200::SoundEffect::B2_pew()
{
    static SoundEffect B2_pew("Assets/Sound/pew.wav");
    return B2_pew;
}

GAM200::SoundEffect& GAM200::SoundEffect::B2_baldosool()
{
    static SoundEffect B2_baldosool("Assets/Sound/baldo.wav");
    return B2_baldosool;
}

GAM200::SoundEffect& GAM200::SoundEffect::B2_swordBeam()
{
    static SoundEffect B2_swordBeam("Assets/Sound/sword_beam.wav");
    return B2_swordBeam;
}

GAM200::SoundEffect& GAM200::SoundEffect::B2_jump_Attack()
{
    static SoundEffect B2_jump_Attack("Assets/Sound/JJikgi.wav");
    return B2_jump_Attack;
}

////////////////////////Boss3   
GAM200::SoundEffect& GAM200::SoundEffect::B3_Bbaeggom()
{
    static SoundEffect B3_Bbaeggom("Assets/Sound/Bbaeggom.wav");
    return B3_Bbaeggom;
}

GAM200::SoundEffect& GAM200::SoundEffect::B3_WormJump()
{
    static SoundEffect B3_WormJump("Assets/Sound/WormJump.wav");
    return B3_WormJump;
}

////////////////////////Boss4
GAM200::SoundEffect& GAM200::SoundEffect::B4_Inferno()
{
    static SoundEffect B4_Inferno("Assets/Sound/Inferno.wav");
    return B4_Inferno;
}

GAM200::SoundEffect& GAM200::SoundEffect::B4_Fireball()
{
    static SoundEffect B4_Fireball("Assets/Sound/Flame.wav");
    return B4_Fireball;
}

GAM200::SoundEffect& GAM200::SoundEffect::B4_Psychokinesis()
{
    static SoundEffect B4_Psychokinesis("Assets/Sound/Psychokinesis.wav");
    return B4_Psychokinesis;
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
    sounds.back().setVolume(musicVolume);
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