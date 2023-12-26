#pragma once

#include <vector>
using namespace std;

class Matrix {
private:
	vector<vector<double>> m;
public:
	Matrix() : m(4, vector<double>(4, 0.0)) {
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
		m[3][3] = 1;
	}

	bool isIdentity() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (m[i][j] != (i == j)) return false;
			}
		}
		return true;
	}

	static Matrix multiply(const Matrix &a, const Matrix &b) {
		Matrix res;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				res.m[i][j] = 0;
				for (int k = 0; k < 4; k++)
					res.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}

		return res;
	}

	void translate(float x, float y, float z) {
		Matrix trans;

		trans.m[0][3] = x;
		trans.m[1][3] = y;
		trans.m[2][3] = z;

		*this = multiply(*this, trans);
	}

	void translate(float x, float y) {
		translate(x, y, 0.0);
	}

	void rotateZ(float alpha) {
		Matrix rot;

		double sina = sin(alpha);
		double cosa = cos(alpha);

		rot.m[0][0] = cosa;
		rot.m[0][1] = -sina;
		rot.m[1][0] = sina;
		rot.m[1][1] = cosa;

		*this = multiply(*this, rot);
	}

	void rotate(float alpha) {
		rotateZ(alpha);
	}

	void scale(float x, float y, float z) {
		Matrix scale;

		scale.m[0][0] = x;
		scale.m[1][1] = y;
		scale.m[2][2] = z;

		*this = multiply(*this, scale);
	}

	void scale(float x, float y) {
		scale(x, y, 1.0);
	}

	void shear(float x, float y) {
		Matrix shear;

		shear.m[1][0] = x;
		shear.m[0][1] = y;

		*this = multiply(*this, shear);
	}

	Vector2 transformPoint(Vector2 pnt) {
		Vector2 res;
		const float x = pnt.x;
		const float y = pnt.y;
		const float z = 0.0;
		const float w = 1.0;

		res.x = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3] * w;
		res.y = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3] * w;

		return res;
	}

	vector<Vector2> transformPoints(vector<Vector2> pnts) {
		vector<Vector2> res = pnts;
		for (int i = 0; i < pnts.size(); i++)
			res[i] = transformPoint(pnts[i]);

		return res;
	}
};