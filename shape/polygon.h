#pragma once

#include <vector>
#include "shape.h"

class Polygon : public Shape {
protected:
	vector<Vector2> pnt;
public:
	Polygon(int vertexCount, bool squareShape) : Shape(squareShape), pnt(vertexCount) {}

	virtual Vector2 getCenter() {
		Vector2 center;

		const int vertexCount = pnt.size();

		for (int i = 0; i < vertexCount; i++) {
			center.x += pnt[i].x;
			center.y += pnt[i].y;
		}

		center.x /= vertexCount;
		center.y /= vertexCount;

		return center;
	}

	virtual void render(ShapeFramebuffer *drawer) {
		const int vertexCount = pnt.size();

		for (int i = 0; i < vertexCount - 1; i++) {
			drawer->setLine(pnt[i], pnt[i + 1]);
		}
		if (vertexCount > 2) {
			drawer->setLine(pnt[vertexCount - 1], pnt[0]); //close loop
		}
	}
};