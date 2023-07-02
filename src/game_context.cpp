#include "game_context.hpp"

GameContext::GameContext() {
    gameMap.reset(new Map(MapDesc, {MapWidth, MapHeight}));

    auto& ctx = Context::Inst();
    auto tilesheet = ctx.GetTextureManager().FindTilesheet(TilesheetName);
    monsters.emplace_back(
        tilesheet->Get(static_cast<int>(ImageTileType::Pacman), 0),
        // FIXME: remove this magic number
        Vector2(48, 32)
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
}

void GameContext::Update() {
    for (auto& monster : monsters) {
        monster.Update();
    }

    for (auto& monster : monsters) {
        dealCollideWithMap(monster);
    }
}
