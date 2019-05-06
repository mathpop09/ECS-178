#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
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

//Bernstein Implementation, but Yellow!
void algo::BernsteinYellow (vector<dim> coordinates, int res)
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
  glColor3f(1.0,1.0,0);
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

//Bernstein Implementation, but Magneta!
void algo::BernsteinMagneta (vector<dim> coordinates, int res)
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
  //make polygon magneta
  glColor3f(1.0,0,1.0);
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

//get specific C(t)
dim algo::singleT (vector<dim> points, double tVal)
{
  Pascals(points.size());
  vector<int> coeff = Pascals(points.size())[points.size()-1];

  double x = 0;
  double y = 0;
  for (int i = 0; i < points.size(); i++)
  {
    x += (coeff[i] * pow(tVal, i) * pow((1 - tVal), points.size() - 1 - i)) * points[i].x;
    y += (coeff[i] * pow(tVal, i) * pow((1 - tVal), points.size() - 1 - i)) * points[i].y;
  }
  return {x, y};
}

/* START OF PART A
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
*/

//Draws out the degrees raised polygon
void algo::degreeRaised (vector<dim> points, int res)
{
  //number of dots to be connected
  int resolution = res;
  double tVals[resolution+1];
  double tValue = 0;
  vector<dim> drawDR;

  //store the first and last points of the original curve
  vector<dim> pointsCopy = points;
  dim first = pointsCopy[0];
  dim last = pointsCopy[pointsCopy.size()-1];

  //loop from 1 to n and create the points that are between the original bezier curve end control points
  vector<dim> toInsert;
  for (int i = 1; i < points.size(); i++)
  {
    int nSize = points.size();
    double xcoor = ((float(i) / nSize) * points[i-1].x) + ((1 - (float(i) / nSize)) * points[i].x);
    double ycoor = ((float(i) / nSize) * points[i-1].y) + ((1 - (float(i) / nSize)) * points[i].y);
    toInsert.push_back({xcoor, ycoor});
  }

  //Create the full control polygon for the degree raised curve
  drawDR.push_back(first);
  for (int i = 0; i < toInsert.size(); i++)
  {
    drawDR.push_back(toInsert[i]);
  }
  drawDR.push_back(last);

  //Draw the curve but in yellow
  BernsteinYellow(drawDR, res);
}

vector<dim> algo::degreeLowerL (vector<dim> points)
{
  int cpNum = points.size();
  int degNum = cpNum - 1;
  vector<dim> toSpit;
  //store original curve
  vector<dim> pointsCopy = points;
  dim storedB;
  for (int i = 0; i < cpNum-1; i++)
  {
    if (i != 0)
    {
      double xcoor = pointsCopy[i].x;
      double ycoor = pointsCopy[i].y;
      double doneX = ((degNum / float(degNum - i)) * xcoor) - ((i / float(degNum - i)) * storedB.x);
      double doneY = ((degNum / float(degNum - i)) * ycoor) - ((i / float(degNum - i)) * storedB.y);
      storedB.x = doneX;
      storedB.y = doneY;
      toSpit.push_back({doneX, doneY});
      cout << doneX << ", " << doneY << endl;
    }
    //special case for b index -1
    else
    {
      double xcoor = pointsCopy[i].x;
      double ycoor = pointsCopy[i].y;
      double doneX = xcoor;
      double doneY = ycoor;
      storedB.x = doneX;
      storedB.y = doneY;
      toSpit.push_back({doneX, doneY});
      cout << doneX << ", " << doneY << endl;
    }
  }
  //BernsteinMagneta(toSpit, 30);
  return toSpit;
}

