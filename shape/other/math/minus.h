#pragma once

#include "../../baked_shape.h"

//    p0******************p1
//    *                    *
//    *                    *
//    *                    *
//    p3******************p2
class SMinusSign : public BakedShape {
public:
	SMinusSign() : BakedShape(4, false) {
		const float thickness = 0.3;
		const float halfThick = thickness / 2.0;

		coords[0] = {0, 0.5 + halfThick};
		coords[1] = {1, 0.5 + halfThick};
		coords[2] = {1, 0.5 - halfThick};
		coords[3] = {0, 0.5 - halfThick};
	}

	string getName() {
		return "Minus Sign";
	}
};