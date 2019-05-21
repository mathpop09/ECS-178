#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "algo.h"
#include <chrono>
using namespace std;

vector<vector<dim>> curves;
vector<dim> coordinates;

//Store the Bernstein Curves
vector<vector<dim>> BernsteinCurves;

//Stors the derivative vectors for the curve
vector<bSpline> bSplines;

int pointsNum = 0;

int res = 0;

int realPType = 0;

algo ag;

int order = 0;

dim vector1;

dim vector2;

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

void BSplineCalc()
{
	cout << "Hello! What order is your B-Spline Curve? (de Boors)" << endl;
	cin >> order;
	string points;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
	cout << "Hello! How many control points is your B-Spline Curve? (de Boors)" << endl;
	cin >> points;
	cout << "Please enter your " << points << " control points. Format: x y" << endl;
	//loop over the number of control points
	for (int i = 0; i < stoi(points); i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY;
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});
	}
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.deBoors(BernsteinCurves[k], order, res);
	}
	glutSwapBuffers();
	BSplineCalcRe();
}

void NaturalCubicSplineRe()
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

	cout << "get here" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.c2Algo(BernsteinCurves[k], realPType, res);
	}
	glutSwapBuffers();
	NaturalCubicSplineRe();
}

void NaturalCubicSpline()
{
	string points;
	cout << "Hello! How many points would you like to interpolate?" << endl;
	cin >> points;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
	string pType;
	cout << "What kind of parametrization do you desire? [U]niform/[C]hord Length/C[E]ntripidal Parametrization" << endl;
	cin >> pType;
	if (pType == "U")
	{
		realPType = 1;
	}
	else if (pType == "C")
	{
		realPType = 2;
	}
	else if (pType == "E")
	{
		realPType = 3;
	}
	cout << "Please enter your " << points << " control points. Format: x y" << endl;
	//loop over the number of control points
	for (int i = 0; i < stoi(points); i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY;
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});
	}
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.c2Algo(BernsteinCurves[k], realPType, res);
	}
	glutSwapBuffers();
	NaturalCubicSplineRe();
}

void QuadInterpolationRe()
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.c1Algo(BernsteinCurves[k], vector1, vector2, res);
	}
	glutSwapBuffers();
	QuadInterpolationRe();
}

void QuadInterpolation()
{
	string points;
	cout << "Hello! How many points would you like to interpolate?" << endl;
	cin >> points;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
	cout << "Please enter your " << points << " control points. Format: x y" << endl;
	double partX;
	double partY;
	cout << "What is the derivative vector at the first point?" << endl;
	cin >> partX >> partY;
	vector1 = {partX, partY};
	cout << "What is the derivative vector at the last point?" << endl;
	cin >> partX >> partY;
	vector2 = {partX, partY};

	//loop over the number of control points
	for (int i = 0; i < stoi(points); i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY;
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});
	}
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.c1Algo(BernsteinCurves[k], vector1, vector2, res);
	}
	glutSwapBuffers();
	QuadInterpolationRe();
}

void promptUser(void)
{
	string CI;
	cout << "Hello! Please choose between these three options: [C]2 Continuous piecewise cubic interpolation, [D]e Boor Algorithm, C1-continuous [Q]uadratic B-spline curve interpolation" << endl;
	cin >> CI;
	if (CI == "C")
	{
		NaturalCubicSpline();
	}
	else if (CI == "D")
	{
		// Perform Bspline
		BSplineCalc();
	}
	else if (CI == "Q")
	{
		QuadInterpolation();
	}


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
	glutCreateWindow("Homework 3");
	// register callbacks
	glutDisplayFunc(renderScene);
	cout << "The dimensions of the window is 800 by 800, the bottom left is (0, 0)" << endl;
	glutMainLoop();
	// enter GLUT event processing cycle
	return 1;
}
