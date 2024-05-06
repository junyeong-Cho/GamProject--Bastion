/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/


#include "TextureManager.h"
#include "Texture.h"
#include "Engine.h"


GAM200::Texture* GAM200::TextureManager::Load(const std::filesystem::path& file_path)
{
    auto it = textures.find(file_path);
    if (it != textures.end())
    {
        //Engine::GetLogger().LogEvent("Texture already loaded: " + file_path.generic_string());
        return it->second;
    }
    else
    {
        Texture* texture = new Texture(file_path);
        textures[file_path] = texture;
        Engine::GetLogger().LogEvent("Loaded texture: " + file_path.generic_string());
        return texture;
    }
}


void GAM200::TextureManager::Unload()
{
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
        it->second = nullptr;
    }

    textures.clear();
}
