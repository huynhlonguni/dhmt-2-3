#pragma once

#include "../../baked_shape.h"

//           p0****p1
//           *      *
//           *      *
//           *      *
//    p10***p11     p2****p3
//    *                    *
//    *                    *
//    *                    *
//    p9*****p8     p5****p4
//           *      *
//           *      *
//           *      *
//           p7****p6
class SPlusSign : public BakedShape {
public:
	SPlusSign() : BakedShape(12, false) {
		const float thickness = 0.3;
		const float halfThick = thickness / 2.0;

		coords[0] = {0.5 - halfThick, 1};
		coords[1] = {0.5 + halfThick, 1};
		coords[2] = {0.5 + halfThick, 0.5 + halfThick};
		coords[3] = {1, 0.5 + halfThick};
		coords[4] = {1, 0.5 - halfThick};
		coords[5] = {0.5 + halfThick, 0.5 - halfThick};
		coords[6] = {0.5 + halfThick, 0};
		coords[7] = {0.5 - halfThick, 0};
		coords[8] = {0.5 - halfThick, 0.5 - halfThick};
		coords[9] = {0, 0.5 - halfThick};
		coords[10] = {0, 0.5 + halfThick};
		coords[11] = {0.5 - halfThick, 0.5 + halfThick};
	}

	string getName() {
		return "Plus Sign";
	}
};