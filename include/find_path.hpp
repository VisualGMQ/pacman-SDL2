#pragma once

#include "map.hpp"
#include <queue>

struct VisitRecord {
    Vector2 prev = {-1, -1};
    int count = 0;
    bool canReach = false;
};

bool FindShortestPath(Matrix<VisitRecord>& recordMap,
                      Map& gameMap,
                      const Vector2& prevGrid,
                      const Vector2& currentGrid,
                      const Vector2& targetGrid);