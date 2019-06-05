#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "algo.h"
#include <chrono>
using namespace std;

vector<threeDim> coordinates;

//Note that for this first assignment all the beginnig indexs will be 0 since we are creating one NURBS surface

/*NURBS defined by:*/

//two orders k and l
//Index of Surfaces --> Index for orders on a single surface
vector<orders> nurbOrderVec;

//control points d_ij = (x_ij, y_ij, z_ij)^Transpose, i = 0, ... , m   j = 0, ... , n
//Index of Surfaces --> Index for control points on a single surface
vector<cpDim> cpDimensions;
vector<vector<vector<threeDim>>> controlPoints;

//real weights w_ij, i = 0, ... , m  j = 0, ... , n
//Index of Surfaces --> Index for weights on a single surface
vector<vector<vector<double>>> weights;

//a set of real u-knots, {u_0, ..., u_m+k | u_i <= u_i+1, i = 0, ..., (m + k - 1)}
//Index of Surfaces --> Index for weights on a single surface
vector<vector<double>> uKnots;

//a set of real v-knots, {v_0, ..., v_n+l | v_j <= v_j+1, j = 0, ..., (n + l - 1)}
vector<vector<double>> vKnots;

//One global resolution for all NURBS

int res = 0;


int pointsNum = 0;



algo ag;

/*
void BSplineCalcRe()
{

	cout << "Curve 0: " << endl;
	for (int j = 0; j < BernsteinCurves[0].size(); j++)
	{
		cout << "  Index: " << j << " " << BernsteinCurves[0][j].x << ", " << BernsteinCurves[0][j].y << endl;
	}

	cout << "Please send me the curve you want to modify and the proper modifications [Index Number] [(I)nsert/(D)elete]" << endl;
	int iNum;
	cin >> iNum;

	string insDel;
	cin >> insDel;

	if (insDel == "I")
	{
		cout << "What are the coordinates?" << endl;
		double xcoor;
		double ycoor;
		cin >> xcoor >> ycoor;
		BernsteinCurves[0].insert(BernsteinCurves[0].begin() + iNum, {xcoor, ycoor});
	}
	else
	{
		BernsteinCurves[0].erase(BernsteinCurves[0].begin() + iNum);
	}

	cout << "Current order is " << order << ", what would you like you new order to be?" << endl;
	cin >> order;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.deBoors(BernsteinCurves[k], order, res);
	}
	glutSwapBuffers();
	BSplineCalcRe();
}
*/

void NURBSCalc()
{
	cout << "Hello! What are the orders of your 3D NURBS Curve?" << endl;
	int order1;
	int order2;
	cin >> order1 >> order2;
	orders orderCombo = {order1, order2};
	nurbOrderVec.push_back(orderCombo);


	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;

	string rowCP;
	string columnCP;
	cout << "Hello! What are the dimensions of the control points of your NURBs Curve?" << endl;
	cin >> rowCP >> columnCP;
	cpDim pair = {stoi(rowCP), stoi(columnCP)};
	cpDimensions.push_back(pair);

	/*
	cout << "Please enter your " << points << " control points. Format: x y" << endl;
	//loop over the number of control points
	for (int i = 0; i < stoi(points); i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY>>
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});
	}
	controlPoints.push_back(coordinates);
	coordinates.clear();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < controlPoints.size(); k++)
	{

	}
	*/
	glutSwapBuffers();
}

void promptUser(void)
{
	NURBSCalc();
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	promptUser();
}


int main(int argc, char **argv)
{

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400,200);
	glutInitWindowSize(800,800);
	glutCreateWindow("Homework 4");
	// register callbacks
	glutDisplayFunc(renderScene);
	cout << "The dimensions of the window is 800 by 800, the bottom left is (0, 0)" << endl;
	glutMainLoop();
	// enter GLUT event processing cycle
	return 1;
}
