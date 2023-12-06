#pragma once

#include "../baked_shape.h"

//                         p2
//                         * *
//                         *   *
//                         *     *
//    p0*******************p1      *
//    *                    *         *
//    *                    *          p3
//    *                    *         *
//    p6*******************p5      *
//                         *     *
//                         *   *
//                         * *
//                         p4
class SArrow : public BakedShape {
public:
	SArrow() : BakedShape(7, false) {
		const float thickness = 0.4;
		const float arrowHeadStart = 0.7;

		const float halfThick = thickness / 2.0;

		coords[0] = {0, 0.5 + halfThick};
		coords[1] = {arrowHeadStart, 0.5 + halfThick};
		coords[2] = {arrowHeadStart, 1};
		coords[3] = {1, 0.5};
		coords[4] = {arrowHeadStart, 0};
		coords[5] = {arrowHeadStart, 0.5 - halfThick};
		coords[6] = {0, 0.5 - halfThick};
	}

	string getName() {
		return "Arrow";
	}
};