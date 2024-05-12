
#pragma once

#include "../Engine/Component.h"
#include "../Engine/Matrix.h"

#include "Rect.h"
#include "Vec2.h"

namespace GAM200
{
    class Camera : public Component
    {
    public:
        Camera(Math::rect player_zone);

        void                       SetPosition(Math::vec2 new_position);
        const Math::vec2&          GetPosition() const;
        Math::TransformationMatrix& GetMatrix();

        void SetLimit(Math::irect new_limit);
        void Update(const Math::vec2& player_position);

        void UpdatePosition(Math::vec2 delta);
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);

    private:
        Math::irect limit;
        Math::vec2  position;
        Math::rect  player_zone;
        Math::vec2  scale;

        Math::TransformationMatrix object_matrix;

        bool matrix_outdated;
    };
}
