#pragma once
#include "pch.hpp"
#include "context.hpp"
#include "texture.hpp"
#include "consts.hpp"

struct Monster final {
    enum class Direction {
        Right= 0, Left, Up, Down,
    };

    Direction dir = Direction::Up;
    Image image;
    float speed = 4;

    void Move(const Vector2& offset) {
        offset_ = offset;
        position_ += offset;
    }

    auto& GetPosition() const { return position_; }
    auto& GetVelocity() const { return offset_; }

    Monster(const Image& image, const Vector2& position)
        : image(image), position_(position) {}

    void Draw();
    void Update();

private:
    Vector2 offset_;
    Vector2 position_;
};