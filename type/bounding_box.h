#pragma once

#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "primitive.h"
#include "util.h"
#include "matrix.h"
using namespace std;

class BoundingBox {
private:
	Vector2 lt;
	Vector2 rb;

	vector<Vector2> pnts;
	float l, r, b, t;
public:
	BoundingBox() : pnts(4) {}

	void populatePnts() {
		pnts[0] = lt;
		pnts[1] = {rb.x, lt.y};
		pnts[2] = rb;
		pnts[3] = {lt.x, rb.y};
	}

	void calcLimits() {
		l = pnts[0].x;
		r = pnts[0].x;
		b = pnts[0].y;
		t = pnts[0].y;

		for (int i = 1; i < 4; i++) {
			Vector2 p = pnts[i];

			if (l > p.x) l = p.x;
			else if (r < p.x) r = p.x;

			if (b > p.y) b = p.y;
			else if (t < p.y) t = p.y;
		}
	}

	void applyTransformationMatrix(Matrix mtrx) {
		populatePnts();
		pnts = mtrx.transformPoints(pnts);
		calcLimits();
	}

	float getWidth() {
		return rb.x - lt.x;
	}

	float getHeight() {
		return lt.y - rb.y;
	}

	float getBase() {
		return getWidth();
	}

	Vector2 getCenter() {
		return {(lt.x + rb.x) / 2, (lt.y + rb.y) / 2};
	}

	Vector2 getTransformedCenter() {
		return {(pnts[0].x + pnts[2].x) / 2, (pnts[0].y + pnts[2].y) / 2};
	}

	bool containsPoint(Vector2 pnt) {
		return Util::isOnSideOfLine(pnt, pnts[0], pnts[1]) && Util::isOnSideOfLine(pnt, pnts[1], pnts[2]);
	}

	void getBoundingBox(Vector2 &leftTop, Vector2 &rightBottom) {
		leftTop = lt;
		rightBottom = rb;
	}

	void getLimits(int &xs, int &xe, int &ys, int &ye, int padding = 1) {
		xs = floor(l);
		xe = ceil(r);
		ys = floor(b);
		ye = ceil(t);

		xs -= padding;
		ys -= padding;
		xe += padding;
		ye += padding;
	}

	void reshape(Vector2 start, Vector2 end, bool makeSquare = false) {
		l = start.x < end.x ? start.x : end.x;
		r = start.x > end.x ? start.x : end.x;
		b = start.y < end.y ? start.y : end.y;
		t = start.y > end.y ? start.y : end.y;
		
		const float width = r - l;
		const float height = t - b;

		const float base = width < height ? width : height;

		if (l == start.x) {
			lt.x = l;
			rb.x = l + (makeSquare ? base : width);
		}
		else {
			rb.x = r;
			lt.x = r - (makeSquare ? base : width);
		}

		if (t == start.y) {
			lt.y = t;
			rb.y = t - (makeSquare ? base : height);
		}
		else {
			rb.y = b;
			lt.y = b + (makeSquare ? base : height);
		}

		populatePnts();
	}

	void draw() {
		Util::drawDashedLine(pnts[0], pnts[1]);
		Util::drawDashedLine(pnts[1], pnts[2]);
		Util::drawDashedLine(pnts[2], pnts[3]);
		Util::drawDashedLine(pnts[3], pnts[0]);

		Util::drawControlPoint(pnts[0]);
		Util::drawControlPoint(pnts[1]);
		Util::drawControlPoint(pnts[2]);
		Util::drawControlPoint(pnts[3]);

		Util::drawControlPoint(getTransformedCenter());

		glFlush();
	}

};