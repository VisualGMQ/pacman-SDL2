#include "pch.hpp"
#include "context.hpp"
#include "game_context.hpp"
#include "consts.hpp"

void Startup() {
    Context::Init("Pacman", Vector2{720, 600});

    auto& ctx = Context::Inst();
    auto& textureMgr = ctx.GetTextureManager();
    textureMgr.LoadTilesheet(TilesheetName, "./resources/tilesheet.bmp", KeyColor, TilesheetCol, TilesheetRow);

    GameContext::Init();
}

void Shutdown() {
    GameContext::Quit();
    Context::Quit();
}

void Update() {
    auto& gameCtx = GameContext::Inst();
    gameCtx.Update();
}

void Draw() {
    auto& ctx = Context::Inst();
    auto& gameCtx = GameContext::Inst();
    auto& textureMgr = ctx.GetTextureManager();
    auto& renderer = ctx.GetRenderer();
    auto* tilesheet = textureMgr.FindTilesheet("tilesheet");
    if (!tilesheet) {
        SDL_Log("[FatalError]: can't find tilesheet");
    }

    gameCtx.gameMap->Draw();
    for (auto& monster : gameCtx.monsters) {
        monster.Draw();
    }
}

void Run() {
    auto& gameCtx = GameContext::Inst();
    auto& event = gameCtx.GetEvent();
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameCtx.Exit();
        }
        gameCtx.HandleEvent();
    }

    auto& renderer = Context::Inst().GetRenderer();
    renderer.SetColor(SDL_Color{0, 0, 0, 255});
    renderer.Clear();
    Update();
    Draw();
    renderer.Present();
    SDL_Delay(30);
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    Startup();

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
    emscripten_set_main_loop(Run, 0, 1);
#else
    while(!GameContext::Inst().ShouldClose()) {
        Run();
    }
#endif

    Shutdown();
    SDL_Quit();

    return 0;
}