vector<dim> algo::degreeLowerR (vector<dim> points)
{
  int cpNum = points.size();
  int degNum = cpNum - 1;
  vector<dim> toSpit;
  //store original curve
  vector<dim> pointsCopy = points;
  //filler
  dim storedB = {1, 1};
  for (int i = cpNum-1; i > 0; i--)
  {
    double xcoor = pointsCopy[i].x;
    double ycoor = pointsCopy[i].y;
    double doneX = ((degNum / float(i)) * xcoor) - (((degNum - i) / float(i)) * storedB.x);
    double doneY = ((degNum / float(i)) * ycoor) - (((degNum - i) / float(i)) * storedB.y);
    cout << doneX << ", " << doneY << endl;
    storedB.x = doneX;
    storedB.y = doneY;
    toSpit.push_back({doneX, doneY});
  }
  reverse(toSpit.begin(), toSpit.end());
  return toSpit;
}

void algo::degreeLowerAvg (vector<dim> points, int res)
{
  //get the coordinates from the two difference degree reductions
  vector<dim> points1 = degreeLowerL(points);
  vector<dim> points2 = degreeLowerR(points);

  vector<dim> newCurve;
  for(int i = 0; i < points1.size(); i++)
  {
    double x1 = points1[i].x;
    double y1 = points1[i].y;
    double x2 = points2[i].x;
    double y2 = points2[i].y;

    dim newCoor;
    newCoor.x = (x1 + x2) / 2;
    newCoor.y = (y1 + y2) / 2;
    newCurve.push_back({newCoor.x, newCoor.y});
  }

  BernsteinMagneta(newCurve, res);
}

/* START OF PART B
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
*/

double algo::twoPointDistance (dim point1, dim point2)
{
  dim copyP1 = point1;
  dim copyP2 = point2;

  double distance = sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));

  return distance;
}

void algo::Aitkens (vector<dim> coordinates, double t, int res)
{
  dim tPoint;
  //number of dots to be connected
  int resolution = res;
  double tVals[resolution+1];
  double tValue = 0;
  double drawT = (round((1-t) * 100))/100;


  for (int i = 0; i < resolution; i++)
  {
    tVals[i] = tValue;
    tValue += (1.0/resolution);
  }

  tVals[resolution] = tValue;
  //t's are now filled out from 0, 0.01, 0.02... to 1

  double tIndex[coordinates.size()];
  tValue = 0;

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
    tIndex[i] = tValue;
    if (i != coordinates.size() - 1)
    {
      toAdd = (twoPointDistance(coordinates[i], coordinates[i + 1]) / totalLength);
    }
    tValue += toAdd;
  }




  vector<dim> castDraw;
  //Do Casteljau's
  //loop over all the t-values
  for (int h = 0; h <= resolution; h++)
  {
    //loop over the number of lines in the polygon
    vector<dim> looper = coordinates;
    vector<dim> temp = looper;
    vector<dim> temp2 = looper;
    for (int i = 0; i < looper.size() - 1; i++)
    {
      //one column level calculator
      double xVal = 0.0;
      double yVal = 0.0;
      temp = temp2;
      temp2.clear();
      for (int j = 0; j < temp.size() - 1 ; j++)
      {
        int plusR = (looper.size() + 1) - temp.size();
        if (i == 0)
        {
          double xVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (looper[j].x)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (looper[j + 1].x));

          double yVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (looper[j].y)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (looper[j + 1].y));
          temp2.push_back({xVal, yVal});
        }
        else if (i == looper.size() - 2)
        {
          double xVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j].x)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j + 1].x));

          double yVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j].y)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j + 1].y));
          castDraw.push_back({xVal, yVal});
          if (abs(tVals[h] - t) < 0.005)
          {
            //draw the single point for the t-value
            glColor3f(1,1,0);
            glPointSize(5.0f);
            glBegin(GL_POINTS);
              glVertex2f(xVal, yVal);
            glEnd();
          }
        }
        else
        {
          double xVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j].x)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j + 1].x));

          double yVal = ((tIndex[j + plusR] - tVals[h]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j].y)) + ((tVals[h] - tIndex[j]) / (tIndex[j + plusR] - tIndex[j]) * (temp[j + 1].y));
          temp2.push_back({xVal, yVal});
        }
      }
      if (abs(tVals[h] - t) < 0.005)
      {
        glColor3f(0,0,1);
        glBegin(GL_LINES);
        for(int i = 1; i < temp2.size(); i++) {
          glVertex2f(temp2[i-1].x, temp2[i-1].y);
          glVertex2f(temp2[i].x, temp2[i].y);
        }
        glEnd();
      }
      temp.clear();
    }
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
	for (int i = 1; i < castDraw.size(); i++)
  {
    glVertex2f(castDraw[i-1].x, castDraw[i-1].y);
    glVertex2f(castDraw[i].x, castDraw[i].y);
	}
  glEnd();


  coordinates.clear();
  castDraw.clear();
}

