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


//Pascal's Triangle implementaion for Bernstein
//Input the level of the triangle and then outputs a 2d vector that stores the
//different triangle values up to the desired level
vector<vector<int>> algo::Pascals (int level)
{
  vector<vector<int>> triangle;
  vector<int> row;
  for (int i = 0; i < level; i++)
  {
    //create one level
    for (int j = 0; j <= i; j++)
    {
      if ((j == 0) || (j == i))
      {
        row.push_back(1);
      }
      else
      {
        int pushed = triangle[i-1][j] + triangle[i-1][j-1];
        row.push_back(pushed);
      }
    }
    //push created level to triangle and clear the level vector
    triangle.push_back(row);
    row.clear();
  }
  return triangle;
}

//Euclidean Distance
double algo::EucDistance(dim point1, dim point2)
{
  double distx = (point1.x - point2.x);
  double disty = (point1.y - point2.y);
  double eucDist = sqrt(pow(distx,2) + pow(disty,2));
  return eucDist;
}

vector<double> algo::EucKnot(vector<dim> points, int order)
{
  vector<double> knots;
  vector<double> EucDist;
  double totalLength = 0;
  for (int i = 1; i < points.size(); i++)
  {
    int counter = 0;
    if (order > counter)
    {
      counter++;
      totalLength += EucDistance(points[i-1], points[i]);
    }
    else
    {
      counter = 0;
      //set the index to the length of the bezier component
      EucDist.push_back(totalLength);
      totalLength = 0;
    }
  }

  for (int i = 1; i < points.size(); i++)
  {
    knots.push_back(totalLength);
    totalLength += EucDistance(points[i-1], points[i]);
  }
  knots.push_back(1);
}

//Bernstein Implementation
void algo::Bernstein (vector<dim> coordinates, int res)
{
  //number of dots to be connected
  int resolution = res;
  double tVals[resolution+1];
  double tValue = 0;
  vector<dim> drawBern;

  //Coefficient of bernstein equation
  vector<int> coeff = Pascals(coordinates.size())[coordinates.size()-1];

  for (int i = 0; i < resolution; i++)
  {
    tVals[i] = tValue;
    tValue += (1.0/resolution);
  }
  //added 1
  tVals[resolution] = tValue;
  //t's are now filled out from 0, 0.01, 0.02... to 1

  //loop over all the t-values
  for (int h = 0; h <= resolution; h++)
  {
    dim coord = {0,0};
    double x = 0;
    double y = 0;
    for (int i = 0; i < coordinates.size(); i++)
    {
      x += (coeff[i] * pow(tVals[h], i) * pow((1 - tVals[h]), coordinates.size() - 1 - i)) * coordinates[i].x;
      y += (coeff[i] * pow(tVals[h], i) * pow((1 - tVals[h]), coordinates.size() - 1 - i)) * coordinates[i].y;
    }
    drawBern.push_back({x,y});
  }

  //draw out the polygon created by the points.
  //make polygon red
  glColor3f(1.0,0,0);
  glBegin(GL_LINES);
    for (int i = 1; i < coordinates.size(); i++)
    {
      glVertex2f(coordinates[i-1].x, coordinates[i-1].y);
      glVertex2f(coordinates[i].x, coordinates[i].y);
    }
  glEnd();

  // with the draw vector, connect all of the points in the vector together.
  glColor3f(0,1,0);
  glBegin(GL_LINES);
	for (int i = 1; i < drawBern.size(); i++) {
    glVertex2f(drawBern[i-1].x, drawBern[i-1].y);
    glVertex2f(drawBern[i].x, drawBern[i].y);
	}
  glEnd();
}

// Code from: https://hnagib.com/portfolio/tridiagonal-solver/
vector<double> algo::tridiagonal_solver(vector<double> a, vector<double> b, vector<double> c, vector<double> f)
{

    int n = f.size();
    vector<double> x(n);
    vector<double> newa = a;
    vector<double> newb = b;
    vector<double> newc = c;
    vector<double> newf = f;
    for(int i=1; i<n; i++){

        double m = newa[i-1]/newb[i-1];
        newb[i] -= m*newc[i-1];
        newf[i] -= m*newf[i-1];
    }
    // solve for last x value
    x[n-1] = newf[n-1]/newb[n-1];
    // solve for remaining x values by back substitution
    for(int i=n-2; i >= 0; i--)
    {
        x[i] = (newf[i]- newc[i]*x[i+1])/newb[i];
    }

    return x;
}

