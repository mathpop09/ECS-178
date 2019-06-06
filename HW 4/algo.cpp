#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "algo.h"

using namespace std;



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
      /*
      cerr << "dPoints: " << endl;
      cerr << weights[i][j] << endl;
      cerr << d[i][j].x << ", " << d[i][j].y << ", " << d[i][j].z << endl;
      */
      fourDim newVectorElem = {d[i][j].x * weights[i][j], d[i][j].y * weights[i][j], d[i][j].z * weights[i][j], weights[i][j]};

      newVector[i][j] = newVectorElem;
      //cerr << newVector[i][j].x << ", " << newVector[i][j].y << ", " << newVector[i][j].z << endl;
    }
  }
  return newVector;
}


//HERE IS THE MAIN COMPUTATION FUNCTION
double algo::basisFunc (int upperVal, int lowerVal, double mainVal, vector<double> knotVector, int order)
{
  double uBar = mainVal;



  vector<vector<double>> triScheme;

  //resize the triScheme
	triScheme.resize(lowerVal+1);


	for (int i = 0; i < lowerVal+1; i++)
	{
		triScheme[i].resize(lowerVal);
	}

  //initalize triangular Scheme
  cerr << lowerVal << " end" << endl;;
  for (int i = 1; i <= lowerVal; i++)
  {
      if ((knotVector[i] <= mainVal) && (mainVal < knotVector[i+1]))
      {
        triScheme[0][i] = 1;
      }
      else
      {
        cerr << "kek" << endl;
        triScheme[0][i] = 0;
      }
  }
  //print triScheme for test

  //tri scheme testing
  for (int i = 0; i < triScheme.size(); i++)
  {
    for (int j = 0; j < triScheme[i].size(); j++)
    {
      cerr << triScheme[j][i] << " ";
    }
    cerr << endl;
  }

  int IValue = 0;
  //loop over knot to find I
  for (int x = order - 1; x < knotVector.size() - order + 1; x++)
  {
    if ((knotVector[x] <= uBar) && (knotVector[x+1] > uBar))
    {
      IValue = x;
    }
  }

  //column then row
  int counter = 0;
  for (int j = 1; j < order; j++)
  {
    int calc = (IValue - (order - 1));
    int calc2 = IValue - j;
    int spit = calc;
    for (int i = calc; i <= calc2; i++)
    {
      //j = i i = k
      cerr << "----------Start:----------" << endl;
      cerr << uBar << endl;
      cerr << knotVector[i] << endl;
      cerr << knotVector[i+j-1] << endl;
      cerr << triScheme[i-1][j] << endl;
      cerr << triScheme[i-1][j+1] << endl;
      cerr << ((uBar - knotVector[j]) / (knotVector[i+j-1] - knotVector[i]) * triScheme[i-1][j]) + ((knotVector[i+j-1] - uBar) * triScheme[i-1][j+1]) << endl;
      cerr << "----------End:----------" << endl;
      triScheme[i][j] = ((uBar - knotVector[j]) / (knotVector[i+j-1] - knotVector[i]) * triScheme[i-1][j]) + ((knotVector[i+j-1] - knotVector[i]) * triScheme[i-1][j+1]);
      //tri scheme testing
      for (int i = 0; i < triScheme.size(); i++)
      {
        for (int j = 0; j < triScheme[i].size(); j++)
        {
          cerr << triScheme[j][i] << " ";
        }
        cerr << endl;
      }
      //end
    }
  }
  return triScheme[lowerVal-1][upperVal-1];
}


vector<vector<fourDim>> algo::eval4Space (vector<vector<fourDim>> dStar, vector<double> uKnots, vector<double> vKnots, orders orderPair, int res){
  cerr << "start" << endl;

  //number of dots to be connected
  int resolution = res;
  //Knot computation
  vector<double> knots;

  //all the uv points that will be calculated
  double uVals[res];
  double vVals[res];
  //all the nurbs points that will be drawn to create a nurbs curve
  threeDim nurbDraw[res][res];

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


  //Summation
  int rowI = dStar.size();
  int colI = dStar[0].size();

  //resize the nurbs vector
  vector<vector<fourDim>> Nurbs4D;
	Nurbs4D.resize(colI);


	for (int i = 0; i < rowI; i++)
	{
		Nurbs4D[i].resize(colI);
	}

  for (int u = 0; u < res; u++)
  {
    for (int v = 0; v < res; v++)
    {
      cerr << "u: " << u << endl;
      cerr << uVals[u] << v <<endl;
      cerr << "v: " << endl;
      cerr << vVals[v] << endl;
      fourDim sum1;
      for(int j = 0; j < colI ; j++)
      {
        fourDim sum2;
        for(int i = 0; i < rowI; i++)
        {
          //double basisFunc (int upperVal, int lowerVal, double mainVal, vector<double> knotVector, double order);
          double basis = basisFunc(orderPair.uKnotO_k, rowI, uVals[u], uKnots, orderPair.uKnotO_k);
          cerr << "Dstar: " << endl;
          cerr << dStar[i][j].x << ", " << dStar[i][j].y << ", " << dStar[i][j].z << endl;
          sum2.x += dStar[i][j].x * basis;
          sum2.z += dStar[i][j].y * basis;
          sum2.y += dStar[i][j].z * basis;
          sum2.w += dStar[i][j].w * basis;
        }
        double basis1 = basisFunc(orderPair.vKnotO_l, colI, uVals[v], vKnots, orderPair.vKnotO_l);
        sum1.x += sum2.x * basis1;
        sum1.y += sum2.y * basis1;
        sum1.z += sum2.z * basis1;
        sum1.w += sum1.w * basis1;
        cerr << "Nurbs Point: " << sum1.x << ", " << sum1.y << ", " << sum1.z << endl;
        Nurbs4D[u][v] = sum1;
      }
    }
  }

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
  /*
  vector<vector<threeDim>> projectedNURBSPoints = proj3Space (fourDNURBSPoints);
  //Draw the NURBS mesh
  int row = projectedNURBSPoints.size();
  int col = projectedNURBSPoints[0].size();


  glColor3f(1,1,0);
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
  */
}
