#pragma once
#include<array>

// �����࣬����Ϊ3������Ϊfloat�� {float, float, float}
using v3f = std::array<float, 3u>;

// ���� pos:����λ�ã�r:�뾶��ks kd ka:������ĸ߹�ϵ����������ϵ����������ϵ��
struct Sphere {
	Sphere() = default;
	Sphere(v3f pos, int r) : pos(pos), r(r), ks(v3f{ 0.5f, 0.5f, 0.5f }), kd(v3f{ 0.5f, 0.5f, 0.5f }), ka(v3f{ 0.5f, 0.5f, 0.5f }) {}
	Sphere(v3f pos, int r, v3f ks, v3f kd, v3f ka) :
		pos(pos), r(r), ks(ks), kd(kd), ka(ka) {}
	v3f pos;
	int r;
	v3f ks, kd, ka;
};

// ���Դ�� pos:���Դλ�ã�color:��Դ��ɫ
struct PointLight {
	PointLight() = default;
	PointLight(v3f pos, v3f color) : pos(pos), color(color) {}
	v3f pos;
	v3f color;
};

// �������ˣ���*����
template<typename T>
v3f operator *(const T& t, const v3f& v);

template<typename T>
v3f operator *(const v3f& v, const T& t);

// ������ˣ�v1*v2
v3f operator *(const v3f& v1, const v3f& v2);

// ������ӣ�v1+v2
v3f operator +(const v3f& v1, const v3f& v2);

// ���������v1-v2
v3f operator -(const v3f& v1, const v3f& v2);

// ������ˣ�v1��v2
float dot(const v3f& v1, const v3f& v2);

// ������ˣ�v1��v2
v3f cross(const v3f& v1, const v3f& v2);

// ����ģ��
float norm(const v3f& v);

// ��λ��������һ��
v3f normalize(const v3f& v);