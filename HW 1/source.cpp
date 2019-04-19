#include <GL/glut.h>
#include <iostream>
#include "algo.h"
using namespace std;

vector<vector<dim>> curves;
vector<dim> coordinates;
dim coor;

algo ag;


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINES);
		glVertex2f(-0.5,-0.5);
		glVertex2f(0.5,0.0);
		glVertex2f(0.0,0.5);
	glEnd();
	coor = {-0.5,-0.5};
	coordinates.push_back(coor);
	coor = {0.5,0.0};
	coordinates.push_back(coor);
	coor = {0.0,0.5};
	coordinates.push_back(coor);
	ag.deCastlejau(coordinates);

  glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400,200);
	glutInitWindowSize(800,800);
	glutCreateWindow("Homework 1");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
