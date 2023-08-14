#pragma once

#include "monster.hpp"

class Controller final {
public:
    Controller(Monster& monster): monster_(monster) {}

    void HandleEvent(const SDL_Event&);
    void Update();

private:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void acceptKey(SDL_Scancode key) {
        key_ = key;
        keyRemainsTime_ = invalidTime_;
    }

    SDL_Scancode consume() {
        if (keyRemainsTime_ <= 0) {
            key_ = SDL_SCANCODE_UNKNOWN;
            return SDL_SCANCODE_UNKNOWN;
        }
        auto key = key_;
        key_ = SDL_SCANCODE_UNKNOWN;
        keyRemainsTime_ = 0;
        return key;
    }

    Monster& monster_;

    SDL_Scancode key_;
    const int invalidTime_ = 10;
    int keyRemainsTime_ = invalidTime_;
};