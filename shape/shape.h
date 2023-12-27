#pragma once

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "../type/primitive.h"
#include "../type/bounding_box.h"
#include "../type/matrix.h"
#include "../type/shape_framebuffer.h"
#include "../type/clock.h"
#include "../fill/boundary_filler.h"
#include "../fill/flood_filler.h"
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
	bool showBoundingBox = false;

	ShapeFramebuffer fbo;

	Color outlineColor = {0, 0, 0, 255};
	Color fillColor = {0, 0, 0, 0};

protected:

	virtual void fitBoundingBox(Vector2 start, Vector2 end) = 0;

	virtual void render(ShapeFramebuffer *drawer) = 0;

public:
	Shape(bool squareShape) : squareShape(squareShape) {
		fbo.setFillFunction(BoundaryFiller::fill);
	}

	~Shape() {}

	void draw() {
		fbo.draw(outlineColor, fillColor);
	}

	virtual void setOutlineColor(Color col) {
		outlineColor = col;
	}

	virtual void setFillColor(Color col) {
		fillColor = col;
	}

	void toggleBoundingBox(bool show) {
		showBoundingBox = show;
	}

	void drawBoundingBox() {
		if (showBoundingBox) bbox.draw();
	}

	virtual bool containsPoint(Vector2 p) {
		return fbo.containsPoint(p);
	}

	unsigned int getShapeArea() {
		return fbo.getShapeArea();
	}

	void fitShape(Vector2 start, Vector2 end) {
		bbox.reshape(start, end, squareShape);
		fitBoundingBox(start, end);

		fbo.reshape(bbox);
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
		const float rad = M_PI / 180.0;

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

		fbo.applyTransformationMatrix(transform);
		fbo.reshape(bbox);

		renderShape();

		Vector2 fillCenter = transform.transformPoint(shapeCenter);
		fillShape(fillCenter);
	}

	virtual void log(int i = 0, char type = 0) {
		if (type == 0)
			cout << "Rendered";
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