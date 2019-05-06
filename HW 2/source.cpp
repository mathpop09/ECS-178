#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "algo.h"
#include <chrono>
using namespace std;

vector<vector<dim>> curves;
vector<dim> coordinates;

//Store the Castlejau Curves and its t Values
vector<vector<dim>> ElevatedCurves;

//Store the Bernstein Curves
vector<vector<dim>> BernsteinCurves;

//Stors the derivative vectors for the curve
vector<dim> derVectors;
int pointsNum = 0;

int res = 0;

algo ag;

void recycleDR()
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
		ag.Bernstein(BernsteinCurves[k], res);
		ag.degreeRaised(BernsteinCurves[k], res);
	}
	glutSwapBuffers();
	recycleDR();
}

void recycleDRa()
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
		ag.Bernstein(BernsteinCurves[k], res);
		ag.degreeLowerAvg(BernsteinCurves[k], res);
	}
	glutSwapBuffers();
	recycleDRa();
}

void degreeRaising()
{
	cout << "Hello! How many coordinates are on your control polygon?" << endl;
	cin >> pointsNum;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
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
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.Bernstein(BernsteinCurves[k], res);
		ag.degreeRaised(BernsteinCurves[k], res);
	}
	glutSwapBuffers();
	recycleDR();
}

void degreeLowering()
{
	cout << "Hello! How many coordinates are on your control polygon?" << endl;
	cin >> pointsNum;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
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
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.Bernstein(BernsteinCurves[k], res);
		ag.degreeLowerAvg(BernsteinCurves[k], res);
	}
	glutSwapBuffers();
	recycleDRa();
}

void recycleAitkens()
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

	double tPar;
	cout << "What new t-value would you like to see?" << endl;
	cin >> tPar;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.Aitkens(BernsteinCurves[k], tPar, res);
	}
	glutSwapBuffers();
	recycleAitkens();
}

void Aitkens()
{
	cout << "Hello! How many coordinates are on your control polygon?" << endl;
	cin >> pointsNum;
	cout << "What resolution would you like your curve to be? (Must be 100 or greater)" << endl;
	cin >> res;
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
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();

	double tPar;
	cout << "What is your t value? [0,1]" << endl;
	cin >> tPar;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.Aitkens(BernsteinCurves[k], tPar, res);
	}
	glutSwapBuffers();
	recycleAitkens();
}

void recycleCCInterp()
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

		double vecX = 0.0;
		double vecY = 0.0;
		cout << "What is the the derivative vector at this new points?" << endl;
		cin >> vecX >> vecY;
		derVectors.insert(derVectors.begin() + iNum, {vecX, vecY});
	}
	else
	{
		BernsteinCurves[0].erase(BernsteinCurves[0].begin() + iNum);
		derVectors.erase(derVectors.begin() + iNum);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.CCInterp(BernsteinCurves[k], derVectors, res);
	}
	glutSwapBuffers();
	recycleCCInterp();
}

void CCInterp()
{
	cout << "Hello! How many coordinates are on your control polygon?" << endl;
	cin >> pointsNum;
	cout << "What resolution would you like your curve to be?" << endl;
	cin >> res;
	cout << "Please enter your " << pointsNum << " control points and derivative vectors. Format: x y" << endl;
	//loop over the number of control points
	for (int i = 0; i < pointsNum; i++)
	{
			double coorX = 0;
			double coorY = 0;
			cout << "Control Point " << (i + 1) << ": " << endl;
			cin >> coorX >> coorY;
			cout << "Coordinate X: " << coorX << " Coordinate Y: " << coorY << endl;
			coordinates.push_back({coorX, coorY});

			double vecX = 0.0;
			double vecY = 0.0;
			cout << "Derivative Vector " << (i + 1) << ": " << endl;
			cin >> vecX >> vecY;
			derVectors.push_back({vecX, vecY});
	}
	BernsteinCurves.push_back(coordinates);
	coordinates.clear();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	for (int k = 0; k < BernsteinCurves.size(); k++)
	{
		ag.CCInterp(BernsteinCurves[k], derVectors, res);
	}
	glutSwapBuffers();
	recycleCCInterp();
}

void promptUser(void)
{
	string CI;
	//Two modes, regular curve drawing or intersection
	cout << "Hello! Please choose between these three options: [D]egree-raising algorithms, [A]itken's Algorithm, [P]iecewise cubic curve interpolation" << endl;
	cin >> CI;
	if (CI == "D")
	{
		string raiseReduc;
		cout << "Hello! Would you like to degree-r[a]ise or degree-r[e]duction?" << endl;
		cin >> raiseReduc;

		//perform degreeRaising prompt
		if (raiseReduc == "a")
		{
			degreeRaising();
		}
		else if (raiseReduc == "e")
		{
			degreeLowering();
		}
	}
	else if (CI == "A")
	{
		Aitkens();
	}
	else if (CI == "P")
	{
		CCInterp();
	}
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	promptUser();
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
	glutMainLoop();
	// enter GLUT event processing cycle
	return 1;
}
