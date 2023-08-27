#pragma once

#include <queue>
#include <vector>

#include "map.hpp"

struct VisitRecord {
    Vector2 prev = {-1, -1};
    int count = 0;
    bool visited = false;
};

bool FindShortestPath(Matrix<VisitRecord>& recordMap, Map& gameMap,
                      const Vector2& prevGrid, const Vector2& currentGrid,
                      const Vector2& targetGrid, int& count,
                      std::vector<Vector2>& path);