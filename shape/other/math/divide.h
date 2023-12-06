#pragma once

#include "../../baked_shape.h"

//                     p0*********p1
//                    *           *
//                   *           *
//                  *           *
//                 *           *
//                *           *
//               *           *
//              *           *
//             *           *
//            *           *
//           *           *
//          *           *
//         *           *
//        *           *
//       *           *
//      *           *
//     *           *
//    p3*********p2
class SDivideSign : public BakedShape {
public:
	SDivideSign() : BakedShape(4, false) {
		const float thickness = 0.3;
		const float halfThick = thickness / 2.0;
		const float offset = 0.3;

		coords[0] = {0.5 - halfThick + offset, 1};
		coords[1] = {0.5 + halfThick + offset, 1};
		coords[2] = {0.5 + halfThick - offset, 0};
		coords[3] = {0.5 - halfThick - offset, 0};
	}

	string getName() {
		return "Divide Sign";
	}
};