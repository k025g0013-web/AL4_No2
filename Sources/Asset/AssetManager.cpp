#include "AssetManager.h"

#include <fstream>
#include <sstream>
#include <filesystem>

AssetManager *AssetManager::GetInstance() {
    static AssetManager instance;
    return &instance;
}

uint32_t AssetManager::GetTextureHandle(const std::string &filename) {
    // 既に読み込まれているか確認
    auto it = textures_.find(filename);

    if (it != textures_.end()) {
        return it->second;
    }

    // 読み込まれていなければロード
    uint32_t handle = KamataEngine::TextureManager::Load(filename);

    // 読み込んだリソースを保存
    textures_.emplace(filename, handle);

    return handle;
}


uint32_t AssetManager::GetAudioHandle(const std::string &filename) {
    // 既に読み込まれているか確認
    auto it = audios_.find(filename);

    if (it != audios_.end()) {
        return it->second;
    }

    // 読み込まれていなければロード
    uint32_t handle = KamataEngine::Audio::GetInstance()->LoadWave(filename);

    // 読み込んだリソースを保存
    audios_.emplace(filename, handle);

    return handle;
}


KamataEngine::Model *AssetManager::GetModel(const std::string &filename) {
    // 既に読み込まれているか確認
    auto it = models_.find(filename);

    if (it != models_.end()) {
        return it->second.get();
    }

    // モデルを生成
    std::unique_ptr<KamataEngine::Model> model(
        KamataEngine::Model::CreateFromOBJ(filename, true)
    );

    // 生成に失敗した場合
    if (!model) {
        return nullptr;
    }

    // モデルを保存
    KamataEngine::Model *result = model.get();
    models_.emplace(filename, std::move(model));

    return result;
}

std::string AssetManager::LoadCSV(const std::string &filename) const {
    // ファイルを開く
    std::ifstream file("Resources/maps/" + filename);

    if (!file.is_open()) {
        return "";
    }

    // ファイルの内容を読み込む
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void AssetManager::PreloadAll() {
    // リソースフォルダ
    const std::filesystem::path resourceDir = "Resources";

    // フォルダが存在しなければ終了
    if (!std::filesystem::exists(resourceDir)) {
        return;
    }

    // フォルダ内のファイルを再帰的に検索
    for (const auto &entry :
        std::filesystem::recursive_directory_iterator(resourceDir)) {

        // ファイル以外は無視
        if (!entry.is_regular_file()) {
            continue;
        }

        // ファイル情報を取得
        const std::filesystem::path path = entry.path();
        const std::string extension = path.extension().string();

        // Resourcesからの相対パス
        const std::string relativePath =
            std::filesystem::relative(path, resourceDir).string();

        // 拡張子によって処理を分岐
        if (extension == ".png") {

            // モデル用のテクスチャなら読み込まない
            const std::filesystem::path objPath =
                path.parent_path() /
                (path.parent_path().filename().string() + ".obj");

            if (std::filesystem::exists(objPath)) {
                continue;
            }

            GetTextureHandle(relativePath);

        } else if (extension == ".mp3") {

            GetAudioHandle(relativePath);

        } else if (extension == ".obj") {

            // モデルが入っているフォルダ名を取得
            const std::string modelName =
                path.parent_path().filename().string();

            GetModel(modelName);
        }
    }
}

void AssetManager::Clear() {
    // 管理しているリソース情報を削除
    textures_.clear();
    audios_.clear();
    models_.clear();
}