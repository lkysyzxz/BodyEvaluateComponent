#pragma once
#include <math.h>
#include <fbxsdk.h>
#include <ctime>
#include <string>
#include <iostream>

class Vector3 {
private:
	static float Pow2(float x) { return x*x; }

	static float Sqrt(float x) { return sqrt(x); }
public:
	float x;
	float y;
	float z;

	Vector3(float x_, float y_, float z_)
		:x(x_), y(y_), z(z_) {

	}

	float Length() {
		return Vector3::Sqrt(Pow2(x) + Pow2(y) + Pow2(z));
	}

	Vector3 Normalize() {
		float l = Length();
		x /= l;
		y /= l;
		z /= l;
		return *this;
	}
};

class Quaternion {
private:
	static float Pow2(float x) { return x*x; }

	static float Sqrt(float x) { return sqrt(x); }

	static Quaternion MakeQuaternion(const Vector3 &axis, float theta) {
		return Quaternion(axis.x*sin(theta / 2.0f), axis.y*sin(theta / 2.0f), axis.z*sin(theta / 2.0f), cos(theta / 2.0f));
	}

	static Quaternion Mul(Quaternion &left, Quaternion &right, Quaternion *dest = NULL) {
		float nw = left.W()*right.W() - left.X()*right.X() - left.Y()*right.Y() - left.Z()*right.Z();
		float nx = left.W()*right.X() + left.X()*right.W() + left.Y()*right.Z() - left.Z()*right.Y();
		float ny = left.W()*right.Y() - left.X()*right.Z() + left.Y()*right.W() + left.Z()*right.X();
		float nz = left.W()*right.Z() + left.X()*right.Y() - left.Y()*right.X() + left.Z()*right.W();
		if (dest) {
			dest->x = nx;
			dest->y = ny;
			dest->z = nz;
			dest->w = nw;
		}
		return Quaternion(nx, ny, nz, nw);

	}

public:
	float W() { return this->w; }
	float X() { return this->x; }
	float Y() { return this->y; }
	float Z() { return this->z; }

	void Mul(Quaternion &right) {
		Quaternion &left = *this;
		float nw = left.W()*right.W() - left.X()*right.X() - left.Y()*right.Y() - left.Z()*right.Z();
		float nx = left.W()*right.X() + left.X()*right.W() + left.Y()*right.Z() - left.Z()*right.Y();
		float ny = left.W()*right.Y() - left.X()*right.Z() + left.Y()*right.W() + left.Z()*right.X();
		float nz = left.W()*right.Z() + left.X()*right.Y() - left.Y()*right.X() + left.Z()*right.W();
		this->x = nx;
		this->y = ny;
		this->z = nz;
		this->w = nw;
	}

	void DCM2Quat(FbxAMatrix r) {
		/*
		Rotation Matrix:
			R=[ r11 r12 r13
				r21 r22 r23
				r31 r32 r33 ];
		Quaternion:
			q0=0.5*sqrt(1+r11+r22+r33);
			q1=(r32-r23)/(4*q0);
			q2=(r13-r31)/(4*q0);
			q3=(r21-r12)/(4*q0);
		*/
		x = (float)(0.5*sqrt(1 + r.Get(0, 0) + r.Get(1, 1) + r.Get(2, 2)));
		y = (float)((r.Get(2, 1) - r.Get(1, 2)) / (4 * x));
		z = (float)((r.Get(0, 2) - r.Get(2, 0)) / (4 * x));
		w = (float)((r.Get(1, 0) - r.Get(0, 1)) / (4 * x));
		matrix = r;
	}
	FbxAMatrix Quat2DCM() {
		//print(matrix, "before:");
		srand((unsigned)time(NULL));
		float rotateAngle = (rand() / float(RAND_MAX)) * 2 * 3.1415926f;
		Quaternion rot = Quaternion::MakeQuaternion(Vector3((rand() / float(RAND_MAX)), (rand() / float(RAND_MAX)), (rand() / float(RAND_MAX))).Normalize(), rotateAngle);
		Quaternion::Mul(rot, *this, this);
		//x += rand() / float(RAND_MAX);
		//y += rand() / float(RAND_MAX);
		//z += rand() / float(RAND_MAX);
		//w += rand() / float(RAND_MAX);
		//x /= length();
		//y /= length();
		//z /= length();
		//w /= length();
		matrix[0][0] = 1 - 2 * z*z - 2 * w*w;   matrix[0][1] = 2 * y*z - 2 * x*w;			matrix[0][2] = 2 * y*w + 2 * x*z;
		matrix[1][0] = 2 * y*z + 2 * x*w;       matrix[1][1] = 1 - 2 * y*y - 2 * w*w;		matrix[1][2] = 2 * z*w - 2 * x*y;
		matrix[2][0] = 2 * y*w - 2 * x*z;	    matrix[2][1] = 2 * z*w + 2 * x*y;		    matrix[2][2] = 1 - 2 * y*y - 2 * z*z;
		//print(matrix, "end:");
		return matrix;
	}
	FbxMatrix AddError() {

		return Quat2DCM();
	}
	static float DistanceBetween(const Quaternion &a, const Quaternion &b) {
		return Sqrt(Pow2(a.x - b.x) + Pow2(a.y - b.y) + Pow2(a.z - b.z) + Pow2(a.w - b.w));
	}

private:
	float x;
	float y;
	float z;
	float w;
	FbxAMatrix matrix;

public:
	Quaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f)
		:x(_x), y(_y), z(_z), w(_w) {
	}
	float length() {
		return Sqrt(Pow2(x) + Pow2(y) + Pow2(z) + Pow2(w));
	}
	void print(FbxAMatrix m, std::string s) {
		std::cout << s << std::endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << m.Get(i, j) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};