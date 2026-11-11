#pragma once

#include "KamataEngine.h"

#include <cmath>
#include <cstddef>
#include <random>
#include <algorithm>
#include <cassert>

#ifndef MATH_EPSILON_DEFINED
#define MATH_EPSILON_DEFINED
inline constexpr float kEpsilon = 1e-4f;
#endif

//==============================
// ベクトル型ごとの次元情報
//==============================

template <typename T>
struct VectorTraits;

template <>
struct VectorTraits<KamataEngine::Vector2> {
    static constexpr size_t Dimensions = 2;
};

template <>
struct VectorTraits<KamataEngine::Vector3> {
    static constexpr size_t Dimensions = 3;
};

template <>
struct VectorTraits<KamataEngine::Vector4> {
    static constexpr size_t Dimensions = 4;
};

//==============================
// 計算関数群
//==============================

// Vector2
inline KamataEngine::Vector2 AddVector(
    const KamataEngine::Vector2 &v1,
    const KamataEngine::Vector2 &v2) {

    return {
        v1.x + v2.x,
        v1.y + v2.y
    };
}

inline KamataEngine::Vector2 SubtractVector(
    const KamataEngine::Vector2 &v1,
    const KamataEngine::Vector2 &v2) {

    return {
        v1.x - v2.x,
        v1.y - v2.y
    };
}

// Vector3
inline KamataEngine::Vector3 AddVector(
    const KamataEngine::Vector3 &v1,
    const KamataEngine::Vector3 &v2) {

    return {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
}

inline KamataEngine::Vector3 SubtractVector(
    const KamataEngine::Vector3 &v1,
    const KamataEngine::Vector3 &v2) {

    return {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
}

// Vector4
inline KamataEngine::Vector4 AddVector(
    const KamataEngine::Vector4 &v1,
    const KamataEngine::Vector4 &v2) {

    return {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
        v1.w + v2.w
    };
}

inline KamataEngine::Vector4 SubtractVector(
    const KamataEngine::Vector4 &v1,
    const KamataEngine::Vector4 &v2) {

    return {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z,
        v1.w - v2.w
    };
}

// スカラー倍
template <typename VectorN>
inline VectorN Multiply(float scalar, const VectorN &v) {

    constexpr size_t dim = VectorTraits<VectorN>::Dimensions;

    if constexpr (dim == 2) {
        return { v.x * scalar, v.y * scalar };
    } else if constexpr (dim == 3) {
        return { v.x * scalar, v.y * scalar, v.z * scalar };
    } else {
        return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
    }
}

// スカラー除算
template <typename VectorN>
inline VectorN Divide(const VectorN &v, float scalar) {

    assert(std::abs(scalar) >= kEpsilon);

    return Multiply(1.0f / scalar, v);
}

//==============================
// 演算子オーバーロード
//==============================

namespace KamataEngine {
    // ベクトル加算
    inline Vector2 operator+(
        const Vector2 &v1,
        const Vector2 &v2) {
        return AddVector(v1, v2);
    }

    inline Vector3 operator+(
        const Vector3 &v1,
        const Vector3 &v2) {
        return AddVector(v1, v2);
    }

    inline Vector4 operator+(
        const Vector4 &v1,
        const Vector4 &v2) {
        return AddVector(v1, v2);
    }

    // ベクトル減算
    inline Vector2 operator-(
        const Vector2 &v1,
        const Vector2 &v2) {
        return SubtractVector(v1, v2);
    }

    inline Vector3 operator-(
        const Vector3 &v1,
        const Vector3 &v2) {
        return SubtractVector(v1, v2);
    }

    inline Vector4 operator-(
        const Vector4 &v1,
        const Vector4 &v2) {
        return SubtractVector(v1, v2);
    }
}

    // スカラー乗算
    template <typename VectorN>
    inline VectorN operator*(const VectorN &v, float scalar) {
        return Multiply(scalar, v);
    }

    template <typename VectorN>
    inline VectorN operator*(float scalar, const VectorN &v) {
        return Multiply(scalar, v);
    }

    // スカラー除算
    template <typename VectorN>
    inline VectorN operator/(const VectorN &v, float scalar) {
        return Divide(v, scalar);
    }

    // 加算代入
    template <typename VectorN>
    inline VectorN &operator+=(VectorN &v1, const VectorN &v2) {
        v1 = v1 + v2;
        return v1;
    }

    // 減算代入
    template <typename VectorN>
    inline VectorN &operator-=(VectorN &v1, const VectorN &v2) {
        v1 = v1 - v2;
        return v1;
    }

    // 乗算代入
    template <typename VectorN>
    inline VectorN &operator*=(VectorN &v, float scalar) {
        v = v * scalar;
        return v;
    }

    // 除算代入
    template <typename VectorN>
    inline VectorN &operator/=(VectorN &v, float scalar) {
        v = v / scalar;
        return v;
    }

    // 等価比較
    template <typename VectorN>
    inline bool operator==(const VectorN &v1, const VectorN &v2) {
        constexpr size_t dim = VectorTraits<VectorN>::Dimensions;

        if constexpr (dim == 2) {
            return std::abs(v1.x - v2.x) < kEpsilon &&
                std::abs(v1.y - v2.y) < kEpsilon;
        } else if constexpr (dim == 3) {
            return std::abs(v1.x - v2.x) < kEpsilon &&
                std::abs(v1.y - v2.y) < kEpsilon &&
                std::abs(v1.z - v2.z) < kEpsilon;
        } else {
            return std::abs(v1.x - v2.x) < kEpsilon &&
                std::abs(v1.y - v2.y) < kEpsilon &&
                std::abs(v1.z - v2.z) < kEpsilon &&
                std::abs(v1.w - v2.w) < kEpsilon;
        }
    }

    // 非等価比較
    template <typename VectorN>
    inline bool operator!=(const VectorN &v1, const VectorN &v2) {
        return !(v1 == v2);
    }

//==============================
// ベクトル計算
//==============================

// 内積
template <typename VectorN>
inline float Dot(const VectorN &v1, const VectorN &v2) {
    constexpr size_t dim = VectorTraits<VectorN>::Dimensions;

    if constexpr (dim == 2) {
        return v1.x * v2.x + v1.y * v2.y;
    } else if constexpr (dim == 3) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    } else {
        return v1.x * v2.x + v1.y * v2.y +
            v1.z * v2.z + v1.w * v2.w;
    }
}

// 長さの二乗
template <typename VectorN>
inline float LengthSquare(const VectorN &v) {
    return Dot(v, v);
}

// 長さ
template <typename VectorN>
inline float Length(const VectorN &v) {
    return std::sqrt(LengthSquare(v));
}

// 正規化
template <typename VectorN>
inline VectorN Normalize(const VectorN &v) {

    float length = Length(v);

    if (length < kEpsilon) {
        return {};
    }

    return v / length;
}