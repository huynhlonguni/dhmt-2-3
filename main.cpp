#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include "app.h"
using namespace std;

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

App app(SCREEN_WIDTH, SCREEN_HEIGHT);

void menu_callback(int opt) {
	app.handleMenu(opt);
}

void mouse_callback(int button, int state, int x, int y) {
	app.handleMouse(button, state, x, SCREEN_HEIGHT - y);
}

void mouse_callback_down(int x, int y) {
	app.handleMouseDown(x, SCREEN_HEIGHT - y);
}

void resize_callback(int width, int height) {
	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void normal_key_callback(unsigned char key, int x, int y) {
	app.handleNormalKey(key, x, y);
}

void special_key_callback(int key, int x, int y) {
	app.handleSpecialKey(key, x, y);
}

void initMenu() {
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

void init(void) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	initMenu();
	glutMouseFunc(mouse_callback);
	glutMotionFunc(mouse_callback_down);
	glutReshapeFunc(resize_callback);
	glutKeyboardFunc(normal_key_callback);
	glutSpecialFunc(special_key_callback);
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	app.run();
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - SCREEN_WIDTH / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - SCREEN_HEIGHT / 2);

	glutCreateWindow("Computer Graphics");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
