#pragma once
#include "KamataEngine.h"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    // インスタンス取得
    static AssetManager *GetInstance();

    // テクスチャ取得
    uint32_t GetTextureHandle(const std::string &filename);

    // 音声取得
    uint32_t GetAudioHandle(const std::string &filename);

    // モデル取得
    KamataEngine::Model *GetModel(const std::string &filename);

    // CSV読み込み
    std::string LoadCSV(const std::string &filename) const;

    // リソースの事前読み込み
    void PreloadAll();

    // リソース解放
    void Clear();

private:
    // テクスチャ
    std::unordered_map<std::string, uint32_t> textures_;

    // 音声
    std::unordered_map<std::string, uint32_t> audios_;

    // 3Dモデル
    std::unordered_map<std::string, std::unique_ptr<KamataEngine::Model>> models_;
};
