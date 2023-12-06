#pragma once

#include <math.h>
#include "../shape.h"

class SCircle : public Shape {
private:
	Vector2 center;
	float radius;


public:
	SCircle() : Shape(true) {}

	SCircle(Vector2 center, float radius) : Shape(true), center(center), radius(radius) {}
	
	virtual Vector2 getCenter() {
		return center;
	}

	void render(ShapeFramebuffer *drawer) {
		float xc = center.x;
		float yc = center.y;
		float r = radius;

		int segment = radius * 4 * 2;

		if (!segment) return;

		Vector2 prev(xc + r, yc); // i = 0
		for (int i = 0; i < segment + 1; i++) {
			float th = (i % segment) * 2.0 * M_PI / (float)segment;
			float x = xc + r * cos(th);
			float y = yc + r * sin(th);
			drawer->setLine(prev, Vector2(x, y));
			prev = {x, y};
		}
	}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);
		
		radius = (rb.x - lt.x) / 2;
		center.x = (lt.x + rb.x) / 2;
		center.y = (lt.y + rb.y) / 2;
	}

	string getName() {
		return "Circle";
	}
};