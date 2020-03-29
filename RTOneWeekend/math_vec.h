#pragma once

#include <math.h>

typedef double real;

struct vec3
{
public:
	union {
		struct {
			real x, y, z;
		};
		real m[3];
	};

public:
	vec3() : x(0), y(0), z(0) {}
	vec3(real f) : x(f), y(f), z(f) {}
	vec3(real x, real y, real z) : x(x), y(y), z(z) {}
};

inline vec3 operator+(const vec3& a, const vec3& b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline vec3 operator-(const vec3& a, const vec3& b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vec3 operator*(const vec3& a, const vec3& b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline vec3 operator/(const vec3& a, const vec3& b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
inline vec3 operator*(const vec3& a, real f) { return vec3(f * a.x, f * a.y, f * a.z); }
inline vec3 operator*(real f, const vec3& a) { return vec3(f * a.x, f * a.y, f * a.z); }
inline vec3 operator/(const vec3& a, real f) { return vec3(a.x / f, a.y / f, a.z / f); }
inline vec3 operator-(const vec3& a) { return vec3(-a.x, -a.y, -a.z); }

inline real dot(const vec3& a, const vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline real length_squared(const vec3& a) { return dot(a, a); }
inline real length(const vec3& a) { return sqrt(dot(a, a)); }
inline vec3 normalize(const vec3& a) { return a / length(a); }

inline vec3 cross(const vec3& a, const vec3& b) { return vec3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y + a.y*b.x); }
inline vec3 vec3_pow(const vec3& a, real p) { return vec3(pow(a.x, p), pow(a.y, p), pow(a.z, p)); }


struct ray
{
	ray() {}
	ray(const vec3& origin, const vec3& dir) :origin(origin), dir(dir) {}

	vec3 origin;
	vec3 dir;
};

inline vec3 ray_at(const ray& r, real t) { return r.origin + t * r.dir; }

