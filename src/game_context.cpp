#include "game_context.hpp"

GameContext::GameContext() {
    gameMap.reset(new Map(MapDesc, {MapWidth, MapHeight}));

    auto& ctx = Context::Inst();
    auto tilesheet = ctx.GetTextureManager().FindTilesheet(TilesheetName);
    monsters.emplace_back(
        tilesheet->Get(static_cast<int>(ImageTileType::Pacman), 0),
        // FIXME: remove this magic number
        Vector2(32, 32)
    );

    controller.reset(new Controller(monsters[0]));
}

void GameContext::dealCollideWithMap(Monster& monster) {
    // FIXME remove this magic number
    Rect monsterRect(monster.GetPosition(), {32, 32});

    for (int y = 0; y < gameMap->Height(); y++) {
        for (int x = 0; x < gameMap->Width(); x++) {
            Rect tileRect(Vector2(x * 32, y * 32), {32, 32});
            if (gameMap->GetTile(x, y).type == Tile::Type::Wall && tileRect.IsIntersect(monsterRect)) {
                auto monsterCenter = monsterRect.Center();  
                auto tileCenter = tileRect.Center();
                auto dir = monsterCenter - tileCenter;
                auto maxIntersectV = (monsterRect.size + tileRect.size) / 2.0;
                auto intersectDepth = maxIntersectV - Vector2{std::abs(dir.x), std::abs(dir.y)};
                auto seperate = (-monster.GetVelocity()).Normalize() * intersectDepth;
                monster.Move(seperate);
                monsterRect = Rect(monster.GetPosition(), {32, 32});
            }
        }
    }

    tryEatBean(monster.GetPosition());
}

void GameContext::tryEatBean(const Vector2& playerPosition) {
    if (int(playerPosition.x) % 32 == 0 && int(playerPosition.y) % 32 == 0) {
        auto grid = playerPosition / 32;
        auto& tile = gameMap->GetTile(int(grid.x), int(grid.y));
        if (tile.type == Tile::Type::Bean) {
            tile.type = Tile::Type::Emtpy;
            score_ ++;
            std::cout << "new Score: " << score_ << std::endl;
        }
    }
}

void GameContext::Update() {
    controller->Update();

    for (auto& monster : monsters) {
        monster.Update();
    }

    for (auto& monster : monsters) {
        dealCollideWithMap(monster);
    }

    //  Test codes for path finding
    Matrix<VisitRecord> recordMap(gameMap->Width(), gameMap->Height());
    auto startGrid = Vector2(1, 1);
    recordMap.Get(startGrid.x, startGrid.y).visited = true;
    auto targetGrid = Vector2(6, 9);
    // auto targetGrid = Vector2(1, 5);
    int count = 114514;
    static std::vector<Vector2> path;
    static auto find = false;

    if (!find) {
        find = FindShortestPath(recordMap, *gameMap, Vector2{-1, -1}, startGrid,
                                targetGrid, count, path);
        // std::cout << "path.size = " << path.size() << std::endl;
        // for (auto& grid : path) {
        //     std::cout << grid.x << ", " << grid.y << std::endl;
        // }
    } else {
        auto& renderer = Context::Inst().GetRenderer();
        renderer.SetColor({0, 255, 0, 255});
        for (auto& grid : path) {
            // ! DrawRect可能不会生效，因为main中先update在draw，会被覆盖
            // ! 这里能显示部分路径恰好是因为豆子有部分地方没有颜色
            renderer.DrawRect({int(grid.x * 32), int(grid.y * 32), 16, 16});
        }
    }
}
