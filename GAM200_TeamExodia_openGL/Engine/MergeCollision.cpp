/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    March 8,  2023
Updated:    November 06, 2023
*/


#include "MergeCollision.h"

#include "GameObjectManager.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "DrawShape.h"




GAM200::MergeCircleCollision::MergeCircleCollision(double radius, GAM200::GameObject* object) :
    radius(radius),
    object(object)
{ }

bool GAM200::MergeCircleCollision::IsMergingWith(Math::vec2 point)
{
    Math::vec2 circle_center = object->GetPosition();
    double circle_radius = GetRadius();

    Math::vec2 distance = point - circle_center;
    double distanceSquared = distance.x * distance.x + distance.y * distance.y;
    double radiusSquared = circle_radius * circle_radius;

    if (distanceSquared <= radiusSquared)
    {
        return true;
    }

    return false;
}

bool GAM200::MergeCircleCollision::IsMergingWith(GameObject* other_object)
{
    if (other_object == nullptr)
        return false;

    MergeCollision* other_collider = other_object->GetGOComponent<MergeCollision>();

    if (other_collider == nullptr)
    {
        return false;
    }

    // Calculate the squared distance between the two circles
    Math::vec2 circle_1 = object->GetPosition();
    Math::vec2 circle_2 = dynamic_cast<MergeCircleCollision*>(other_collider)->object->GetPosition();

    double distance_squared = pow(circle_1.x - circle_2.x, 2) + pow(circle_1.y - circle_2.y, 2);

    // Calculate the squared sum of the radii
    double radius_sum_squared = pow(radius + dynamic_cast<MergeCircleCollision*>(other_collider)->radius, 2);

    // Check if the two circles are colliding
    if (distance_squared < radius_sum_squared)
    {
        return true;
    }

    return false;
}



void GAM200::MergeCircleCollision::Draw(Math::TransformationMatrix display_matrix)
{
    DrawShape draw_shape;
    draw_shape.SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // White color
    draw_shape.SetLineWidth(50);

    glPushMatrix();
    glMultMatrixd(&(display_matrix[0][0]));
    draw_shape.DrawCircle((int)object->GetPosition().x, (int)object->GetPosition().y, (int)GetRadius(), 100);
    glPopMatrix();
}

// CircleCollision::GetRadius() . Do not forget to consider the scale matrix!
double GAM200::MergeCircleCollision::GetRadius()
{
    Math::ScaleMatrix scale_matrix = object->GetScale();
    Math::vec2 scale = { scale_matrix[0][0], scale_matrix[1][1] };
    return radius * std::max(scale.x, scale.y);
}

