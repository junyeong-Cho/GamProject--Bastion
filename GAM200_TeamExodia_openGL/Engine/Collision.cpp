/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.cpp
Project:    GAM200 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#include "GameObjectManager.h"
#include "GameStateManager.h"

#include "Collision.h"
#include "GameObject.h"


GAM200::RectCollision::RectCollision(Math::irect boundary, GameObject* object) :
    boundary(boundary),
    object(object)
{ }


bool GAM200::RectCollision::IsCollidingWith(Math::vec2 point)
{
    Math::rect rectangle = WorldBoundary();

    if (point.x >= rectangle.Left() && point.x <= rectangle.Right() &&
        point.y >= rectangle.Bottom() && point.y <= rectangle.Top())
    {
        return true;
    }
    return false;
}

bool GAM200::RectCollision::IsCollidingWith(GameObject* other_object)
{
    Collision* other_collider = other_object->GetGOComponent<Collision>();


    if (other_collider == nullptr)
    {
        return false;
    }


    if (other_collider->Shape() != CollisionShape::Rect)
    {
        Engine::GetLogger().LogError("Rect vs unsupported type");
        return false;
    }


    Math::rect rectangle_1 = WorldBoundary();
    Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();


    Engine::GetLogger().LogDebug("Rec1: " + std::to_string(rectangle_1.Left()) + " " + std::to_string(rectangle_1.Bottom()) + " " + std::to_string(rectangle_1.Right()) + " " + std::to_string(rectangle_1.Top()));
    Engine::GetLogger().LogDebug("Rec2: " + std::to_string(rectangle_2.Left()) + " " + std::to_string(rectangle_2.Bottom()) + " " + std::to_string(rectangle_2.Right()) + " " + std::to_string(rectangle_2.Top()) + "\n");

    /* AABB check between rectangle_1 and rectangle_2 */
    if (rectangle_1.Right() > rectangle_2.Left() &&
        rectangle_1.Left() < rectangle_2.Right() &&
        rectangle_1.Bottom() < rectangle_2.Top() &&
        rectangle_1.Top() > rectangle_2.Bottom())
    {
        Engine::GetLogger().LogEvent("Returned true!\n");
        return true;
    }
    return false;
}




Math::rect GAM200::RectCollision::WorldBoundary()
{

    /*Engine::GetLogger().LogDebug(
        "\nMatrix: \n" +
        std::to_string(object->GetMatrix()[0][0]) + ", " + std::to_string(object->GetMatrix()[0][1]) + ", " + std::to_string(object->GetMatrix()[0][2]) + "\n" +
        std::to_string(object->GetMatrix()[1][0]) + ", " + std::to_string(object->GetMatrix()[1][1]) + ", " + std::to_string(object->GetMatrix()[1][2]) + "\n" +
        std::to_string(object->GetMatrix()[2][0]) + ", " + std::to_string(object->GetMatrix()[2][1]) + ", " + std::to_string(object->GetMatrix()[2][2]) + "\n" +
        "Boundary: " + std::to_string(boundary.point1.x) + ", " + std::to_string(boundary.point1.y) + ", " + std::to_string(boundary.point2.x) + ", " + std::to_string(boundary.point2.y) + "\n"
    );*/
    return
    {
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point1),
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point2)
    };
    //return { static_cast<Math::vec2>(boundary.point1) , static_cast<Math::vec2>(boundary.point2) };
}


void GAM200::RectCollision::Draw(Math::TransformationMatrix display_matrix)
{
    /*doodle::no_fill();

    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    Math::rect world_boundary = WorldBoundary();
    doodle::apply_matrix(display_matrix[0][0], display_matrix[1][0], display_matrix[0][1], display_matrix[1][1], display_matrix[0][2], display_matrix[1][2]);
    doodle::draw_rectangle(world_boundary.Left(), world_boundary.Bottom(), world_boundary.Size().x, world_boundary.Size().y);

    doodle::pop_settings();*/
}


//GAM200::CircleCollision::CircleCollision(double radius, GAM200::GameObject* object) :
//    radius(radius),
//    object(object)
//{ }

//bool GAM200::CircleCollision::IsCollidingWith(Math::vec2 point)
//{
//    Math::vec2 circle_center = object->GetPosition();
//    double circle_radius = GetRadius();
//
//    Math::vec2 distance = point - circle_center;
//    double distanceSquared = distance.x * distance.x + distance.y * distance.y;
//    double radiusSquared = circle_radius * circle_radius;
//
//    if (distanceSquared <= radiusSquared)
//    {
//        return true;
//    }
//
//    return false;
//}

//bool GAM200::CircleCollision::IsCollidingWith(GameObject* other_object)
//{
//    Collision* other_collider = other_object->GetGOComponent<Collision>();
//
//    if (other_collider == nullptr)
//    {
//        return false;
//    }
//
//    if (other_collider->Shape() != CollisionShape::Circle)
//    {
//        //Engine::GetLogger().LogError("Rect vs unsupported type");
//        return false;
//    }
//
//    // Calculate the squared distance between the two circles
//    Math::vec2 circle_1 = object->GetPosition();
//    Math::vec2 circle_2 = dynamic_cast<CircleCollision*>(other_collider)->object->GetPosition();
//
//    double distance_squared = pow(circle_1.x - circle_2.x, 2) + pow(circle_1.y - circle_2.y, 2);
//
//    // Calculate the squared sum of the radii
//    double radius_sum_squared = pow(radius + dynamic_cast<CircleCollision*>(other_collider)->radius, 2);
//
//    // Check if the two circles are colliding
//    if (distance_squared < radius_sum_squared)
//    {
//        return true;
//    }
//
//    return false;
//}



//void GAM200::CircleCollision::Draw(Math::TransformationMatrix display_matrix)
//{
//    /*doodle::no_fill();
//    doodle::set_outline_width(2);
//    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
//    doodle::push_settings();
//    doodle::apply_matrix(display_matrix[0][0], display_matrix[1][0], display_matrix[0][1], display_matrix[1][1], display_matrix[0][2], display_matrix[1][2]);
//    doodle::draw_ellipse(object->GetPosition().x, object->GetPosition().y, GetRadius() * 2);
//    doodle::pop_settings();*/
//}

// CircleCollision::GetRadius() . Do not forget to consider the scale matrix!
//double GAM200::CircleCollision::GetRadius()
//{
//    /*Math::ScaleMatrix scale_matrix = object->GetScale();
//    Math::vec2 scale = { scale_matrix[0][0], scale_matrix[1][1] };
//
//    return radius * std::max(scale.x, scale.y);*/
//    
//}