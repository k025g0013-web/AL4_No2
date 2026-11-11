#pragma once

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

    // シーン遷移要求があるか
    bool IsSceneChangeRequested() const {
        return isSceneChangeRequested_;
    }

    // 遷移先を取得
    SceneType GetNextScene() const {
        return nextScene_;
    }

protected:
    // シーン遷移を要求
    void RequestSceneChange(SceneType nextScene) {
        nextScene_ = nextScene;
        isSceneChangeRequested_ = true;
    }

private:
    // 遷移先
    SceneType nextScene_ = SceneType::kTitle;

    // シーン遷移要求フラグ
    bool isSceneChangeRequested_ = false;
};