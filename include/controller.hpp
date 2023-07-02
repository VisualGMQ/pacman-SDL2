#pragma once

#include "monster.hpp"

class Controller final {
public:
    Controller(Monster& monster): monster_(monster) {}

    void HandleEvent(const SDL_Event&);

private:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    Monster& monster_;
};