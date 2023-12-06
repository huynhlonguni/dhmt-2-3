#pragma once

#include <math.h>
#include "../polygon.h"

//         p0
//        *  *
//      *      *
//    p1        p4
//    *          *
//     *        *
//      *      *
//      p2****p3
class SPentagon : public Polygon {
public:
	SPentagon() : Polygon(5, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float radius = bbox.getBase() * 0.5257311121191336;
		float height = bbox.getBase() * 0.552786404500042;
		Vector2 center;
		center.x = (lt.x + rb.x) / 2;
		center.y = lt.y > rb.y ? lt.y - height : rb.y - height;

		for (int i = 0; i < 5; i++) {
			float th = M_PI / 2 + i * 2.0 * M_PI / 5.0;
			pnt[i].x = center.x + radius * cos(th);
			pnt[i].y = center.y + radius * sin(th);
		}
	}

	string getName() {
		return "Pentagon";
	}
};