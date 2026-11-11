#include "TitleScene.h"

using namespace KamataEngine;

void TitleScene::Initialize() {
    InitializeObjects();
}

void TitleScene::Update() {
    HandleInput();
}

void TitleScene::Draw() {
}

// タイトル画面の初期化
void TitleScene::InitializeObjects() {};

// 入力処理
void TitleScene::HandleInput() {
    // スタートボタンが押されたら
    if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {

        // ゲームシーンへの遷移を要求
        RequestSceneChange(SceneType::kGame);
    };
};