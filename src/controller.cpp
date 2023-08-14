#include "controller.hpp"

void Controller::moveUp() {
    monster_.dir = Monster::Direction::Up;
}

void Controller::moveDown() {
    monster_.dir = Monster::Direction::Down;
}

void Controller::moveRight() {
    monster_.dir = Monster::Direction::Right;
}

void Controller::moveLeft() {
    monster_.dir = Monster::Direction::Left;
}

void Controller::HandleEvent(const SDL_Event& event) {
    auto position = monster_.GetPosition();
    if (event.type == SDL_KEYDOWN) {
        auto key = event.key.keysym.scancode;
        acceptKey(key);
        
    }
}

void Controller::Update() {
    if (keyRemainsTime_ > 0) {
        keyRemainsTime_ --;
    }

    auto position = monster_.GetPosition();
    auto offsetedPos = position;
    if (int(offsetedPos.x) % 32 == 0 && int(offsetedPos.y) % 32 == 0) {
        auto key = consume();
        if (key == SDL_SCANCODE_A) {
            moveLeft();
        }
        if (key == SDL_SCANCODE_D) {
            moveRight();
        }
        if (key == SDL_SCANCODE_W) {
            moveUp();
        }
        if (key == SDL_SCANCODE_S) {
            moveDown();
        }
    }
}