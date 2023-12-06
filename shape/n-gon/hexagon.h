#pragma once

#include <math.h>
#include "../polygon.h"

//         p0
//      *      *
//    p1        p5
//    *          *
//    *          *
//    p2        p4
//      *      *
//         p3
class SHexagon : public Polygon {
public:
	SHexagon() : Polygon(6, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float radius = bbox.getBase() / 2;
		Vector2 center;
		center.x = (lt.x + rb.x) / 2;
		center.y = (lt.y + rb.y) / 2;

		for (int i = 0; i < 6; i++) {
			float th = M_PI / 2 + i * 2.0 * M_PI / 6.0;
			pnt[i].x = center.x + radius * cos(th);
			pnt[i].y = center.y + radius * sin(th);
		}
	}

	string getName() {
		return "Hexagon";
	}
};