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
	app.handleMouse(button, state, x, app.getHeight() - y);
}

void mouse_callback_down(int x, int y) {
	app.handleMouseDown(x, app.getHeight() - y);
}

void resize_callback(int width, int height) {
	app.setupViewport(width, height);
	app.handleResize(width, height);
}

void normal_key_callback(unsigned char key, int x, int y) {
	app.handleNormalKey(key, x, y);
}

void special_key_callback(int key, int x, int y) {
	app.handleSpecialKey(key, x, y);
}

void display_callback() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	app.run();
	glutSwapBuffers();
}

void init(int width, int height) {
	app.setupViewport(width, height);
	app.createMenu(menu_callback);
	
	glutMouseFunc(mouse_callback);
	glutMotionFunc(mouse_callback_down);
	glutReshapeFunc(resize_callback);
	glutKeyboardFunc(normal_key_callback);
	glutSpecialFunc(special_key_callback);
	glutDisplayFunc(display_callback);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - SCREEN_WIDTH / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - SCREEN_HEIGHT / 2);

	glutCreateWindow("Computer Graphics");

	init(SCREEN_WIDTH, SCREEN_HEIGHT);

	glutMainLoop();

	return 0;
}
