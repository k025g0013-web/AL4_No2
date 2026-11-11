#pragma once
#include <functional>
#include <utility>

class IScene {
public:
    // シーンの種類
    enum class SceneType {
        kTitle,
        kGame,
        kGameOver,
        kClear,
    };

public:
    virtual ~IScene() = default;

    // 初期化
    virtual void Initialize() = 0;

    // 更新
    virtual void Update() = 0;

    // 描画
    virtual void Draw() = 0;

    // 遷移要求用コールバックを設定
    void SetSceneChangeCallback(std::function<void(SceneType)> callback) {
        sceneChangeCallback_ = std::move(callback);
    }

protected:
    // シーン遷移を要求
    void RequestSceneChange(SceneType nextScene) {
        if (sceneChangeCallback_) {
            sceneChangeCallback_(nextScene);
        }
    }

private:
    // シーン遷移要求用コールバック
    std::function<void(SceneType)> sceneChangeCallback_;
};