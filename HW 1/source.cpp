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

	coor = {-0.75,-0.5};
	coordinates.push_back(coor);
	coor = {0.5,0.0};
	coordinates.push_back(coor);
	coor = {0.0,0.5};
	coordinates.push_back(coor);
	ag.deCastlejau(coordinates);
	coordinates.clear();
  glutSwapBuffers();
}

void processMenuEvents(int option)
{

	switch (option)
	{
		case 1 :
			break;
		case 2 :
			break;
		case 3 :
			break;
		case 4 :
			break;
	}
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

	//glutCreateWindow("Options Menu");
//	glutDisplayFunc(renderScene);
	int menu = glutCreateMenu(processMenuEvents);

	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Blue",2);
	glutAddMenuEntry("Green",3);
		glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Colors", menu);

	glutAddMenuEntry("Exit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
