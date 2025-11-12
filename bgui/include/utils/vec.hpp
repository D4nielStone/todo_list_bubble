#pragma once
#include <cmath>
#include <array>

namespace butil {
    template<size_t N, typename T = float>
    class vec {
    public:
        std::array<T, N> v{};

        vec() {
            for(auto& component : v) {
                component = (T)0;
            } 
        }
        
        vec(const T& scalar) {
            for(auto& component : v) {
                component = scalar;
            } 
        }

        vec(std::initializer_list<T> list) {
            size_t i = 0;
            for (auto& value : list) {
                if (i < N) {
                    v[i++] = value;
                }
            }
        }

        T& operator[](size_t index) {
            return v[index];
        }
        const T& operator[](size_t index) const {
            return v[index];
        }

        vec<N, T> operator+(const vec<N, T>& other) const {
            vec<N, T> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = v[i] + other[i];
            }
            return result;
        }

        vec<N, T> operator-(const vec<N, T>& other) const {
            vec<N, T> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = v[i] - other[i];
            }
            return result;
        }

        vec<N, T> operator*(const T& scalar) const {
            vec<N, T> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = v[i] * scalar;
            }
            return result;
        }

        vec<N, T> operator/(const T& scalar) const {
            vec<N, T> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = v[i] / scalar;
            }
            return result;
        }

        vec<N, T> operator*(const vec<N, T>& other) const {
            vec result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = v[i] * other[i];
            }
            return result;
        }

        bool operator==(const vec<N, T>& other) const {
            return v == other.v;
        }
    };

    using vec4 = vec<4, float>;
    using vec3 = vec<3, float>;
    using vec2 = vec<2, float>;

    using vec4i = vec<4, int>;
    using vec3i = vec<3, int>;
    using vec2i = vec<2, int>;

    using color = vec4;
} // namespace butil