#pragma once
#include "window.hpp"
#include "renderer.hpp"
#include "texture.hpp"

class Context final: public Singlton<Context> {
public:
    // static void Init(const std::string& title, const Vector2& windowSize);

    Context(const std::string& title, const Size& windowSize);

    auto& GetRenderer() { return *renderer_; }
    auto& GetTextureManager() { return *textureMgr_; }

private:
    std::unique_ptr<Window> window_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<TextureManager> textureMgr_;

    static std::unique_ptr<Context> instance_;
};