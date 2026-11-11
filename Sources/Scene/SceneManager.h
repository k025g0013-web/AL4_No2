#pragma once

#include "IScene.h"

#include <memory>
#include <optional>

class WipeManager;

class SceneManager {
public:
    enum class TransitionState {
        kNone,      // 通常
        kFadeOut,   // フェードアウト
        kFadeIn,    // フェードイン
    };

public:
    SceneManager() = default;
    ~SceneManager() = default;

    // 初期化
    void Initialize(IScene::SceneType initialScene = IScene::SceneType::kTitle);
    // 更新
    void Update();
    // 描画
    void Draw();

    // ゲーム終了要求
    void Quit();

    // ゲーム終了判定
    bool IsQuitRequested() const { return isQuit_; }

private:
    // シーン生成
    std::unique_ptr<IScene> CreateScene(IScene::SceneType type);

    // シーン切り替え
    void ChangeScene(IScene::SceneType type);

    // シーン遷移処理
    void CheckSceneChange();

    // 遷移処理
    void UpdateTransition();

private:
    // 現在のシーン
    std::unique_ptr<IScene> scene_;

    // 遷移先のシーン
    std::optional<IScene::SceneType> nextScene_;

    // 遷移フェーズ
    TransitionState transitionPhase_ = TransitionState::kNone;

    // ゲーム終了フラグ
    bool isQuit_ = false;

    // ワイプ管理
    WipeManager *wipeManager_ = nullptr;
};