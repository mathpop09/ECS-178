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


void NURBSCalcRe()
{

	cout << "Curve Composition: " << endl;
	cout << "Control Points: " << endl;
	for (int i = 0; i < cpDimensions[0].row; i++)
	{
		for (int j = 0; j < cpDimensions[0].col; j++)
		{
			cout << " Index: " << i << ", " << j << " " << controlPoints[0][i][j].x << ", " << controlPoints[0][i][j].y << ", " << controlPoints[0][i][j].z << endl;
			cout << " Weight: " << weights[0][i][j] << endl;
		}
	}

	cout << "Orders k and l: " << endl;
	cout << "k: " << nurbOrderVec[0].uKnotO_k << " l:" << nurbOrderVec[0].vKnotO_l << endl;
	cout << "u-knots: " << endl;
	cout << "[";
  for (int i = 0; i < uKnots[0].size(); i++)
  {
    if (i != uKnots[0].size() - 1)
    {
      cout << uKnots[0][i] << ", ";
    }
    else
    {
      cout << uKnots[0][i] << "]" << endl;
    }
  }
	cout << "v-knots: " << endl;
	cout << "[";
  for (int i = 0; i < vKnots[0].size(); i++)
  {
    if (i != vKnots[0].size() - 1)
    {
      cout << vKnots[0][i] << ", ";
    }
    else
    {
      cout << vKnots[0][i] << "]" << endl;
    }
  }

	cout << "What modifications would you like to make?: " << endl;
	cout << "[1] Changing a control point: " << endl;
	cout << "[2] Changing a weight of a control point" << endl;
	cout << "[3] Control point row/column deletion: " << endl;
	cout << "[4] Control point row/column insertion: " << endl;
	cout << "[5] Changing the order: " << endl;
	cout << "[6] Changing the knot vector: " << endl;
	cout << "[7] Changing the resolution: " << endl;
	int iNum;
	cin >> iNum;


	//CP MOD
	if (iNum == 1)
	{
		cout << "Please enter the index of the control point you would like to change: (x y)" << endl;
		int i = 0;
		int j = 0;
		cin >> i >> j;
		cout << "What would you like to change the control point to?: (x y z)" << endl;
		double x = 0;
		double y = 0;
		double z = 0;
		cin >> x >> y >> z;
		controlPoints[0][i][j] = {x, y, z};
	}
	//CP WEIGHT MOD
	else if (iNum == 2)
	{
		cout << "Please enter the index of the control point (weight) you would like to change: (x y)" << endl;
		int i = 0;
		int j = 0;
		cin >> i >> j;
		cout << "What would you like to change the weight to?: (x y z)" << endl;
		double x = 0;
		cin >> x;
		weights[0][i][j] == x;
	}
	//CP ROW DELETION
	else if (iNum == 3)
	{
		cout << "Would you like to delete a row or a column? [r/c] " << endl;
		string RC;
		cin >> RC;
		if (RC == "r")
		{
			cout << "Which row would you like to delete? " << endl;
			int row;
			cin >> row;
			if (controlPoints[0].size() > row)
			{
			  controlPoints[0].erase(controlPoints[0].begin() + row );
			}
			cpDimensions[0].row = cpDimensions[0].row - 1;
		}
		else
		{
			cout << "Which column would you like to delete? " << endl;
			int col;
			cin >> col;
			for (int i = 0; i < controlPoints.size(); ++i)
			{
			  if (controlPoints[0][i].size() > col)
			  {
			    controlPoints[0][i].erase(controlPoints[0][i].begin() + col);
			  }
			}
			cpDimensions[0].col = cpDimensions[0].col - 1
		}
	}
	//CP ROW INSERTION
	else if (iNum == 4)
	{
		cout << "Would you like to insert a row or a column? [r/c] " << endl;
		string RC;
		cin >> RC;
		if (RC == "r")
		{
			cout << "Where would you like to insert your row? " << endl;
			int row;
			cin >> row;

			vector<threeDim> rowCP;
			cout << "Please enter a row of control points of size " <<  cpDimensions[0].col << ": " << endl;
			for (int i = 0; i < cpDimensions[0].col; i++)
			{
				threeDim cp;
				double x;
				double y;
				double z;
				cin >> x >> y >> z;
				cp = {x, y, z};
				rowCP.push_back(cp);
			}

			if (controlPoints[0].size() > row)
			{
			  controlPoints[0].insert(controlPoints[0].begin() + row, rowCP);
			}
			cpDimensions[0].row = cpDimensions[0].row + 1;
		}
		else
		{
			cout << "Where would you like to insert your column? " << endl;
			int col;
			cin >> col;

			vector<threeDim> colCP;
			cout << "Please enter a column of control points of size " <<  cpDimensions[0].row << ": " << endl;
			for (int i = 0; i < cpDimensions[0].col; i++)
			{
				threeDim cp;
				double x;
				double y;
				double z;
				cin >> x >> y >> z;
				cp = {x, y, z};
				colCP.push_back(cp);
			}

			for (int i = 0; i < controlPoints[0].size(); ++i)
			{
			  if (controlPoints[0][i].size() > col)
			  {
			    controlPoints[0][i].insert(controlPoints[0][i].begin() + col, colCP[i]);
			  }
			}
			cpDimensions[0].col = cpDimensions[0].col + 1;
		}
	}
	//CP ORDER CHANGE
	else if (iNum == 5)
	{
		cout << "Please set your new order pairs" << endl;
		int order1;
		int order2;
		cin >> order1 >> order2;
		orders orderCombo = {order1, order2};
		nurbOrderVec[0] = (orderCombo);
	}
	//CP KNOT MODIFICATION
	else if (iNum == 6)
	{
		vector<double> uSKnots;
		vector<double> vSKnots;
		cout << "Please enter your u-knots set of size: " <<  cpDimensions[0].row + nurbOrderVec[0].uKnotO_k << ". Formating: 1 2 3 4 5..." << endl;
		for (int i = 0; i < cpDimensions[0].row + nurbOrderVec[0].uKnotO_k; i++)
		{
			double knotVal;
			cin >> knotVal;
			uSKnots.push_back(knotVal);
		}
		uKnots[0] = uSKnots;

		cout << "Please enter your v-knots set of size: " <<  cpDimensions[0].col + nurbOrderVec[0].vKnotO_l << ". Formating: 1 2 3 4 5..." << endl;
		for (int i = 0; i < cpDimensions[0].col + nurbOrderVec[0].vKnotO_l; i++)
		{
			double knotVal;
			cin >> knotVal;
			vSKnots.push_back(knotVal);
		}
		vKnots[0] = vSKnots;
	}
	else if (iNum == 7)
	{
		int resolution;
		cout << "Please enter your new desired resolution: " << endl;
		cin >> resolution;
		res = resolution;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	glColor3f(1,1,0);
	glBegin(GL_LINES);

	for (int i = 0; i < cpDimensions[0].row; i++)
	{
		for (int j = 0; j < cpDimensions[0].col; j++)
		{
				// if last row
				if ((i == cpDimensions[0].row - 1) && (j != cpDimensions[0].col - 1))
				{
					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i][j+1].x, controlPoints[0][i][j+1].y, controlPoints[0][i][j+1].z);

				}
				//if last col
				else if ((j == cpDimensions[0].col - 1) && (i != cpDimensions[0].row - 1))
				{
					glVertex3f(controlPoints[0][i][j].x, controlPoints[0][i][j].y, controlPoints[0][i][j].z);
					glVertex3f(controlPoints[0][i+1][j].x, controlPoints[0][i+1][j].y, controlPoints[0][i+1][j].z);

				}
				//if anything else
				else if ((i != cpDimensions[0].row- 1) && (i != cpDimensions[0].col - 1))
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
	NURBSCalcRe();
}


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

	cout << "Please enter your v-knots set of size: " <<  pair.col + order2 << ". Formating: 1 2 3 4 5..." << endl;
	for (int i = 0; i < pair.col + order2; i++)
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
	NURBSCalcRe();
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