double algo::twoPointDistance (dim point1, dim point2)
{
  dim copyP1 = point1;
  dim copyP2 = point2;

  double distance = sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));

  return distance;
}

void algo::c2Algo(vector<dim> coordinates, int parametrization, int res)
{
  //number of dots to be connected
  int resolution = res;
  vector<double> tVals;
  double tValue = 0;
  //Uniform
  if (parametrization == 1)
  {
    for (int i = 0; i < (coordinates.size() + 4); i++)
    {
      tVals.push_back(tValue);
      tValue += 1;
    }
    //added 1
    tVals[coordinates.size() + 3] = tValue;
    //knots are filled out with their respective values
  }
  //Chord Length
  else if (parametrization == 2)
  {
    //length of all chords
    double totalLength = 0;
    for (int i = 1; i < coordinates.size(); i++)
    {
      totalLength += twoPointDistance(coordinates[i-1], coordinates[i]);
    }

    //Implemented chord length parametrization
    double toAdd = 0;
    for (int i = 0; i < coordinates.size(); i++)
    {
      tVals[i] = tValue;
      if (i != coordinates.size() - 1)
      {
        toAdd = (twoPointDistance(coordinates[i], coordinates[i + 1]) / totalLength);
      }
      tValue += toAdd;
    }
  }
  //Centripetal
  else if (parametrization == 3)
  {
    //length of all chords
    double totalLength = 0;
    for (int i = 1; i < coordinates.size(); i++)
    {
      totalLength += sqrt(twoPointDistance(coordinates[i-1], coordinates[i]));
    }

    //Implemented chord length parametrization
    double toAdd = 0;
    for (int i = 0; i < coordinates.size(); i++)
    {
      tVals[i] = tValue;
      if (i != coordinates.size() - 1)
      {
        toAdd = (sqrt(twoPointDistance(coordinates[i], coordinates[i + 1])) / totalLength);
      }
      tValue += toAdd;
    }
  }

  vector<double> alphaVector;
  vector<double> betaVector;
  vector<double> gammaVector;
  //Create alpha, beta, and gamma
  //Start at +2 (which is delta 0) and end at +2 since there are 4 extra points
  //set beginning points to 1
  double alpha;
  double beta;
  double gamma;
  for (int i = 0; i < coordinates.size(); i++)
  {
    alpha = pow(tVals[i], 2) / (tVals[i-2] + tVals[i-1] + tVals[i]);
    beta = ((tVals[i] * (tVals[i-2] + tVals[i-1])) / (tVals[i-2] + tVals[i-1] + tVals[i])) + ((tVals[i-1] * (tVals[i] + tVals[i+1])) / (tVals[i-1] + tVals[i] + tVals[i+1]));
    gamma = pow(tVals[i-1], 2) / (tVals[i-1] + tVals[i] + tVals[i+1]);
    if (i == 0)
    {
      betaVector.push_back(2);
      gammaVector.push_back(1);
    }
    //push it back
    alphaVector.push_back(1);
    betaVector.push_back(4);
    gammaVector.push_back(1);
  }
  //just set endpoints to one
  alphaVector.push_back(1);
  betaVector.push_back(2);
  vector<double> vectorX;
  vector<double> vectorY;
  //just set user coordinates to the coordinates 0

  vectorX.push_back((6 * ((coordinates[0].x)/2)));
  vectorY.push_back((6 * ((coordinates[0].y)/2)));

  for (int i = 0; i < coordinates.size(); i++)
  {
    vectorX.push_back((6 * ((coordinates[i].x))));
    vectorY.push_back((6 * ((coordinates[i].y))));
  }
  //just set user coordinates to the last coordinates

  vectorX.push_back((6 * (coordinates[coordinates.size()-1].x)/2));
  vectorY.push_back((6 * (coordinates[coordinates.size()-1].y)/2));


  vector<double> dPointX = tridiagonal_solver(alphaVector, betaVector, gammaVector, vectorX);
  vector<double> dPointY = tridiagonal_solver(alphaVector, betaVector, gammaVector, vectorY);

  vector<dim> deBoorPoints;
  for(int i = 0; i < dPointX.size(); i++)
  {
    deBoorPoints.push_back({dPointX[i], dPointY[i]});
  }


  //Draw the deBoor polygon
  glColor3f(0,0,1);
  glBegin(GL_LINES);
  for(int i = 1; i < deBoorPoints.size(); i++)
  {
    glVertex2f(deBoorPoints[i-1].x, deBoorPoints[i-1].y);
    glVertex2f(deBoorPoints[i].x, deBoorPoints[i].y);
  }

  //Draw the Bezier lines
  glColor3f(1,0,1);
  glPointSize(5.0f);

  vector<dim>  bezierPolygon;

  bezierPolygon.push_back(coordinates[0]);
  for(int i = 1; i < deBoorPoints.size(); i++)
  {
    dim Third1 = {(deBoorPoints[i-1].x + ((deBoorPoints[i].x - deBoorPoints[i-1].x)/3)), (deBoorPoints[i-1].y + ((deBoorPoints[i].y - deBoorPoints[i-1].y)/3))};
    dim Third2 = {(deBoorPoints[i-1].x + (((deBoorPoints[i].x - deBoorPoints[i-1].x)*2)/3)), (deBoorPoints[i-1].y + ((2*(deBoorPoints[i].y - deBoorPoints[i-1].y))/3))};

    glBegin(GL_POINTS);
    glVertex2f(Third1.x, Third1.y);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(Third2.x, Third2.y);
    glEnd();
    if ((i != 1) && (i != deBoorPoints.size() - 1))
    {
      bezierPolygon.push_back(Third1);
      bezierPolygon.push_back(Third2);
      bezierPolygon.push_back(coordinates[i-1]);
    }
  }
  bezierPolygon.push_back(coordinates[coordinates.size()-1]);



  //Draw the control points
  glColor3f(1,1,0);
  glPointSize(5.0f);
  glBegin(GL_POINTS);
  for(int i = 0; i < coordinates.size(); i++)
  {
    glVertex2f(coordinates[i].x, coordinates[i].y);
  }
  glEnd();

  //Draw the Bezier Polygon
  glColor3f(1,0,1);
  glBegin(GL_LINES);
  for(int i = 1; i < bezierPolygon.size(); i++)
  {
    glVertex2f(bezierPolygon[i-1].x, bezierPolygon[i-1].y);
    glVertex2f(bezierPolygon[i].x, bezierPolygon[i].y);
  }
  glEnd();



  //draw out actual
  vector<dim> oneCurve;
  int counter = 0;
  for(int i = 0; i < bezierPolygon.size(); i++)
  {
    if (counter == 4)
    {
      Bernstein(oneCurve, res);
      counter = 1;
      oneCurve.clear();
      i--;
      oneCurve.push_back(bezierPolygon[i]);
    }
    else
    {
      counter++;
      oneCurve.push_back(bezierPolygon[i]);
    }
  }
}

