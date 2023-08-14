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

    /* Test codes for path finding
    Matrix<VisitRecord> recordMap(gameMap->Width(), gameMap->Height());
    auto startGrid = Vector2(1, 1);
    // auto targetGrid = Vector2(7, 9);
    auto targetGrid = Vector2(1, 5);

    if (FindShortestPath(recordMap, *gameMap, Vector2{-1, -1}, startGrid, targetGrid)) {
        // std::cout << recordMap.Get(targetGrid.x, targetGrid.y).count << std::endl;
        // std::cout << recordMap.Get(startGrid.x, startGrid.y).count << std::endl;
        Vector2 pos = targetGrid;
        while (pos != targetGrid) {
            auto& renderer = Context::Inst().GetRenderer();
            renderer.SetColor({0, 255, 0, 255});
            renderer.DrawRect({int(pos.x * 32), int(pos.y * 32), 16, 16});

            pos = recordMap.Get(pos.x, pos.y).prev;
        }
    }
    */
}
