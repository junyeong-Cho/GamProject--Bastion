/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once

#include <string>

#include "Vec2.h"
#include "Texture.h"
#include "Animation.h"
#include "Engine/GameObject.h"
#include "ComponentManager.h"
#include "Engine.h"


#include "Engine/Matrix.h"



namespace GAM200
{
    class GameObject;


    class Sprite : public Component
    {
    public:

        friend class GameObject;


        Sprite(const std::filesystem::path& sprite_file, GameObject* object);

        ~Sprite();

        void Update(double dt) override;

        void Load(const std::filesystem::path& sprite_file, GameObject* object);
        void Draw(Math::TransformationMatrix display_matrix);
        Math::ivec2 GetHotSpot(int index);
        Math::ivec2 GetFrameSize();

        void PlayAnimation(int animation);
        bool AnimationEnded();

        int CurrentAnimation();

    private:
        Math::ivec2 GetFrameTexel(int index) const;

        Texture* texture;
        std::vector<Math::ivec2> hotspots;

        int current_animation = 0;
        Math::ivec2 frame_size;
        std::vector<Math::ivec2> frame_texels;
        std::vector<Animation*> animations;
    };
}
