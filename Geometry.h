#pragma once
#include<array>

// 向量类，长度为3，类型为float： {float, float, float}
using v3f = std::array<float, 3u>;

// 球类 pos:球心位置，r:半径，ks kd ka:此球面的高光系数、漫反射系数、环境光系数
struct Sphere {
	Sphere() = default;
	Sphere(v3f pos, int r) : pos(pos), r(r), ks(v3f{ 0.5f, 0.5f, 0.5f }), kd(v3f{ 0.5f, 0.5f, 0.5f }), ka(v3f{ 0.5f, 0.5f, 0.5f }) {}
	Sphere(v3f pos, int r, v3f ks, v3f kd, v3f ka) :
		pos(pos), r(r), ks(ks), kd(kd), ka(ka) {}
	v3f pos;
	int r;
	v3f ks, kd, ka;
};

// 点光源类 pos:点光源位置，color:光源颜色
struct PointLight {
	PointLight() = default;
	PointLight(v3f pos, v3f color) : pos(pos), color(color) {}
	v3f pos;
	v3f color;
};

// 向量数乘，数*向量
template<typename T>
v3f operator *(const T& t, const v3f& v);

template<typename T>
v3f operator *(const v3f& v, const T& t);

// 向量相乘：v1*v2
v3f operator *(const v3f& v1, const v3f& v2);

// 向量相加：v1+v2
v3f operator +(const v3f& v1, const v3f& v2);

// 向量相减：v1-v2
v3f operator -(const v3f& v1, const v3f& v2);

// 向量点乘：v1·v2
float dot(const v3f& v1, const v3f& v2);

// 向量叉乘：v1×v2
v3f cross(const v3f& v1, const v3f& v2);

// 向量模长
float norm(const v3f& v);

// 单位向量，归一化
v3f normalize(const v3f& v);