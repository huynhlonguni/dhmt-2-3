#pragma once

#include <math.h>
#include "../polygon.h"

class SLine : public Polygon {
public:
	SLine() : Polygon(2, false) {}

	SLine(Vector2 p1, Vector2 p2) : Polygon(2, false) {
		pnt[0] = p1;
		pnt[1] = p2;
	}

	void fitBoundingBox(Vector2 start, Vector2 end) {
		pnt[0] = start;
		pnt[1] = end;
	}

	//Since a line is so thin, this function is overloaded to additionally check its surrounding areas
	virtual bool containsPoint(Vector2 p) {
		const float maxDist = 30;
		const float expansion = 15;
		const float minBoxSize = 5;

		if (!Util::isOnSideOfLine(p, pnt[0], pnt[1])) return false;

		float dist = Util::getDistanceToLine(p, pnt[0], pnt[1]);
		
		return dist <= maxDist;
	}

	//Line only uses outlineColor
	virtual void setFillColor(Color col) {
		fbo.setOutlineColor(col);
	}

	virtual void fillShape(Vector2 center) {
		//Do nothing;
	}

	string getName() {
		return "Line";
	}
};