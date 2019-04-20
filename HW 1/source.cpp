#include <GL/glut.h>
#include <iostream>
#include "algo.h"
using namespace std;

vector<vector<dim>> curves;
vector<dim> coordinates;

//Store the Castlehau Curves and its t Values
vector<vector<dim>> CastlejauCurves;
vector<double> tValues;

int pointsNum = 0;

algo ag;

void promptUser(void)
{
	//Separate the Bernstein-Casteljau Drawing Window and the Curve-Curve Intersection Window
	//Bezier Curve Prompt
	cout << "Hello! How many coordinates are on your control polygon?" << endl;
	cin >> pointsNum;
	cout << "Please enter your " << pointsNum << " control points. Format: x y" << endl;
	//loop over the number of control points
	for (int i = 0; i < pointsNum; i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY;
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});
	}
	ag.deCastlejau(coordinates, 0.2);
	coordinates.clear();


}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	promptUser();
	/*
	coor = {-0.75,-0.5};
	coordinates.push_back(coor);
	coor = {0.5,0.0};
	coordinates.push_back(coor);
	coor = {0.0,0.5};
	coordinates.push_back(coor);
	ag.deCastlejau(coordinates);
	coordinates.clear();
	*/
  glutSwapBuffers();
}


int main(int argc, char **argv)
{

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400,200);
	glutInitWindowSize(800,800);
	glutCreateWindow("Homework 1");
	// register callbacks
	glutDisplayFunc(renderScene);
	cout << "The dimensions of the window is 800 by 800, the bottom left is (0, 0)" << endl;


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
