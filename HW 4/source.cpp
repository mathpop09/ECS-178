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


	//resize
	vector<vector<vector<threeDim>>> controlPoints;
	controlPoints.resize(1);
	weights.resize(1);

	//TODO CHANGE, FOR PROJECT LATER ON
	controlPoints[0].resize(pair.row);
	weights[0].resize(pair.row);

	for (int i = 0; i < pair.row; i++)
	{
		controlPoints[0][i].resize(pair.col);
		weights[0][i].resize(pair.col);
	}



	cout << "Please enter your control points. Format: x y z" << endl;
	cout << "After you add each control point, please enter the weight" << endl;

	//loop over the number of control points
	for (int i = 0; i < cpDimensions[0].row; i++)
	{
		for (int j = 0; j < cpDimensions[0].col; j++)
		{
			double coorX = 0;
			double coorY = 0;
			double coorZ = 0;
			double weight = 0;
			cout << "Control Point " << i << "," << j << ":" << endl;
			cin >> coorX >> coorY >> coorZ;
			cout << "Weight " << i << "," << j << ":" << endl;
			cin >> weight;
			controlPoints[0][i][j] = {coorX, coorY, coorZ};
			weights[0][i][j] = weight;
		}
	}

	vector<double> uSKnots;
	vector<double> vSKnots;
	cout << "Please enter your u-knots set of size: " <<  pair.row + order1 << ". Formating: 1 2 3 4 5..." << endl;
	for (int i = 0; i < pair.row + order1; i++)
	{
		double knotVal;
		cin >> knotVal;
		uSKnots.push_back(knotVal);
	}
	uKnots.push_back(uSKnots);

	cout << "Please enter your v-knots set of size: " <<  pair.row + order1 << ". Formating: 1 2 3 4 5..." << endl;
	for (int i = 0; i < pair.col + order1; i++)
	{
		double knotVal;
		cin >> knotVal;
		vSKnots.push_back(knotVal);
	}
	vKnots.push_back(vSKnots);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	glColor3f(1,1,0);
	glBegin(GL_LINES);

	//Draw the control polygon

	for (int i = 0; i < pair.row; i++)
	{
		for (int j = 0; j < pair.col; j++)
		{
				// if last row
				if ((i == pair.row - 1) && (j != pair.col - 1))
				{
					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i][j+1].x, controlPoints[0][i][j+1].y, controlPoints[0][i][j+1].z);

				}
				//if last col
				else if ((j == pair.col - 1) && (i != pair.row - 1))
				{
					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i+1][j].x, controlPoints[0][i+1][j].y, controlPoints[0][i+1][j].z);

				}
				//if anything else
				else if ((i != pair.row - 1) && (i != pair.col - 1))
				{

					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i+1][j].x, controlPoints[0][i+1][j].y, controlPoints[0][i+1][j].z);

					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i][j+1].x, controlPoints[0][i][j+1].y, controlPoints[0][i][j+1].z);

				}
		}
	}

	glEnd();

	for (int k = 0; k < controlPoints.size(); k++)
	{
		ag.NURBS(nurbOrderVec[k], controlPoints[k], weights[k], uKnots[k], vKnots[k], res);
	}
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
