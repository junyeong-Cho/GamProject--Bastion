#pragma once

#include <string>
#include <unordered_map>

namespace GAM200
{
    enum class AudioID
    {
        MainMenu_BGM,
        Game_BGM,
        Maintheme_Reference,
        BattleTheme_Reference,

        Button_1,
        Button_2,
        Button_3,

        Dash_1,
        Dash_2,

        GameClear,
        GameOver,
        cannot_select,

        Monster_Die_1,
        Monster_Die_2,
        Monster_Die_3,

        Reload,

        Select_MainMenu,
        Select_Map,

        Shotgun,

        Tower_Delete,
        Tower_Placing,
        Tower_Upgrade,

        gun_sound_meca,

        Wave_Start
    };

    static const std::unordered_map<AudioID, std::string> AudioFiles = 
    {
        {         AudioID::MainMenu_BGM,   "assets/Sounds/Theme/Maintheme_Reference.wav"},
        {             AudioID::Game_BGM, "assets/Sounds/Theme/BattleTheme_Reference.wav"},
        {  AudioID::Maintheme_Reference,   "assets/Sounds/Theme/Maintheme_Reference.wav"},
        {AudioID::BattleTheme_Reference, "assets/Sounds/Theme/BattleTheme_Reference.wav"},

        {             AudioID::Button_1,        "assets/Sounds/SoundEffect/Button_1.wav"},
        {             AudioID::Button_2,        "assets/Sounds/SoundEffect/Button_2.wav"},
        {             AudioID::Button_3,        "assets/Sounds/SoundEffect/Button_3.wav"},

        {               AudioID::Dash_1,          "assets/Sounds/SoundEffect/Dash_1.wav"},
        {               AudioID::Dash_2,          "assets/Sounds/SoundEffect/Dash_2.wav"},

        {            AudioID::GameClear,       "assets/Sounds/SoundEffect/GameClear.wav"},
        {             AudioID::GameOver,        "assets/Sounds/SoundEffect/GameOver.wav"},
        {        AudioID::cannot_select,   "assets/Sounds/SoundEffect/cannot_select.wav"},

        {        AudioID::Monster_Die_1,   "assets/Sounds/SoundEffect/Monster_Die_1.wav"},
        {        AudioID::Monster_Die_2,   "assets/Sounds/SoundEffect/Monster_Die_2.wav"},
        {        AudioID::Monster_Die_3,   "assets/Sounds/SoundEffect/Monster_Die_3.wav"},

        {               AudioID::Reload,          "assets/Sounds/SoundEffect/Reload.wav"},

        {      AudioID::Select_MainMenu, "assets/Sounds/SoundEffect/Select_MainMenu.wav"},
        {           AudioID::Select_Map,      "assets/Sounds/SoundEffect/Select_Map.wav"},

        {              AudioID::Shotgun,         "assets/Sounds/SoundEffect/Shotgun.wav"},

        {         AudioID::Tower_Delete,    "assets/Sounds/SoundEffect/Tower_Delete.wav"},
        {        AudioID::Tower_Placing,   "assets/Sounds/SoundEffect/Tower_Placing.wav"},
        {        AudioID::Tower_Upgrade,   "assets/Sounds/SoundEffect/Tower_Upgrade.wav"},

        {       AudioID::gun_sound_meca,  "assets/Sounds/SoundEffect/gun_sound_meca.wav"},

        {           AudioID::Wave_Start,      "assets/Sounds/SoundEffect/Wave_Start.wav"}
    };
}
