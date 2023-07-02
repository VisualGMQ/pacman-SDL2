#pragma once

template <typename T>
class Singlton {
public:
    virtual ~Singlton() = default;

    template <typename... Args>
    static void Init(Args&&... args) {
        if (!instance_) {
            instance_.reset(new T(std::forward<Args>(args)...));
        } else {
            SDL_Log("[Singlton]: repeat init singlton");
        }
    }

    Singlton() = default;
    Singlton(const Singlton&) = delete;
    Singlton& operator=(const Singlton&) = delete;

    static void Quit() { instance_.reset(); }
    static auto& Inst() { return *instance_; }

private:
    inline static std::unique_ptr<T> instance_;
};