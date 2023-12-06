#pragma once

#include "../polygon.h"

//    p1
//    * *
//    *  * 
//    *   *
//    *    *
//    *     *
//    p0*****p2
class SIsoscelesRightTriangle : public Polygon {
public:
	SIsoscelesRightTriangle() : Polygon(3, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float base = bbox.getBase();

		pnt[0] = start;
		pnt[1] = {pnt[0].x, pnt[0].y + base * (end.y > start.y ? 1 : -1)};
		pnt[2] = {pnt[0].x + base * (end.x > start.x ? 1 : -1), pnt[0].y};
	}

	string getName() {
		return "Isosceles Right Triangle";
	}
};