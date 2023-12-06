#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
	const int width;
	const int height;

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
	Shape* createShape(ContextOption opt) {
		switch (currentOption) {
			case CTX_LINE:
				shapes.push_back(new SLine()); break;
			case CTX_TRI_ISOS_RIGHT:
				shapes.push_back(new SIsoscelesRightTriangle()); break;
			case CTX_TRI_EQUIL:
				shapes.push_back(new SEquilateralTriangle()); break;
			case CTX_RECT:
				shapes.push_back(new SRectangle()); break;
			case CTX_SQUARE:
				shapes.push_back(new SSquare()); break;
			case CTX_CIRCLE:
				shapes.push_back(new SCircle()); break;
			case CTX_ELLIPSE:
				shapes.push_back(new SEllipse()); break;
			case CTX_PENTAGON:
				shapes.push_back(new SPentagon()); break;
			case CTX_HEXAGON:
				shapes.push_back(new SHexagon()); break;
			case CTX_ARROW:
				shapes.push_back(new SArrow()); break;
			case CTX_STAR:
				shapes.push_back(new SStar()); break;
			case CTX_SIGN_PLUS:
				shapes.push_back(new SPlusSign()); break;
			case CTX_SIGN_MINUS:
				shapes.push_back(new SMinusSign()); break;
			case CTX_SIGN_MULTIPLY:
				shapes.push_back(new SMultiplySign()); break;
			case CTX_SIGN_DIVIDE:
				shapes.push_back(new SDivideSign()); break;
			default:
				return nullptr;
		}

		shapes.back()->init(width, height);
		return shapes.back();
	}

	void deselectCurrentShape() {
		if (activeShape) activeShape->toggleBoundingBox(false);
		activeShape = nullptr;
		glutPostRedisplay();
	}

	void selectOneShape(Shape *sh) {
		deselectCurrentShape();

		activeShape = sh;
		if (activeShape) activeShape->toggleBoundingBox(true);
		glutPostRedisplay();
	}

public:
	App(int w, int h) : width(w), height(h) {
		srand(time(NULL));
	}

	void run() {
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->draw();
		}
	}

	~App() {
		for (int i = 0; i < shapes.size(); i++)
			delete shapes[i];
	}

	void handleMenu(int opt) {
		currentOption = (ContextOption)opt;

		if (opt > CTX_SHAPE_START && opt < CTX_SHAPE_END) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			deselectCurrentShape();
			currentAction = ACTION_DRAWING;
		}
		else if (opt > CTX_COLOR_START && opt < CTX_COLOR_END) {
			glutSetCursor(GLUT_CURSOR_INFO);
			currentAction = ACTION_PICKING; //Allow continuing picking
			switch (opt) {
				case CTX_COLOR_BLUE:
					currentColor = Color(0, 0, 255);
					break;
				case CTX_COLOR_RED:
					currentColor = Color(255, 0, 0);
					break;
				case CTX_COLOR_YELLOW:
					currentColor = Color(255, 255, 0);
					break;
			}
			if (activeShape) {
				activeShape->setFillColor(currentColor);
				glutPostRedisplay();
			}
		}
		else if (opt == CTX_PICK) {
			glutSetCursor(GLUT_CURSOR_INFO);
			currentAction = ACTION_PICKING;
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			currentAction = ACTION_NONE;
		}
	}

	void handleMouseDown(int x, int y) {
		if (leftMouseDown) {
			if (currentAction == ACTION_DRAWING) {
				activeShape->fitShape(prevLeftMouse, Vector2(x, y));
				glutPostRedisplay();
			}
		}
	}

	void handleMouse(int button, int state, int x, int y) {
		if (currentAction == ACTION_DRAWING) {
			if (button == GLUT_LEFT_BUTTON) {
				if (state == GLUT_DOWN) {
					leftMouseDown = true;
					prevLeftMouse = Vector2(x, y);

					Shape *newShape = createShape(currentOption);
					selectOneShape(newShape);
				}
				else {
					leftMouseDown = false;
					if (activeShape) {
						activeShape->fillShape(activeShape->getCenter());

						if (activeShape->getShapeArea() <= 4 * 4) {
							cout << "Shape is too small\n\n";
							delete activeShape;
							shapes.pop_back();
							activeShape = nullptr;
						}
						else {
							activeShape->log(shapes.size());
						}
						deselectCurrentShape();
					}
				}
			}
		}
		else if (currentAction == ACTION_PICKING) {
			if (button == GLUT_LEFT_BUTTON) {
				if (state == GLUT_DOWN) {
					Vector2 pnt(x, y);

					int i = shapes.size() - 1;
					for (; i >= 0; i--) {
						if (shapes[i]->containsPoint(pnt)) {
							selectOneShape(shapes[i]);
							break;
						}
					}
					if (i < 0) { //No shape is selected
						//A transform session is finished, log new draw & fill time after transformation
						if (transformingShape && activeShape) {
							int idx = 0;
							for (; idx < shapes.size(); idx++)
								if (shapes[idx] == activeShape)
									break;

							if (idx < shapes.size()) {
								activeShape->log(idx + 1, 1);
							}
						}
						transformingShape = false;				
						deselectCurrentShape();
					}
				}
			}

		}
	}

	void handleNormalKey(unsigned char key, int x, int y) {
		switch (key) {
			case 'l': handleKey(INPUT_KEY_L); break;
			case 'r': handleKey(INPUT_KEY_R); break;
			case '+': handleKey(INPUT_KEY_PLUS); break;
			case '=': handleKey(INPUT_KEY_PLUS); break;
			case '-': handleKey(INPUT_KEY_MINUS); break;
		}

	}

	void handleSpecialKey(int key, int x, int y) {
		switch (key) {
			case GLUT_KEY_UP: handleKey(INPUT_ARROW_UP); break;
			case GLUT_KEY_DOWN: handleKey(INPUT_ARROW_DOWN); break;
			case GLUT_KEY_LEFT: handleKey(INPUT_ARROW_LEFT); break;
			case GLUT_KEY_RIGHT: handleKey(INPUT_ARROW_RIGHT); break;
		}
	}

	void handleKey(InputOption key) {
		if (!activeShape) return;

		if (key > INPUT_TRANSFORM_START && key < INPUT_TRANSFORM_END)
			transformingShape = true;

		switch (key) {
			case INPUT_KEY_L:
				activeShape->rotate(1);
				break;
			case INPUT_KEY_R:
				activeShape->rotate(-1);
				break;
			case INPUT_KEY_PLUS:
				activeShape->scale(0.1);
				break;
			case INPUT_KEY_MINUS:
				activeShape->scale(-0.1);
				break;
			case INPUT_ARROW_UP:
				activeShape->translate(0, 1);
				break;
			case INPUT_ARROW_DOWN:
				activeShape->translate(0, -1);
				break;
			case INPUT_ARROW_LEFT:
				activeShape->translate(-1, 0);
				break;
			case INPUT_ARROW_RIGHT:
				activeShape->translate(1, 0);
				break;
		}

		glutPostRedisplay();
	}
};