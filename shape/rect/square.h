#pragma once

#include "../polygon.h"

//    p0********p1
//    *          *
//    *          *
//    *          *
//    *          *
//    *          *
//    p3********p2
class SSquare : public Polygon {
public:
	SSquare() : Polygon(4, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		pnt[0] = lt;
		pnt[2] = rb;
		pnt[1] = {pnt[2].x, pnt[0].y};
		pnt[3] = {pnt[0].x, pnt[2].y};
	}

	string getName() {
		return "Square";
	}
};