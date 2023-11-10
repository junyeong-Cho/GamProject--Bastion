#pragma once

#include "../Engine/GameObjectManager.h"
#include "../Engine/Matrix.h"
#include "../Game/GameObjectTypes.h"

class Bullet : public GAM200::GameObject {
public:
    Bullet(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Bullet; }
    std::string TypeName() override { return "Bullet"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 600;

    static int GetDamage() { return damage; }

protected:
    int size = 10;

    static constexpr int damage = 1;

    struct Color {
        float r;
        float g;
        float b;
    } color;
};