/*PART BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB*/

void algo::deBoors(vector<dim> coordinates, int order, int res)
{
  //number of dots to be connected
  int resolution = res;
  //Knot computation
  vector<double> knots;


  double EucDistTotal = 0.0;
  double tempEucDist = 0.0;
  vector<double> knotDistance;
  int counter = order - 2;
  for (int i = 0; i < coordinates.size()-1; i++)
  {
    if (counter == 0)
    {
      tempEucDist += EucDistance(coordinates[i-1], coordinates[i]);
      knotDistance.push_back(tempEucDist);
      EucDistTotal += tempEucDist;
      tempEucDist = 0;
      counter = order - 2;
      i -= order - 2;
    }
    else
    {
      tempEucDist += EucDistance(coordinates[i-1], coordinates[i]);
      counter--;
    }
  }


  //add middle knots
  double knotVal = 0.0;
  for (int i = 0; i < coordinates.size() + order - 1; i++)
  {
    knots.push_back(knotVal);
    knotVal += (1.0/(coordinates.size() + order - 1));
  }
  knots.push_back(knotVal);

  cout << "Knot Bar: " << endl;
  cout << "[";
  for (int i = 0; i < knots.size(); i++)
  {
    if (i != knots.size() - 1)
    {
      cout << knots[i] << ", ";
    }
    else
    {
      cout << knots[i] << "]" << endl;
    }
  }

  double tVals[resolution+1];
  double tValue = knots[order-1];
  double bounds = knots[coordinates.size()] - knots[order-1];
  for (int i = 0; i < resolution; i++)
  {
    tVals[i] = tValue;
    tValue += (bounds/resolution);
  }
  tVals[resolution] = tValue;

  //Draw the control points
  glColor3f(1,1,0);
  glBegin(GL_LINES);
  for(int i = 1; i < coordinates.size(); i++)
  {
    glVertex2f(coordinates[i-1].x, coordinates[i-1].y);
    glVertex2f(coordinates[i].x, coordinates[i].y);
  }
  glEnd();


  //Draw the actual B Spline Curve

  vector<dim> castDraw;
  //loop over all the t-values
  for (int h = 0; h <= resolution; h++)
  {
    double uBar = tVals[h];
    int IValue = 0;
    //loop over knot to find I
    for (int x = order - 1; x < knots.size() - order + 1; x++)
    {
      if ((knots[x] <= uBar) && (knots[x+1] > uBar))
      {
        IValue = x;
      }
    }

    dim triScheme[coordinates.size() - 1][coordinates.size()];
    //initalize triangular Scheme
    triScheme[0][0] = {0,0};
    for (int g = 0; g < coordinates.size(); g++)
    {
        triScheme[0][g] = coordinates[g];
    }
    for (int j = 1; j <= order - 1; j++)
    {
      int calc = (IValue - (order - 1));
      int calc2 = IValue - j;
      int spit = calc;
      for (int i = calc; i <= calc2; i++)
      {
        double triX = (((knots[i+order] - uBar) / (knots[i+order] - knots[i + j])) * triScheme[j-1][i].x) + ((uBar - knots[i + j]) / (knots[i+order] - knots[i+j]) * triScheme[j-1][i+1].x);
        double triY = (((knots[i+order] - uBar) / (knots[i+order] - knots[i + j])) * triScheme[j-1][i].y) + ((uBar - knots[i + j]) / (knots[i+order] - knots[i+j]) * triScheme[j-1][i+1].y);
        triScheme[j][i] = {triX, triY};
      }
    }
    castDraw.push_back(triScheme[order-1][IValue-(order-1)]);
  }

  // with the draw vector, connect all of the points in the vector together.
  glColor3f(0,1,0);
  glBegin(GL_LINES);
	for (int i = 1; i < castDraw.size(); i++) {
    glVertex2f(castDraw[i-1].x, castDraw[i-1].y);
    glVertex2f(castDraw[i].x, castDraw[i].y);
	}
  glEnd();
}

