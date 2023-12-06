#pragma once

#include <GL/glut.h>
#include <math.h>

class Util {
public:
	static float getDistance(Vector2 a, Vector2 b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;

		return sqrt(dx * dx + dy * dy);
	}

	static float getDistanceToLine(Vector2 p, Vector2 l1, Vector2 l2) {
		float dx = l1.x - l2.x;
		float dy = l1.y - l2.y;

		if (dx == 0) { //Vertical line
			return abs(l1.x - p.x);
		}

		if (dy == 0) { //Horizontal line
			return abs(l1.y - p.y);
		}

		return abs(dx * (l2.y - p.y) - (l2.x - p.x) * dy) / sqrt(dx * dx + dy * dy);
	}

	//Check if point is inside the region perpendicular to the line, cut off by its endpoints
	static bool isOnSideOfLine(Vector2 p, Vector2 l1, Vector2 l2) {
		float side1 = getDistance(p, l1);
		float side2 = getDistance(p, l2);
		float length = getDistance(l1, l2);

		float side = side1 > side2 ? side1 : side2;
		float dist = getDistanceToLine(p, l1, l2);

		//Pythagorean theorem
		return (side * side - dist * dist) <= (length * length); 
	}

	static void drawDashedLine(Vector2 start, Vector2 end) {
		const int num = 40;
		const Color lineColor(0, 0, 0);

		Vector2 s, e;

		glBegin(GL_LINES);
		Color::setColor(lineColor);
		for (int i = 0; i < num; i ++) {
			float t = i / (float)(num - 1);
			if (i % 2 == 0) {
				s.x = (1 - t) * start.x + t * end.x;
				s.y = (1 - t) * start.y + t * end.y;
			}
			else {
				e.x = (1 - t) * start.x + t * end.x;
				e.y = (1 - t) * start.y + t * end.y;
				Vector2::setVertex(s);
				Vector2::setVertex(e);
			}
		}
		glEnd();
	}

	static void drawControlPoint(Vector2 pnt) {
		const int size = 6;
		const int outline = 1;
		const Color outlineColor(0, 0, 0);
		const Color fillColor(255, 255, 255);

		const int innerSize = size - outline * 2;

		glBegin(GL_QUADS);
		Color::setColor(outlineColor);
		Vector2::setVertex(pnt.x - size / 2, pnt.y - size / 2);
		Vector2::setVertex(pnt.x + size / 2, pnt.y - size / 2);
		Vector2::setVertex(pnt.x + size / 2, pnt.y + size / 2);
		Vector2::setVertex(pnt.x - size / 2, pnt.y + size / 2);

		Color::setColor(fillColor);
		Vector2::setVertex(pnt.x - innerSize / 2, pnt.y - innerSize / 2);
		Vector2::setVertex(pnt.x + innerSize / 2, pnt.y - innerSize / 2);
		Vector2::setVertex(pnt.x + innerSize / 2, pnt.y + innerSize / 2);
		Vector2::setVertex(pnt.x - innerSize / 2, pnt.y + innerSize / 2);
		glEnd();
	}
};