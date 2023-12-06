#pragma once

#include <math.h>
#include "../polygon.h"

//          p0
//         *  *
//        *    *
//       *      * 
//      *        *
//     *          *
//    p1**********p2
class SEquilateralTriangle : public Polygon {
public:
	SEquilateralTriangle() : Polygon(3, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float base = bbox.getBase();
		float radius = base * 0.5773502691896257; //sqrt(3) / 3
		Vector2 center;
		center.x = (lt.x + rb.x) / 2;
		center.y = lt.y > rb.y ? lt.y : rb.y;
		center.y -= base * 0.0669872981077807 + radius; //0.5 - (sqrt(3) / 4)

		for (int i = 0; i < 3; i++) {
			float th = M_PI / 2 + i * 2.0 * M_PI / 3.0;
			pnt[i].x = center.x + radius * cos(th);
			pnt[i].y = center.y + radius * sin(th);
		}
	}

	string getName() {
		return "Equilateral Triangle";
	}
};