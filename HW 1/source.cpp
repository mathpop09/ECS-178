#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "algo.h"
using namespace std;

vector<vector<dim>> curves;
vector<dim> coordinates;

//Store the Castlejau Curves and its t Values
vector<vector<dim>> CasteljauCurves;
vector<double> tValues;

//Store the Bernstein Curves
vector<vector<dim>> BernsteinCurves;

//Curve-Curve Intersection Curves. Always will be Bernstein, but stored separately
//[0] and [1] will be tested for intersection, [2] and [3], [4] and [5], etc etc
vector<vector<dim>> IntersectionCurves;
int pointsNum = 0;

algo ag;
//1. Get control point data from desired curve
//2. Delete curve data from CasteljauCurves (and the t value) and from BezierCurves
//3. Get the two sets of new control points and push it back to either CasteljauCurve or BezierCurves
//Note: castel == true, then casteljau subdivison. castel == false, then bernstein subdivision
void subDivision(int index, double t, bool castel)
{
	vector<dim> subCurve1;
	vector<dim> subCurve2;
	vector<dim> curve;
	vector<dim> smallCurve;

	double casT;
	if (castel == true)
	{
		//save curve index
		curve = CasteljauCurves[index];
		casT = tValues[index];
		//save curve t-value
		//erase that curve from existence
		CasteljauCurves.erase(CasteljauCurves.begin() + index);
		tValues.erase(tValues.begin() + index);
	}
	else
	{
		//save curve index
		curve = BernsteinCurves[index];
		//erase that curve from existence
		BernsteinCurves.erase(BernsteinCurves.begin() + index);
	}

	//calculate the first curve
	for(int i = 0; i < curve.size(); i++)
	{
		if (i == 0)
		{
			subCurve1.push_back(curve[0]);
		}
		else
		{
			for(int j = 0; j <= i; j++)
			{
				cout << curve[j].x << " " << curve[j].y << endl;
				smallCurve.push_back(curve[j]);
			}
			subCurve1.push_back(ag.singleT(smallCurve, t));
			smallCurve.clear();
		}
	}

	//calculate the second curve
	for(int i = curve.size() - 1; i >= 0; i--)
	{
		if (i == curve.size() - 1)
		{
			subCurve2.push_back(curve[curve.size()-1]);
		}
		else
		{
			for(int j = curve.size() - 1; j >= i; j--)
			{
				smallCurve.push_back(curve[j]);
			}
			subCurve2.push_back(ag.singleT(smallCurve, 1-t));
			smallCurve.clear();
		}
	}

	//add curves back to the curve collection
	if (castel == true)
	{
		CasteljauCurves.push_back(subCurve1);
		reverse(subCurve2.begin(), subCurve2.end());
		CasteljauCurves.push_back(subCurve2);
		tValues.push_back(casT);
		tValues.push_back(casT);
	}
	else
	{
		BernsteinCurves.push_back(subCurve1);
		BernsteinCurves.push_back(subCurve2);
	}
}


void promptUser(void)
{
	bool intersection;
	//Two modes, regular curve drawing or intersection
	cout << "Hello! Would you like to perform an intersection or would you just like to draw some curves? false for Curve Drawing/true for Intersection" << endl;
	cin >> intersection;
	if (intersection == false)
	{
		//Separate the Bernstein-Casteljau Drawing Window and the Curve-Curve Intersection Window
		//Bezier Curve Prompt
		for (int j = 0; j < 2; j++)
		{
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
			BernsteinCurves.push_back(coordinates);
			coordinates.clear();
		}
		ag.Bernstein(BernsteinCurves[0], 30);
		ag.Bernstein(BernsteinCurves[1], 30);
		ag.IntersectionCheck (BernsteinCurves[0], BernsteinCurves[1], 0.005);

	}
	//else if (intersection == false)
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