/* START OF PART C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
*/

void algo::CCInterp(vector<dim> points, vector<dim> derivativeVectors, int res)
{

  //number of dots to be connected
  int resolution = res;
  double tVals[resolution+1];
  double tValue = 0;

  for (int i = 0; i < resolution; i++)
  {
    tVals[i] = tValue;
    tValue += (1.0/resolution);
  }

  tVals[resolution] = tValue;
  //t's are now filled out from 0, 0.01, 0.02... to 1

  //length of all chords
  double totalLength = 0;
  for (int i = 1; i < points.size(); i++)
  {
    totalLength += twoPointDistance(points[i-1], points[i]);
  }

  double tIndex[points.size()];
  //Implemented chord length parametrization
  double toAdd = 0;
  tValue = 0;
  for (int i = 0; i < points.size(); i++)
  {
    cout << tValue << endl;
    tIndex[i] = tValue;
    if (i != points.size() - 1)
    {
      toAdd = (twoPointDistance(points[i], points[i + 1]) / totalLength);
    }
    tValue += toAdd;
  }



  vector<dim> toDraw;
  for (int t = 0; t < resolution; t++)
  {
    double h0 = 1 - (3 * tVals[t] * tVals[t]) + (2 * tVals[t] * tVals[t] * tVals[t]);
    double h1 = (3 * tVals[t] * tVals[t]) - (2 * tVals[t] * tVals[t]);
    double h0bar = tVals[t] - (2 * tVals[t] * tVals[t]) + (tVals[t] * tVals[t] * tVals[t]);
    double h1bar = ((-1) * tVals[t] * tVals[t]) + (tVals[t] * tVals[t] * tVals[t]);

    int theCorrectI = 0;
    for (int i = 1; i < points.size(); i++)
    {
      if ((tVals[t] < tIndex[i]) && (theCorrectI == 0))
      {
        theCorrectI = i;
      }
    }
    double pushX = (points[theCorrectI-1].x * h0) + (points[theCorrectI].x * h1) + (derivativeVectors[theCorrectI-1].x * h0bar) + (derivativeVectors[theCorrectI].x * h1bar);
    double pushY = (points[theCorrectI-1].y * h0) + (points[theCorrectI].y * h1) + (derivativeVectors[theCorrectI-1].y * h0bar) + (derivativeVectors[theCorrectI].y * h1bar);
    cout << pushX << ", " << pushY << endl;
    toDraw.push_back({pushX, pushY});
  }

  //draw out the polygon created by the points.
  //make polygon red
  glColor3f(1.0,0,0);
  glBegin(GL_LINES);
  for (int i = 1; i < points.size(); i++)
  {
    glVertex2f(points[i-1].x, points[i-1].y);
    glVertex2f(points[i].x, points[i].y);
  }
  glEnd();


	// with the draw vector, connect all of the points in the vector together.
  glColor3f(0,1.0,0);
  glBegin(GL_LINES);
	for (int i = 1; i < toDraw.size(); i++)
  {
    glVertex2f(toDraw[i-1].x, toDraw[i-1].y);
    glVertex2f(toDraw[i].x, toDraw[i].y);
	}
  glEnd();

  toDraw.clear();
}
