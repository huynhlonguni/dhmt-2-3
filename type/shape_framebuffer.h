#pragma once

#include "primitive.h"
#include "bounding_box.h"
#include "matrix.h"
#include "../fill/fill.h"
#include <math.h>
#include <vector>
using namespace std;

class ShapeFramebuffer {
private:
	enum PIXEL_TYPE {
		PIXEL_NONE = 0,
		PIXEL_OUTLINE,
		PIXEL_FILL,
	};

	Matrix transform;

	int xo = 0; //frame x
	int yo = 0; //frame y
	int w = 0; //frame width
	int h = 0; //frame height

	vector<char> img;

	FillFunctionPtr filler = nullptr;
private:

	void setPixel(int x, int y) {
		x = x - xo;
		y = y - yo;

		if (x >= 0 && x < w && y >= 0 && y < h)
			img[y * w + x] = PIXEL_OUTLINE;
	}

	void drawBresenhamDX(int x1, int y1, int x2, int y2) {
		int dx = x2 - x1;
		int dy = y2 - y1;

		int yi = 1;
		if (dy < 0) {
			yi = -1;
			dy = -dy;
		}

		int p = 2 * dy - dx;
		int y = y1;

		for (int x = x1; x <= x2; x++) {
			setPixel(x, y);
			if (p > 0) {
				y += yi;
				p += 2 * (dy - dx);
			}
			else {
				p += 2 * dy;
			}
		}
	}

	void drawBresenhamDY(int x1, int y1, int x2, int y2) {
		int dx = x2 - x1;
		int dy = y2 - y1;

		int xi = 1;
		if (dx < 0) {
			xi = -1;
			dx = -dx;
		}

		int p = 2 * dx - dy;
		int x = x1;

		for (int y = y1; y <= y2; y++) {
			setPixel(x, y);
			if (p > 0) {
				x += xi;
				p += 2 * (dx - dy);
			}
			else {
				p += 2 * dx;
			}
		}
	}


public:
	ShapeFramebuffer() {}

	void reshape(BoundingBox box) {
		int xs, xe, ys, ye;
		box.getLimits(xs, xe, ys, ye, 0);

		xo = xs;
		yo = ys;
		w = xe - xs + 1; // + 1 to include x end too
		h = ye - ys + 1; // + 1 to include y end too

		img.resize(w * h);
		clear();
	}

	void applyTransformationMatrix(Matrix mtrx) {
		transform = mtrx;
	}

	//References: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	void setLine(Vector2 p1, Vector2 p2) {
		p1 = transform.transformPoint(p1);
		p2 = transform.transformPoint(p2);
		
		int x1 = p1.x;
		int y1 = p1.y;
		int x2 = p2.x;
		int y2 = p2.y;
		
		int dx = x2 - x1;
		int dy = y2 - y1;

		if (abs(dx) > abs(dy)) {
			if (x1 > x2)
				drawBresenhamDX(x2, y2, x1, y1);
			else
				drawBresenhamDX(x1, y1, x2, y2);
		}
		else {
			if (y1 > y2)
				drawBresenhamDY(x2, y2, x1, y1);
			else
				drawBresenhamDY(x1, y1, x2, y2);
		}
	}

	void clear() {
		std::fill(img.begin(), img.end(), PIXEL_NONE);
	}

	bool containsPoint(Vector2 pnt) {
		int x = pnt.x - xo;
		int y = pnt.y - yo;

		if (x >= 0 && x < w && y >= 0 && y < h)
			return img[y * w + x] != PIXEL_NONE;
	
		return false;		
	}

	void setFillFunction(FillFunctionPtr func) {
		filler = func;
	}

	void fill(int xc, int yc) {
		if (filler) {
			filler(xc - xo, yc - yo, w, h, img.data(), PIXEL_FILL, PIXEL_OUTLINE);
		}
	}

	unsigned int getShapeArea() {
		unsigned int area = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				area += img[y * w + x] != PIXEL_NONE;
			}
		}
		
		return area;
	}

	void draw(Color outlineColor, Color fillColor) {
		glBegin(GL_POINTS);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				char px = img[y * w + x];

				if (px == PIXEL_OUTLINE && outlineColor.a != 0) {
					Color::setColor(outlineColor);
					Vector2::setVertex(x + xo, y + yo);
				}
				else if (px == PIXEL_FILL && fillColor.a != 0) {
					Color::setColor(fillColor);
					Vector2::setVertex(x + xo, y + yo);
				}
			}
		}
		glEnd();
		glFlush();
	}
};