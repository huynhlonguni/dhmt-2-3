#pragma once

#include <math.h>
#include "../shape.h"

class SEllipse : public Shape {
private:
	Vector2 center;
	float major;
	float minor;


public:
	SEllipse() : Shape(false) {}

	SEllipse(Vector2 center, float major, float minor) : Shape(false), center(center), major(major * 2), minor(minor * 2) {}
	
	virtual Vector2 getCenter() {
		return center;
	}

	void render(ShapeFramebuffer *drawer) {
		float xc = center.x;
		float yc = center.y;
		float a = major / 2;
		float b = minor / 2;

		int segment = (major + minor) * 2;

		if (!segment) return;
		
		Vector2 prev(xc + a, yc); // i = 0
		for (int i = 1; i < segment + 1; i++) {
			float th = (i % segment) * 2.0 * M_PI / (float)segment;
			float x = xc + a * cos(th);
			float y = yc + b * sin(th);
			drawer->setLine(prev, Vector2(x, y));
			prev = {x, y};
		}
	}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		center.x = (start.x + end.x) / 2;
		center.y = (start.y + end.y) / 2;
		major = abs(end.x - start.x);
		minor = abs(end.y - start.y);
	}

	string getName() {
		return "Ellipse";
	}
};