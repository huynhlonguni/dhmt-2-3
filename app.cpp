#include "app.h"

Shape* App::createShape(ContextOption opt) {
	switch (currentOption) {
		case CTX_LINE:
			shapes.push_back(new SStraightLine()); break;
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

	return shapes.back();
}

void App::deselectCurrentShape() {
	if (activeShape) activeShape->toggleBoundingBox(false);
	activeShape = nullptr;
	glutPostRedisplay();
}

void App::selectShape(Shape *sh) {
	if (activeShape) activeShape->toggleBoundingBox(false);

	activeShape = sh;
	if (activeShape) activeShape->toggleBoundingBox(true);
	glutPostRedisplay();
}

int App::getShapeIndex(Shape *sh) {
	for (int idx = 0; idx < shapes.size(); idx++)
		if (shapes[idx] == sh)
			return idx;

	return -1;
}

void App::transformFinalize(Shape *sh) {
	if (sh) {
		int idx = getShapeIndex(sh);
		sh->log(idx + 1, 1);		
	}
}

App::App(int w, int h) : width(w), height(h) {
	srand(time(NULL));
}

void App::run() {
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}
	
	if (activeShape)
		activeShape->drawBoundingBox();
}

App::~App() {
	for (int i = 0; i < shapes.size(); i++)
		delete shapes[i];
}

int App::getWidth() {
	return width;
}

int App::getHeight() {
	return height;
}

void App::setupViewport(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void App::createMenu(void (*menu_callback)(int)) {
	if (!menu_callback) return;

	int triangle = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Vuong can", App::CTX_TRI_ISOS_RIGHT);
	glutAddMenuEntry("Deu", App::CTX_TRI_EQUIL);

	int rectangle = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Hinh chu nhat", App::CTX_RECT);
	glutAddMenuEntry("Hinh vuong", App::CTX_SQUARE);

	int oval = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Hinh tron", App::CTX_CIRCLE);
	glutAddMenuEntry("Elip", App::CTX_ELLIPSE);

	int polygon = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Ngu giac deu", App::CTX_PENTAGON);
	glutAddMenuEntry("Luc giac deu", App::CTX_HEXAGON);

	int other = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Mui ten", App::CTX_ARROW);
	glutAddMenuEntry("Ngoi sao", App::CTX_STAR);

	int sign = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Cong", App::CTX_SIGN_PLUS);
	glutAddMenuEntry("Tru", App::CTX_SIGN_MINUS);
	glutAddMenuEntry("Nhan", App::CTX_SIGN_MULTIPLY);
	glutAddMenuEntry("Chia", App::CTX_SIGN_DIVIDE);

	int color = glutCreateMenu(menu_callback);
	glutAddMenuEntry("Xanh", App::CTX_COLOR_BLUE);
	glutAddMenuEntry("Do", App::CTX_COLOR_RED);
	glutAddMenuEntry("Vang", App::CTX_COLOR_YELLOW);

	glutCreateMenu(menu_callback);
	glutAddMenuEntry("Duong thang", App::CTX_LINE);
	glutAddSubMenu("Tam giac", triangle);
	glutAddSubMenu("Tu giac", rectangle);
	glutAddSubMenu("Oval", oval);
	glutAddSubMenu("Da giac deu", polygon);
	glutAddSubMenu("Hinh khac", other);
	glutAddSubMenu("Dau", sign);
	glutAddSubMenu("To mau", color);
	glutAddMenuEntry("Chon hinh", App::CTX_PICK);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void App::handleMenu(int opt) {
	currentOption = (ContextOption)opt;

	if (opt > CTX_SHAPE_START && opt < CTX_SHAPE_END) {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		//Action changed, transform session has ended, log transform time
		if (transformingShape && activeShape) {
			transformFinalize(activeShape);
			transformingShape = false;
		}
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

void App::handleMouseDown(int x, int y) {
	if (leftMouseDown) {
		if (currentAction == ACTION_DRAWING) {
			if (activeShape)
				activeShape->fitShape(prevLeftMouse, Vector2(x, y));
			glutPostRedisplay();
		}
	}
}

void App::handleMouse(int button, int state, int x, int y) {
	if (currentAction == ACTION_DRAWING) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				leftMouseDown = true;
				prevLeftMouse = Vector2(x, y);

				Shape *newShape = createShape(currentOption);
				selectShape(newShape);
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
				Shape *previousShape = activeShape;

				int i = shapes.size() - 1;
				for (; i >= 0; i--) {
					if (shapes[i]->containsPoint(pnt)) {
						selectShape(shapes[i]);
						break;
					}
				}
				if (i < 0) //No shape is selected
					deselectCurrentShape();

				//A transform session is finished, log new draw & fill time after transformation
				if (transformingShape && previousShape && previousShape != activeShape) {
					transformFinalize(previousShape);
					transformingShape = false;
				}
			}
		}
	}
}

void App::handleNormalKey(unsigned char key, int x, int y) {
	switch (key) {
		case 'l': handleKey(INPUT_KEY_L); break;
		case 'r': handleKey(INPUT_KEY_R); break;
		case '+': handleKey(INPUT_KEY_PLUS); break;
		case '=': handleKey(INPUT_KEY_PLUS); break;
		case '-': handleKey(INPUT_KEY_MINUS); break;
	}

}

void App::handleSpecialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: handleKey(INPUT_ARROW_UP); break;
		case GLUT_KEY_DOWN: handleKey(INPUT_ARROW_DOWN); break;
		case GLUT_KEY_LEFT: handleKey(INPUT_ARROW_LEFT); break;
		case GLUT_KEY_RIGHT: handleKey(INPUT_ARROW_RIGHT); break;
	}
}

void App::handleKey(InputOption key) {
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

void App::handleResize(int w, int h) {
	width = w;
	height = h;
}