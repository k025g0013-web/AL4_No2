#include "GameScene.h"

void GameScene::Initialize() {
    InitializeObjects();
}

void GameScene::Update() {
    CheckGameResult();
}

void GameScene::Draw() {}

void GameScene::InitializeObjects() {};

void GameScene::CheckGameResult() {
    // プレイヤーが敗北した場合
    if (isGameOver_) {
        RequestSceneChange(SceneType::kGameOver);
        return;
    }

    // ボスを撃破した場合
    if (isClear_) {
        RequestSceneChange(SceneType::kClear);
    }
}