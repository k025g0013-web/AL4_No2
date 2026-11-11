#include "SceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"

void SceneManager::Initialize(IScene::SceneType initialScene) {
    isQuit_ = false;
    transitionPhase_ = TransitionState::kNone;
    nextScene_.reset();

    ChangeScene(initialScene);
}

void SceneManager::Update() {
    if (isQuit_) {
        return;
    }

    // 通常時
    if (transitionPhase_ == TransitionState::kNone) {
        if (scene_) {
            scene_->Update();
            // シーン遷移要求を確認
            CheckSceneChange();
        }

    } else {
        // 遷移中
        UpdateTransition();
    }
}

void SceneManager::Draw() {
    // 現在のシーンを描画
    if (scene_) {
        scene_->Draw();
    }

    // ワイプを描画
    // wipeManager_->Draw();
}

std::unique_ptr<IScene> SceneManager::CreateScene(IScene::SceneType type) {
    switch (type) {
    case IScene::SceneType::kTitle:
        return std::make_unique<TitleScene>();

    case IScene::SceneType::kGame:
        return std::make_unique<GameScene>();

    case IScene::SceneType::kGameOver:
        return std::make_unique<GameOverScene>();

    case IScene::SceneType::kClear:
        return std::make_unique<ClearScene>();

    default:
        return nullptr;
    }
}

void SceneManager::ChangeScene(IScene::SceneType type) {
    // シーン生成
    std::unique_ptr<IScene> newScene = CreateScene(type);
    if (!newScene) {
        return;
    }

    // 現在のシーンを新しいシーンに置き換える
    scene_ = std::move(newScene);

    // 新しいシーンを初期化
    scene_->Initialize();
}

// シーン遷移要求の確認
void SceneManager::CheckSceneChange() {
    // シーン遷移要求がなければ終了
    if (!scene_->IsSceneChangeRequested()) {
        return;
    }

    // 遷移先を取得
    nextScene_ = scene_->GetNextScene();

    // フェードアウト開始
    transitionPhase_ = TransitionState::kFadeOut;

    // WipeManagerのフェードアウト開始処理
}

void SceneManager::UpdateTransition() {

    // ワイプの更新
    // wipeManager_->Update();

    switch (transitionPhase_) {

    case TransitionState::kFadeOut:
        // フェードアウトが完了したら
        // if (wipeManager_->IsFinished()) {
        // シーンを切り替える
        if (nextScene_) {
            ChangeScene(*nextScene_);
            nextScene_.reset();
        }

        // フェードイン開始
        transitionPhase_ = TransitionState::kFadeIn;
        // wipeManager_->StartFadeIn();
        //}

        break;

    case TransitionState::kFadeIn:
        // フェードインが完了したら
        // transitionPhase_ = TransitionState::kNone;
        transitionPhase_ = TransitionState::kNone;

        break;

    default:
        break;
    }
}
