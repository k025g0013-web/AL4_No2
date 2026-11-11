#pragma once
#include "KamataEngine.h"
#include "IScene.h"

#include <memory>

class GameScene : public IScene {
public:
    GameScene() = default;
    ~GameScene() override = default;

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

private:
    // ゲームオブジェクトの初期化
    void InitializeObjects();

    // ゲームの終了判定
    void CheckGameResult();

private:
    // ゲーム終了判定
    bool isGameOver_ = false;
    bool isClear_ = false;
};
