



#include "Bullet.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"


// Bullet class
Bullet::Bullet(Math::vec2 pos, Math::vec2 vel) : GameObject(pos)
{
    SetVelocity(vel);
    //AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size, size} }, this)); 

    color = { 0.f, 0.f, 0.f };


    //Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Bullet::Update(double dt)
{
    GameObject::Update(dt);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 position = GetPosition();
    
    if (position.x + size.x < -200 || position.x > window_size.x + 200 ||
        position.y + size.y < -200 || position.y > window_size.y + 200)
    {
        Destroy();
        RemoveGOComponent<GAM200::RectCollision>();
    }
}
void Bullet::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
    RemoveGOComponent<GAM200::RectCollision>();
}
void Bullet::Draw(Math::TransformationMatrix camera_matrix) {
    GAM200::DrawShape bullet;

    Engine::Instance().push();

    bullet.SetColor(color.r, color.g, color.b, 1.0f);
    bullet.DrawRectangle(static_cast<int>(GetPosition().x)-500, static_cast<int>(GetPosition().y)-120, size.x, size.y);

    Engine::Instance().pop();
}

// Constructors
Basic_Bullet::Basic_Bullet(Math::vec2 pos, Math::vec2 vel) : Bullet(pos, vel)
{
    SetVelocity(vel);
    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size.x, size.y} }, this));

    color = { 0.f, 0.f, 0.f };


    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Wide_Range_Bullet::Wide_Range_Bullet(Math::vec2 pos, Math::vec2 vel) : Bullet(pos, vel)
{
    SetVelocity(vel);

    if (vel.x == 0.0)
    {
        size.x = 240;
        size.y = 80;
    }
    else if (vel.y == 0.0)
    {
        size.x = 80;
        size.y = 240;
    }
    else
    {
        size.x = 20;
        size.y = 20;
        Engine::GetLogger().LogError("Push Bullet velocity error!");
    }

    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size.x, size.y} }, this));
    SetVelocity(Math::vec2{});
    color = { 0.f, 0.f, 0.f };


    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Pushing_Bullet::Pushing_Bullet(Math::vec2 pos, Math::vec2 vel) : Bullet(pos, vel)
{
    SetVelocity(vel);
    if (vel.x == 0.0)
    {
        size.x = 80;
        size.y = 10;
    }
    else if (vel.y == 0.0)
    {
        size.x = 10;
        size.y = 80;
    }
    else
    {
        size.x = 20;
        size.y = 20;
        Engine::GetLogger().LogError("Push Bullet velocity error!");
    }

    AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size.x, size.y} }, this));

    color = { 0.f, 0.f, 0.f };


    Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

// Updates
void Basic_Bullet::Update(double dt)
{
    GameObject::Update(dt);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 position = GetPosition();

    if (position.x + size.x < -200 || position.x > window_size.x + 200 ||
        position.y + size.y < -200 || position.y > window_size.y + 200)
    {
        Destroy();
        RemoveGOComponent<GAM200::RectCollision>();
    }
}
void Wide_Range_Bullet::Update(double dt)
{
    GameObject::Update(dt);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 position = GetPosition();

    if (position.x + size.x < -200 || position.x > window_size.x + 200 ||
        position.y + size.y < -200 || position.y > window_size.y + 200)
    {
        Destroy();
        RemoveGOComponent<GAM200::RectCollision>();
    }
}
void Pushing_Bullet::Update(double dt)
{
    GameObject::Update(dt);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    Math::vec2 position = GetPosition();

    if (position.x + size.x < -200 || position.x > window_size.x + 200 ||
        position.y + size.y < -200 || position.y > window_size.y + 200)
    {
        Destroy();
        RemoveGOComponent<GAM200::RectCollision>();
    }
}

// Can Collide With
bool Bullet::CanCollideWith(GameObjectTypes other_object_type)
{
    if (static_cast<int>(other_object_type) >= static_cast<int>(GameObjectTypes::Monster) &&
        static_cast<int>(other_object_type) <= static_cast<int>(GameObjectTypes::Monster_End))
        return true;
    else
        return false;
}
bool Basic_Bullet::CanCollideWith(GameObjectTypes other_object_type)
{
    if (static_cast<int>(other_object_type) >= static_cast<int>(GameObjectTypes::Monster) &&
        static_cast<int>(other_object_type) <= static_cast<int>(GameObjectTypes::Monster_End))
        return true;
    else
        return false;
}
bool Wide_Range_Bullet::CanCollideWith(GameObjectTypes other_object_type)
{
    if (static_cast<int>(other_object_type) >= static_cast<int>(GameObjectTypes::Monster) &&
        static_cast<int>(other_object_type) <= static_cast<int>(GameObjectTypes::Monster_End))
        return true;
    else
        return false;
}
bool Pushing_Bullet::CanCollideWith(GameObjectTypes other_object_type)
{
    if (static_cast<int>(other_object_type) >= static_cast<int>(GameObjectTypes::Monster) &&
        static_cast<int>(other_object_type) <= static_cast<int>(GameObjectTypes::Monster_End))
        return true;
    else
        return false;
}


// Resolve Collision
void Basic_Bullet::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
    RemoveGOComponent<GAM200::RectCollision>();
}
void Wide_Range_Bullet::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
    //RemoveGOComponent<GAM200::RectCollision>();
}
void Pushing_Bullet::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
    //RemoveGOComponent<GAM200::RectCollision>();
}


// Draw
void Basic_Bullet::Draw(Math::TransformationMatrix camera_matrix)//더블이랑 트리플은 어디에?
{
    GAM200::DrawShape bullet;

    Engine::Instance().push();

    bullet.SetColor(color.r, color.g, color.b, 1.0f);
    bullet.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), static_cast<int>(size.x), static_cast<int>(size.y));

    Engine::Instance().pop();
}
void Wide_Range_Bullet::Draw(Math::TransformationMatrix camera_matrix)
{
    GAM200::DrawShape bullet;

    Engine::Instance().push();

    bullet.SetColor(color.r, color.g, color.b, 1.0f);
    bullet.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), static_cast<int>(size.x), static_cast<int>(size.y));

    Engine::Instance().pop();
}
void Pushing_Bullet::Draw(Math::TransformationMatrix camera_matrix)
{
    GAM200::DrawShape bullet;

    Engine::Instance().push();

    bullet.SetColor(color.r, color.g, color.b, 1.0f);
    bullet.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), static_cast<int>(size.x), static_cast<int>(size.y));

    Engine::Instance().pop();
}