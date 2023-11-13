



#include "Bullet.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

Bullet::Bullet(Math::vec2 pos, Math::vec2 vel) : GameObject(pos)
{
    SetVelocity(vel);
    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size, size} }, this)); 

    color = { 0.f, 0.f, 0.f };


    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

void Bullet::Update(double dt)
{
    GameObject::Update(dt);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 position = GetPosition();
    
    if (position.x + size < -200 || position.x > window_size.x + 200 ||
        position.y + size < -200 || position.y > window_size.y + 200)
    {
        Destroy();
        RemoveGOComponent<GAM200::RectCollision>();
    }

    // Check if the laser is outside of the window

    /*Math::ivec2 frame_size = GetGOComponent<CS230::Sprite>()->GetFrameSize();
    if (GetPosition().x < -frame_size.x || GetPosition().x > 800 + frame_size.x ||
        GetPosition().y < -frame_size.y || GetPosition().y > 600 + frame_size.y)
    {
        Destroy();
    }*/
}

bool Bullet::CanCollideWith(GameObjectTypes other_object_type)
{
    if (other_object_type == GameObjectTypes::Monster ||
        other_object_type == GameObjectTypes::Basic_Monster ||
        other_object_type == GameObjectTypes::Fast_Monster ||
        other_object_type == GameObjectTypes::Slow_Monster ||
        other_object_type == GameObjectTypes::Weak_Monster

        )
        return true;
    else
        return false;
}

void Bullet::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
    RemoveGOComponent<GAM200::RectCollision>();
}

void Bullet::Draw(Math::TransformationMatrix camera_matrix) {
    GAM200::DrawShape bullet;

    bullet.SetColor(color.r, color.g, color.b, 1.0f);
    bullet.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size, size);
}