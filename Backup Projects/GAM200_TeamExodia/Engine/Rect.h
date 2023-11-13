/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Rect.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March      8, 2023
Updated:    September 26, 2023
*/

#pragma once

#include <algorithm>

#include "Vec2.h"


namespace Math
{
    struct [[nodiscard]] rect
    {
        Math::vec2 point1{ 0.0, 0.0 };
        Math::vec2 point2{ 0.0, 0.0 };

        double Left() const noexcept
        {
            return std::min(point1.x, point2.x);
        }

        double Right() const noexcept
        {
            return std::max(point1.x, point2.x);
        }

        double Top() const noexcept
        {
            return std::max(point1.y, point2.y);
        }

        double Bottom() const noexcept
        {
            return std::min(point1.y, point2.y);
        }


        vec2 Size() const noexcept
        {
            return
            {
                (Right() - Left()),
                (Top() - Bottom())
            };
        }
    };

    struct [[nodiscard]] irect
    {
        Math::ivec2 point1{ 0, 0 };
        Math::ivec2 point2{ 0, 0 };

        int Left() const noexcept
        {
            return std::min(point1.x, point2.x);
        }

        int Right() const noexcept
        {
            return std::max(point1.x, point2.x);
        }

        int Top() const noexcept
        {
            return std::max(point1.y, point2.y);
        }

        int Bottom() const noexcept
        {
            return std::min(point1.y, point2.y);
        }

        ivec2 Size() const noexcept
        {
            return
            {
                Right() - Left(),
                std::abs(Top() - Bottom())
            };
        }
    };
}

