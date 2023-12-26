#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include "shape/shapes.h"
using namespace std;

class App {
public:
	enum ContextOption {
		CTX_NONE = 0,

		CTX_SHAPE_START,
		CTX_LINE,
		CTX_TRI_ISOS_RIGHT,
		CTX_TRI_EQUIL,
		CTX_RECT,
		CTX_SQUARE,
		CTX_CIRCLE,
		CTX_ELLIPSE,
		CTX_PENTAGON,
		CTX_HEXAGON,
		CTX_ARROW,
		CTX_STAR,
		CTX_SIGN_PLUS,
		CTX_SIGN_MINUS,
		CTX_SIGN_MULTIPLY,
		CTX_SIGN_DIVIDE,
		CTX_SHAPE_END,

		CTX_COLOR_START,
		CTX_COLOR_BLUE,
		CTX_COLOR_RED,
		CTX_COLOR_YELLOW,
		CTX_COLOR_END,

		CTX_PICK,
	};

	enum InputOption {
		INPUT_NONE = 0,


		INPUT_TRANSFORM_START,
		INPUT_KEY_L,
		INPUT_KEY_R,
		INPUT_KEY_PLUS,
		INPUT_KEY_MINUS,
		INPUT_ARROW_UP,
		INPUT_ARROW_DOWN,
		INPUT_ARROW_LEFT,
		INPUT_ARROW_RIGHT,
		INPUT_TRANSFORM_END,
	};

private:
	int width;
	int height;

	vector<Shape*> shapes;
	Shape *activeShape = nullptr;

	ContextOption currentOption = CTX_NONE;
	Color currentColor;
	
	enum {
		ACTION_NONE = 0,
		ACTION_DRAWING,
		ACTION_PICKING,
	} currentAction = ACTION_NONE;

	bool leftMouseDown = false;
	Vector2 prevLeftMouse = {0, 0};
	bool transformingShape = false;


private:
	Shape* createShape(ContextOption opt);

	void deselectCurrentShape();

	void selectShape(Shape *sh);

	int getShapeIndex(Shape *sh);

	void transformFinalize(Shape *sh);

public:
	App(int w, int h);

	void run();

	~App();

	int getWidth();

	int getHeight();

	void setupViewport(int w, int h);

	void createMenu(void (*menu_callback)(int));

	void handleMenu(int opt);

	void handleMouseDown(int x, int y);

	void handleMouse(int button, int state, int x, int y);

	void handleNormalKey(unsigned char key, int x, int y);

	void handleSpecialKey(int key, int x, int y);

	void handleKey(InputOption key);

	void handleResize(int w, int h);
};