//checks if number is odd
bool algo::isOdd(int num)
{
  if ((num % 2) == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void algo::c1Algo (vector<dim> coordinates, dim vector1, dim vector2, int res)
{
  //Uniform parametrization so all the deltas are 1
  //calculate the first vector control polygon
  dim b1;
  double X = coordinates[0].x + (0.5 * vector1.x);
  double Y = coordinates[0].y + (0.5 * vector1.y);
  b1 = {X, Y};

  vector<dim> controlP1;
  dim lastCreate = b1;
  controlP1.push_back(coordinates[0]);
  controlP1.push_back(b1);
  for (int i = 1; i < coordinates.size(); i++)
  {

    controlP1.push_back(coordinates[i]);
    if (i != coordinates.size() - 1)
    {
      double xAdd = coordinates[i].x - lastCreate.x;
      double yAdd = coordinates[i].y - lastCreate.y;
      lastCreate = {coordinates[i].x + xAdd, coordinates[i].y + yAdd};
      controlP1.push_back(lastCreate);
    }
  }

  //calculate the second vector control polygon
  X = coordinates[coordinates.size()-1].x + (0.5 * vector2.x);
  Y = coordinates[coordinates.size()-1].y + (0.5 * vector2.y);
  b1 = {X, Y};

  vector<dim> controlP2;
  lastCreate = b1;
  controlP2.push_back(coordinates[coordinates.size()-1]);
  controlP2.push_back(b1);
  for (int i = coordinates.size() - 2; i >= 0; i--)
  {

    controlP2.push_back(coordinates[i]);
    if (i != 0)
    {
      double xAdd = coordinates[i].x - lastCreate.x;
      double yAdd = coordinates[i].y - lastCreate.y;
      lastCreate = {coordinates[i].x + xAdd, coordinates[i].y + yAdd};
      controlP2.push_back(lastCreate);
    }
  }


  //flip CP2 in preparation for averaging
  reverse(controlP2.begin(), controlP2.end());

  vector<dim> deBoorPoints;
  //average the control_points
  for (int i = 0; i < controlP1.size(); i++)
  {
    double avgX = (controlP1[i].x + controlP2[i].x) / 2.0;
    double avgY = (controlP1[i].y + controlP2[i].y) / 2.0;
    deBoorPoints.push_back({avgX, avgY});
  }
  deBoors(deBoorPoints,3,res);
  // with the draw vector, connect all of the points in the vector together.
  glColor3f(1,0,0);
  glPointSize(7.0f);
  glBegin(GL_POINTS);
	for (int i = 0; i < coordinates.size(); i++) {
    glVertex2f(coordinates[i].x, coordinates[i].y);
	}
  glEnd();
}
