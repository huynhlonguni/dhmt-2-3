#pragma once

#include <GL/glut.h>
#include <math.h>

class Vector2 {
public:
	float x;
	float y;
public:
	Vector2() : x(0), y(0) {}

	Vector2(float x, float y) : x(x), y(y) {}

	static void setVertex(int x, int y) {
		glVertex2i(x, y);
	}

	static void setVertex(float x, float y) {
		glVertex2f(x, y);
	}

	static void setVertex(Vector2 pnt) {
		glVertex2f(pnt.x, pnt.y);
	}

	// Vector2& operator=(const Vector2 &other) = default;
};

class Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

public:
	Color() : r(0), g(0), b(0), a(0) {}

	Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

	static void genColor(Color &color) {
		color.r = rand() / (float)RAND_MAX * 255;
		color.g = rand() / (float)RAND_MAX * 255;
		color.b = rand() / (float)RAND_MAX * 255;
		color.a = 255;
	}

	static void setColor(Color color) {
		glColor4ub(color.r, color.g, color.b, color.a);
	}
};