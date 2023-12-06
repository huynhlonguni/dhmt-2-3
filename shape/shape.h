#pragma once

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "../type/primitive.h"
#include "../type/bounding_box.h"
#include "../type/matrix.h"
#include "../type/shape_framebuffer.h"
#include "../type/clock.h"
#include "../fill/boundary_fill.h"
#include "../fill/flood_fill.h"
using namespace std;

class Shape {
protected:
	Clock clock;
	float drawTime = 0;
	float fillTime = 0;

	Vector2 trans = {0, 0};
	float rot = 0.0;
	float zoom = 1.0;

	BoundingBox bbox;
	const bool squareShape;
	bool drawBbox = false;

	ShapeFramebuffer fbo;

protected:

	virtual void fitBoundingBox(Vector2 start, Vector2 end) = 0;

	virtual void render(ShapeFramebuffer *drawer) = 0;

public:
	Shape(bool squareShape) : squareShape(squareShape) {}

	~Shape() {}

	void init(int w, int h) {
		fbo.resize(w, h);
		fbo.setFillFunction(boundaryFill);
	}

	void draw() {
		fbo.draw(bbox);

		if (drawBbox) bbox.draw();
	}

	void toggleBoundingBox(bool show) {
		drawBbox = show;
	}

	virtual bool containsPoint(Vector2 p) {
		return fbo.containsPoint(p);
	}

	unsigned int getShapeArea() {
		return fbo.getShapeArea(bbox);
	}

	virtual void setOutlineColor(Color col) {
		fbo.setOutlineColor(col);
	}

	virtual void setFillColor(Color col) {
		fbo.setFillColor(col);
	}

	void fitShape(Vector2 start, Vector2 end) {
		bbox.reshape(start, end, squareShape);
		fitBoundingBox(start, end);

		fbo.clear();
		renderShape();
	}

	virtual void renderShape() {
		clock.start();
		render(&fbo);
		drawTime = clock.end();
	}

	virtual void fillShape(Vector2 center) {
		clock.start();
		fbo.fill((int)center.x, (int)center.y);
		fillTime = clock.end();
	}

	void translate(float x, float y) {
		trans.x += x;
		trans.y += y;

		applyTransform();
	}

	void rotate(float degree) {
		const float rad = 0.017453292519943295;

		rot += degree * rad;

		applyTransform();
	}

	void scale(float amount) {
		zoom += amount;
		if (zoom <= 0.0) zoom = 0.0;

		applyTransform();
	}

	void applyTransform() {
		const bool useShapeCenter = false;

		Vector2 bboxCenter = bbox.getCenter();
		Vector2 shapeCenter = getCenter();

		Vector2 transformCenter = bboxCenter;
		if (useShapeCenter) transformCenter = shapeCenter;

		Matrix transform;
		transform.translate(trans.x + transformCenter.x, trans.y + transformCenter.y);
		transform.rotate(rot);
		transform.scale(zoom, zoom);
		transform.translate(-transformCenter.x, -transformCenter.y);

		bbox.applyTransformationMatrix(transform);

		Vector2 fillCenter = transform.transformPoint(shapeCenter);

		fbo.applyTransformationMatrix(transform);

		fbo.clear();
		renderShape();
		fillShape(fillCenter);
	}

	virtual void log(int i = 0, char type = 0) {
		if (type == 0)
			cout << "Drawn";
		else if (type == 1)
			cout << "Transformed";


		if (i) cout << " shape #" << i;
		cout << ": " << getName() << endl;
		cout << "Draw time: " << drawTime << "ms\n";;
		cout << "Fill time: " << fillTime << "ms\n";;
		cout << endl;
	}

	virtual Vector2 getCenter() = 0;

	virtual string getName() = 0;

};