#include "find_path.hpp"

// FIXME: can't work
bool FindShortestPath(Matrix<VisitRecord>& recordMap,
                      Map& gameMap,
                      const Vector2& prevGrid,
                      const Vector2& currentGrid,
                      const Vector2& targetGrid) {
    if (recordMap.Get(currentGrid.x, currentGrid.y).prev == Vector2{-1, -1}) {
        auto& tile = recordMap.Get(currentGrid.x, currentGrid.y);
        tile.prev = prevGrid;
    }

    if (currentGrid == targetGrid) {
        recordMap.Get(currentGrid.x, currentGrid.y).count = recordMap.Get(prevGrid.x, prevGrid.y).count + 1;
        return true;
    }

    static std::array<Vector2, 4> directions = {
        Vector2{-1, 0},
        Vector2{1, 0},
        Vector2{0, 1},
        Vector2{0, -1},
    };

    bool found = false;

    bool hasSearched = false;
    for (const auto& dir : directions) {
        Vector2 newPos = currentGrid + dir;
        auto current = recordMap.Get(newPos.x, newPos.y);
        if (CanWalk(gameMap.GetTile(newPos.x, newPos.y).type)) {
            if (hasSearched) {
                int newCount = (prevGrid == Vector2{-1, -1} ? 0 : recordMap.Get(prevGrid.x, prevGrid.y).count) + 1;
                Vector2 pos = currentGrid;
                if (newCount < current.count) {
                    recordMap.Get(currentGrid.x, currentGrid.y).count = newCount;
                    recordMap.Get(newPos.x, newPos.y).prev = currentGrid;

                    found = found || current.canReach;
                } else {
                    found = found || false;
                }
            } else {
                hasSearched = true;
                recordMap.Get(currentGrid.x, currentGrid.y).count = (prevGrid == Vector2{-1, -1} ? 0 : recordMap.Get(prevGrid.x, prevGrid.y).count) + 1;
                bool found2 = FindShortestPath(recordMap, gameMap, currentGrid, newPos, targetGrid);
                found = found || found2;
                recordMap.Get(currentGrid.x, currentGrid.y).canReach = found;
            }
        }
    }
    return found;
}