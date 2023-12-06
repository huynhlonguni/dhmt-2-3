#pragma once

#include "../polygon.h"

//    p0********p1
//    *          *
//    *          *
//    *          *
//    *          *
//    *          *
//    p3********p2
class SRectangle : public Polygon {
public:
	SRectangle() : Polygon(4, false) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		pnt[0] = start;
		pnt[2] = end;
		pnt[1] = {pnt[2].x, pnt[0].y};
		pnt[3] = {pnt[0].x, pnt[2].y};
	}

	string getName() {
		return "Rectangle";
	}
};