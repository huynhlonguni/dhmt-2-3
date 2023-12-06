#pragma once

#include "../polygon.h"

//               p0
//              *  *
//            *      *
//    p2****p1        p9****p8
//     *                   *
//       *               *
//         p3         p7
//        *     p5     *
//       *    *    *    *
//      *  *         *   *
//      p4              p6 
class SStar : public Polygon {
public:
	SStar() : Polygon(10, true) {}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float radius = bbox.getBase() * 0.5257311121191336;
		float height = bbox.getBase() * 0.552786404500042;
		Vector2 center;
		center.x = (lt.x + rb.x) / 2;
		center.y = lt.y > rb.y ? lt.y - height : rb.y - height;

		//pointed vertices
		for (int i = 0; i < 5; i++) {
			float th = M_PI / 2 + i * 2.0 * M_PI / 5.0;
			pnt[i * 2].x = center.x + radius * cos(th);
			pnt[i * 2].y = center.y + radius * sin(th);
		}

		//inner pentagon
		radius = bbox.getBase() * 0.20081141588622725;
		for (int i = 0; i < 5; i++) {
			float th = M_PI * 1.5 + (i - 2) * 2.0 * M_PI / 5.0;
			pnt[i * 2 + 1].x = center.x + radius * cos(th);
			pnt[i * 2 + 1].y = center.y + radius * sin(th);
		}
	}

	string getName() {
		return "Star";
	}
};