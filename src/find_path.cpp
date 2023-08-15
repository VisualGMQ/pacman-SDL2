#include "find_path.hpp"

// Shopkeeper修改:
// 基于DFS的最短路径搜索，额外增加了count(记录最短路径长度)和path(记录路径，DFS会不断改变VisitRecord的内容)
// 还修改了VisitRecord的数据结构不需要canReach，修改为visited
// 话说真的不用BFS么，你都#include <queue>了，DFS求最短路径性能好差
bool FindShortestPath(Matrix<VisitRecord>& recordMap, Map& gameMap,
                      const Vector2& prevGrid, const Vector2& currentGrid,
                      const Vector2& targetGrid, int& count,
                      std::vector<Vector2>& path) {
    static std::array<Vector2, 4> directions = {
        Vector2{-1, 0},
        Vector2{1, 0},
        Vector2{0, 1},
        Vector2{0, -1},
    };

    // std::cout << currentGrid.x << ", " << currentGrid.y;

    bool found = false;

    // 对自己进行更新
    if (CanWalk(gameMap.GetTile(currentGrid.x, currentGrid.y).type)) {
        // std::cout << " can walk" << std::endl;
        auto& currentRecord = recordMap.Get(currentGrid.x, currentGrid.y);
        currentRecord.count =
            (prevGrid == Vector2{-1, -1}
                 ? 0
                 : (recordMap.Get(prevGrid.x, prevGrid.y).count + 1));
        if (currentRecord.count > count) {
            // 剪枝，大于或者大于等于都可以
            return false;
        }
        if (currentGrid == targetGrid) {
            if (currentRecord.count < count) {
                count = currentRecord.count;  // 将路径拷贝到path中
                // ! 注意路径是从终点到起点的
                path.clear();
                path.push_back(currentGrid);
                auto& nowRecord = currentRecord;
                while (nowRecord.prev != Vector2{-1, -1}) {
                    path.push_back(nowRecord.prev);
                    nowRecord =
                        recordMap.Get(nowRecord.prev.x, nowRecord.prev.y);
                }
                return true;
            } else {
                return false;
            }
        }
        for (const auto& dir : directions) {
            Vector2 newPos = currentGrid + dir;
            // std::cout << currentGrid.x << ", " << currentGrid.y
            //           << " try to go to " << newPos.x << ", " << newPos.y
            //           << std::endl;
            auto& newRecord = recordMap.Get(newPos.x, newPos.y);
            if (!newRecord.visited) {
                // std::cout << newPos.x << ", " << newPos.y << " not visited"
                //           << std::endl;
                newRecord.visited = true;
                newRecord.prev = currentGrid;
                // ! (|| found) 需要放在后面，不然找到一次之后就不会再找了
                found = FindShortestPath(recordMap, gameMap, currentGrid,
                                         newPos, targetGrid, count, path) ||
                        found;
                newRecord.visited = false;
            }
            // else {
            //     std::cout << newPos.x << ", " << newPos.y << " visited"
            //               << std::endl;
            // }
        }
    } else {
        // std::cout << " can not walk" << std::endl;
        return false;
    }

    return found;
}