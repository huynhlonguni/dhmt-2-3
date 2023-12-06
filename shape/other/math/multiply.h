#pragma once

#include "../../baked_shape.h"

//          p1                  p3
//         *  *                *  *
//       *      *            *      *
//     p0         *        *          p4
//       *          *    *          *
//         *          p2          *
//           *                  * 
//             *              * 
//              p11         p5 
//             *              * 
//           *                  * 
//         *          p8          *
//       *          *    *          *
//    p10         *        *          p6
//       *      *            *      *
//         *  *                *  *
//          p9                  p7
class SMultiplySign : public BakedShape {
public:
	SMultiplySign() : BakedShape(12, false) {
		const float thickness = 0.3;
		const float dist = thickness / 1.4142135623730951; //sqrt(2)

		coords[0] = {0, 1 - dist};
		coords[1] = {dist, 1};
		coords[2] = {0.5, 0.5 + dist};
		coords[3] = {1 - dist, 1};
		coords[4] = {1, 1 - dist};
		coords[5] = {0.5 + dist, 0.5};
		coords[6] = {1, dist};
		coords[7] = {1 - dist, 0};
		coords[8] = {0.5, 0.5 - dist};
		coords[9] = {dist, 0};
		coords[10] = {0, dist};
		coords[11] = {0.5 - dist, 0.5};
	}

	string getName() {
		return "Multiply Sign";
	}
};