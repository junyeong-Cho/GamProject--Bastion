
#include "Camera.h"

GAM200::Camera::Camera(Math::rect player_zone) : player_zone(player_zone), position({ 0, 0 }), matrix_outdated(true), scale({1, 1})
{
}

void GAM200::Camera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& GAM200::Camera::GetPosition() const
{
    return position;
}

Math::TransformationMatrix& GAM200::Camera::GetMatrix()
{
    if (matrix_outdated)
    {
        object_matrix   = Math::TranslationMatrix(position) * Math::ScaleMatrix(scale);
        matrix_outdated = false;
    }
    return object_matrix;
    /*return Math::TranslationMatrix(-position);*/
}

void GAM200::Camera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

void GAM200::Camera::UpdatePosition(Math::vec2 delta)
{
    position += delta;
    matrix_outdated = true;
}

void GAM200::Camera::SetScale(Math::vec2 new_scale)
{
    scale           = new_scale;
    matrix_outdated = true;
}

void GAM200::Camera::UpdateScale(Math::vec2 delta)
{
    scale += delta;
    matrix_outdated = true;
}

void GAM200::Camera::Update(const Math::vec2& player_position)
{
    if (player_position.x > player_zone.Right() + position.x)
    {
        position.x = player_position.x - player_zone.Right();
    }
    if (player_position.x - position.x < player_zone.Left())
    {
        position.x = player_position.x - player_zone.Left();
    }

    if (position.x < limit.Left())
    {
        position.x = limit.Left();
    }
    if (position.x > limit.Right())
    {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom())
    {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top())
    {
        position.y = limit.Top();
    }
}