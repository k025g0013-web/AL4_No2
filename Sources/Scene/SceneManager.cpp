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

    // シーン遷移要求用コールバックを設定
    scene_->SetSceneChangeCallback(
        [this](IScene::SceneType nextScene) {
            RequestSceneChange(nextScene);
        }
    );

    // 新しいシーンを初期化
    scene_->Initialize();
}

void SceneManager::RequestSceneChange(IScene::SceneType nextScene) {

	// 遷移中の場合は新しい要求を受け付けない
	if (transitionPhase_ != TransitionState::kNone) {
		return;
	}

	// 遷移先を保存
	nextScene_ = nextScene;

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
		// if (wipeManager_->IsFinished()) {
		// 通常状態に戻る
		transitionPhase_ = TransitionState::kNone;
		//}

		break;

	default:
		break;
	}
}