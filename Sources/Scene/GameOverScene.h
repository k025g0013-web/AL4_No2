#pragma once
#include "KamataEngine.h"
#include "IScene.h"

#include <memory>

class GameOverScene : public IScene {
public:
    GameOverScene() = default;
    ~GameOverScene() override = default;

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

private:
    // ゲームオーバー画面の初期化
    void InitializeObjects();

    // 入力処理
    void HandleInput();

private:
};