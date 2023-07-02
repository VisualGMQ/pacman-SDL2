#include "context.hpp"

std::unique_ptr<Context> Context::instance_;

Context::Context(const std::string& title, const Size& windowSize) {
    window_.reset(new Window(title,
                             static_cast<int>(windowSize.x),
                             static_cast<int>(windowSize.y)));
    renderer_.reset(new Renderer(*window_));
    textureMgr_.reset(new TextureManager(renderer_.get()));
}