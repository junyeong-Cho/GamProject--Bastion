/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "../Engine/Collision.h"
#include"../Engine/GameObjectManager.h"
#include"../Engine/Sprite.h"
#include"../Engine/Matrix.h"
#include "Engine.h"



GAM200::Sprite::Sprite(const std::filesystem::path& sprite_file, GameObject* object)
{
    Load(sprite_file, object);
}

GAM200::Sprite::~Sprite()
{
    for (auto animation : animations)
    {
        delete animation;
    }

    animations.clear();
}


void GAM200::Sprite::Load(const std::filesystem::path& sprite_file, GameObject* object)
{
    if (sprite_file.extension() != ".spt")
    {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .spt file");
    }

    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false)
    {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }



    hotspots.clear();
    frame_texels.clear();
    animations.clear();


    std::string text;
    in_file >> text;

    texture = Engine::GetTextureManager().Load(text);

    frame_size = texture->GetSize();

    in_file >> text;

    while (in_file.eof() == false)
    {
        if (text == "FrameSize")
        {
            in_file >> frame_size.x;
            in_file >> frame_size.y;
        }
        else if (text == "NumFrames")
        {
            int frame_count;
            in_file >> frame_count;
            for (int i = 0; i < frame_count; i++)
            {
                frame_texels.push_back({ frame_size.x * i, 0 });
            }
        }
        else if (text == "Frame")
        {
            int frame_location_x, frame_location_y;
            in_file >> frame_location_x;
            in_file >> frame_location_y;
            frame_texels.push_back({ frame_location_x, frame_location_y });
        }
        else if (text == "HotSpot")
        {
            int hotspot_x, hotspot_y;
            in_file >> hotspot_x;
            in_file >> hotspot_y;
            hotspots.push_back({ hotspot_x, hotspot_y });
        }
        else if (text == "Anim")
        {
            std::string animation_path;
            in_file >> animation_path;
            animations.push_back(new Animation(animation_path));
        }
        else if (text == "RectCollision")
        {
            Math::irect boundary;
            in_file >> boundary.point1.x >> boundary.point1.y >> boundary.point2.x >> boundary.point2.y;
            if (object == nullptr)
            {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else
            {
                object->AddGOComponent(new RectCollision(boundary, object));
            }
        }
        else if (text == "CircleCollision")
        {
            float radius;
            in_file >> radius;

            if (object == nullptr)
            {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else
            {
                object->AddGOComponent(new CircleCollision(radius, object));
            }
        }
        else
        {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
    if (frame_texels.empty() == true)
    {
        frame_texels.push_back({ 0,0 });
    }

    if (animations.empty())
    {
        animations.push_back(new Animation());
        PlayAnimation(0);
    }
}




void GAM200::Sprite::Update(double dt)
{
    animations[current_animation]->Update(dt);
}



Math::ivec2 GAM200::Sprite::GetHotSpot(int index)
{
    if (index < 0 || index >= hotspots.size())
    {
        return Math::ivec2(0, 0);
    }
    return hotspots[index];
}


Math::ivec2 GAM200::Sprite::GetFrameSize()
{
    return frame_size;
}


void GAM200::Sprite::PlayAnimation(int animation)
{
    if (animation < 0 || animation >= animations.size())
    {
        Engine::Instance().GetLogger().LogError("The animation doesn't exist!");
        current_animation = 0;
        return;
    }

    current_animation = animation;
    animations[current_animation]->Reset();
}



bool GAM200::Sprite::AnimationEnded()
{
    if (animations[current_animation]->Ended())
    {
        return true;
    }

    return false;
}

int GAM200::Sprite::CurrentAnimation()
{
    return current_animation;
}


Math::ivec2 GAM200::Sprite::GetFrameTexel(int index) const
{
    if (index < 0 || index >= frame_texels.size())
    {
        Engine::Instance().GetLogger().LogError("The index is not valid!");
        return { 0, 0 };
    }
    return frame_texels[index];
}




void GAM200::Sprite::Draw(Math::TransformationMatrix display_matrix)
{
    int current_frame = animations[current_animation]->CurrentFrame();
    Math::ivec2 hotspot = GetHotSpot(0); 
    texture->Draw(display_matrix * Math::TranslationMatrix(-hotspot), GetFrameTexel(current_frame), GetFrameSize());
}






