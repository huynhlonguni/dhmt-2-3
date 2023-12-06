#pragma once

#include "polygon.h"

class BakedShape : public Polygon {
protected:
	vector<Vector2> coords; //normalized coordinates
public:
	BakedShape(int vertexCount, bool squareShape) : Polygon(vertexCount, squareShape), coords(vertexCount) {}

	virtual void fitBoundingBox(Vector2 start, Vector2 end) {
		Vector2 lt, rb;
		bbox.getBoundingBox(lt, rb);

		float width = bbox.getWidth();
		float height = bbox.getHeight();

		for (int i = 0; i < pnt.size(); i++) {
			pnt[i].x = coords[i].x * width + lt.x;
			pnt[i].y = coords[i].y * height + rb.y;
		}
	} 
};