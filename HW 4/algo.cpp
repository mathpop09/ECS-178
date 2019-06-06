
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iterator>
#include "algo.h"

using namespace std;


//Done
//Draw NURBS

vector<vector<fourDim>> algo::move4Space (vector<vector<threeDim>> d, vector<vector<double>> weights)
{
  int row = d.size();
  int col = d[0].size();

  //resize the vector
  //resize the nurbs vector
  vector<vector<fourDim>> newVector;

  newVector.resize(row);
	for (int i = 0; i < row; i++)
	{
		newVector[i].resize(col);
	}


  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {

      fourDim newVectorElem = {d[i][j].x * weights[i][j], d[i][j].y * weights[i][j], d[i][j].z * weights[i][j], weights[i][j]};

      newVector[i][j] = newVectorElem;
    }
  }
  return newVector;
}


//HERE IS THE MAIN COMPUTATION FUNCTION
double algo::basisFunc (int upperVal, int lowerVal, double mainVal, vector<double> knotVector, int order)
{
  double uBar = mainVal;
  int higherVal = upperVal + lowerVal + 1;


  double triScheme[higherVal][higherVal];
  //initalize triangular Scheme

  for (int g = 0; g < higherVal; g++)
  {
    if ((knotVector[g] <= mainVal) && (mainVal < knotVector[g+1]))
    {
      triScheme[0][g] = 1;
    }
    else
    {
      triScheme[0][g] = 0;
    }
  }
  //column then row
  int counter = 0;
  for (int j = 1; j < higherVal; j++)
  {
    counter++;
    for (int i = 0; i < higherVal - j ; i++)
    {

      double tri = ((mainVal - knotVector[i])/(knotVector[i+j] - knotVector[i]) * triScheme[j-1][i]) + ((knotVector[i+j+1] - mainVal)/(knotVector[i+j+1] - knotVector[i+1]) * triScheme[j-1][i+1]);

      triScheme[j][i] = tri;
    }
  }
  return triScheme[upperVal][lowerVal];
}


vector<vector<fourDim>> algo::eval4Space (vector<vector<fourDim>> dStar, vector<double> uKnots, vector<double> vKnots, orders orderPair, int res){

  //number of dots to be connected
  int resolution = res;

  //all the uv points that will be calculated
  double uVals[res];
  double vVals[res];
  //all the nurbs points that will be drawn to create a nurbs curve
  threeDim nurbDraw[res][res];



  //Summation

  int rowI = dStar.size();
  int colI = dStar[0].size();


  int vStart = orderPair.vKnotO_l - 1;
  int vEnd = vKnots.size() - orderPair.vKnotO_l + 1;

  int uStart = orderPair.uKnotO_k - 1;
  int uEnd = uKnots.size() - orderPair.uKnotO_k + 1;

  double vPlace = vKnots[vStart];
  double uPlace = uKnots[uStart];

  //what to increment by every loop
  double incV = (vKnots[vEnd] - vKnots[vStart]) / (res - 1);
  double incU = (uKnots[uEnd] - uKnots[uStart]) / (res - 1);

  for (int i = 0; i < resolution; i++)
  {
      vVals[i] = vPlace;
      uVals[i] = uPlace;

      vPlace += incV;
      uPlace += incU;
  }

  vector<vector<fourDim>> Nurbs4D;
  //resize the nurbs vector
  Nurbs4D.resize(res);

	for (int i = 0; i < res; i++)
	{
		Nurbs4D[i].resize(res);
	}



  for (int u = 0; u < res; u++)
  {

    for (int v = 0; v < res; v++)
    {
      fourDim sum1 = {0, 0, 0, 0};
      for(int j = 0; j < colI ; j++)
      {

        for(int i = 0; i < rowI; i++)
        {

          //double basisFunc (int upperVal, int lowerVal, double mainVal, vector<double> knotVector, double order);

          double basis = basisFunc(orderPair.uKnotO_k, i, uVals[u], uKnots, orderPair.uKnotO_k);
          double basis1 = basisFunc(orderPair.vKnotO_l, j, vVals[v], vKnots, orderPair.vKnotO_l);
          sum1.x += dStar[i][j].x * basis * basis1;
          sum1.y += dStar[i][j].y * basis * basis1;
          sum1.z += dStar[i][j].z * basis * basis1;
          sum1.w += dStar[i][j].w * basis * basis1;

        }
      }
      Nurbs4D[u][v] = sum1;

    }
  }
  for (int u = 0; u < res; u++)
  {
    for (int v = 0; v < res; v++)
    {

    }
  }



  return Nurbs4D;
}

vector<vector<threeDim>> algo::proj3Space (vector<vector<fourDim>> sStar){
  int row = sStar.size();
  int col = sStar[0].size();

  vector<vector<threeDim>> beSpit;
  //resize the vector
  beSpit.resize(row);
	for (int i = 0; i < row; i++)
	{
		beSpit[i].resize(col);
	}

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      threeDim freeBee;
      freeBee = {sStar[i][j].x / sStar[i][j].w, sStar[i][j].y / sStar[i][j].w, sStar[i][j].z / sStar[i][j].w};
      beSpit[i][j] = freeBee;
    }
  }
  return beSpit;
}


void algo::NURBS (orders order, vector<vector<threeDim>> controlPoints, vector<vector<double>> weights,  vector<double> uKnots, vector<double> vKnots, int resolution)
{
  vector<vector<fourDim>> fourDPoints = move4Space(controlPoints, weights);

  vector<vector<fourDim>> fourDNURBSPoints = eval4Space(fourDPoints, uKnots, vKnots, order, resolution);

  vector<vector<threeDim>> projectedNURBSPoints = proj3Space (fourDNURBSPoints);
  //Draw the NURBS mesh
  int row = projectedNURBSPoints.size();
  int col = projectedNURBSPoints[0].size();


  glColor3f(1,0,1);
	glBegin(GL_LINES);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{




				// if last row
				if ((i == row - 1) && (j != col - 1))
				{
					glVertex3f(projectedNURBSPoints[i][j].x, projectedNURBSPoints[i][j].y, projectedNURBSPoints[i][j].z);
					glVertex3f(projectedNURBSPoints[i][j+1].x, projectedNURBSPoints[i][j+1].y, projectedNURBSPoints[i][j+1].z);

				}
				//if last col
				else if ((j == col - 1) && (i != row - 1))
				{
					glVertex3f(projectedNURBSPoints[i][j].x, projectedNURBSPoints[i][j].y, projectedNURBSPoints[i][j].z);
					glVertex3f(projectedNURBSPoints[i+1][j].x, projectedNURBSPoints[i+1][j].y, projectedNURBSPoints[i+1][j].z);

				}
				//if anything else
				else if ((i != row - 1) && (i != col - 1))
				{

					glVertex3f(projectedNURBSPoints[i][j].x, projectedNURBSPoints[i][j].y, projectedNURBSPoints[i][j].z);
					glVertex3f(projectedNURBSPoints[i+1][j].x, projectedNURBSPoints[i+1][j].y, projectedNURBSPoints[i+1][j].z);

					glVertex3f(projectedNURBSPoints[i][j].x, projectedNURBSPoints[i][j].y, projectedNURBSPoints[i][j].z);
					glVertex3f(projectedNURBSPoints[i][j+1].x, projectedNURBSPoints[i][j+1].y, projectedNURBSPoints[i][j+1].z);

				}
		}
	}
  glEnd();
}
