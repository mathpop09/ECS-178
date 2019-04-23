#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include "algo.h"

using namespace std;

void algo::deCasteljau (vector<dim> coordinates, double t, int res)
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


  vector<dim> castDraw;
  //Do Casteljau's
  //loop over all the t-values
  for (int h = 0; h <= resolution; h++)
  {
    //loop over the number of lines in the polygon
    vector<dim> looper = coordinates;
    vector<dim> temp;

      //one column level calculator
      double xPush = 0;
      double yPush = 0;
      for (int j = looper.size() - 1; j > 0 ; j--)
      {
        double xVal = looper[j-1].x - looper[j].x;
        xPush = looper[j].x + (xVal * tVals[h]);

        double yVal = looper[j-1].y - looper[j].y;
        yPush = looper[j].y + (yVal * tVals[h]);
        temp.push_back({xPush, yPush});


        if ((j == 1) && (temp.size() == 1))
        {
          if (abs(tVals[h] - drawT) < 0.005) {
            tPoint = {xPush, yPush};
            glColor3f(0,0,1);
            glBegin(GL_LINES);
            for(int i = 1; i < looper.size(); i++) {
              glVertex2f(looper[i-1].x, looper[i-1].y);
              glVertex2f(looper[i].x, looper[i].y);
            }
            glEnd();
          }
          castDraw.push_back({xPush, yPush});
          temp.clear();
          j--;
        }

        if (j == 1)
        {
          //Draw the lines that make up specific t-value
          if (abs(tVals[h] - drawT) < 0.005) {
            glColor3f(0,0,1);
            glBegin(GL_LINES);
            for(int i = 1; i < looper.size(); i++) {
              glVertex2f(looper[i-1].x, looper[i-1].y);
              glVertex2f(looper[i].x, looper[i].y);
            }
            glEnd();
          }
          //clear out the vectors
          looper.clear();
          reverse(temp.begin(),temp.end());
          looper = temp;
          temp.clear();
          j = looper.size();
        }
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
	for (int i = 1; i < castDraw.size(); i++) {
    glVertex2f(castDraw[i-1].x, castDraw[i-1].y);
    glVertex2f(castDraw[i].x, castDraw[i].y);
	}
  glEnd();

  //draw the single point for the t-value
  glColor3f(1,1,0);
  glPointSize(5.0f);
  glBegin(GL_POINTS);
    glVertex2f(tPoint.x, tPoint.y);
  glEnd();
  coordinates.clear();
  castDraw.clear();

}

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

//min-max box intersection
//checks if two min max boxes intersection
bool algo::boxIntersection (vector<dim> points1, vector<dim> points2)
{
  double minx1 = 1;
  double miny1 = 1;
  double maxx1 = -1;
  double maxy1 = -1;

  double minx2 = 1;
  double miny2 = 1;
  double maxx2 = -1;
  double maxy2 = -1;

  //loop over control points in curve 1
  for (int i = 0; i < points1.size(); i++)
  {
    if (points1[i].x < minx1)
    {
      minx1 = points1[i].x;
    }
    if (points1[i].x > maxx1)
    {
      maxx1 = points1[i].x;
    }

    if (points1[i].y < miny1)
    {
      miny1 = points1[i].y;
    }
    if (points1[i].y > maxy1)
    {
      maxy1 = points1[i].y;
    }
  }

  //loop over control points in curve 2
  for (int i = 0; i < points2.size(); i++)
  {
    if (points2[i].x < minx2)
    {
      minx2 = points2[i].x;
    }
    if (points2[i].x > maxx2)
    {
      maxx2 = points2[i].x;
    }

    if (points2[i].y < miny2)
    {
      miny2 = points2[i].y;
    }
    if (points2[i].y > maxy2)
    {
      maxy2 = points2[i].y;
    }
  }

  if (minx1 > maxx2 || minx2 > maxx1 || miny1 > maxy2 || miny2 > maxy1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

double algo::area (vector<dim> curve)
{
  double minx = 1;
  double miny = 1;
  double maxx = -1;
  double maxy = -1;

  //loop over control points in curve 1
  for (int i = 0; i < curve.size(); i++)
  {
    if (curve[i].x < minx)
    {
      minx = curve[i].x;
    }
    if (curve[i].x > maxx)
    {
      maxx = curve[i].x;
    }

    if (curve[i].y < miny)
    {
      miny = curve[i].y;
    }
    if (curve[i].y > maxy)
    {
      maxy = curve[i].y;
    }
  }
  return ((maxx - minx) * (maxy - miny));
}

//modified sub divison only for intersection detection
vector<vector<dim>> algo::modSubDiv(vector<dim> curve)
{
	vector<dim> subCurve1;
	vector<dim> subCurve2;
	vector<dim> smallCurve;


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
				smallCurve.push_back(curve[j]);
			}
			subCurve1.push_back(singleT(smallCurve, 0.5));
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
			subCurve2.push_back(singleT(smallCurve, 0.5));
			smallCurve.clear();
		}
	}
  return {subCurve1, subCurve2};
}

//recursive intersection check
void algo::IntersectionCheck (vector<dim> curve1, vector<dim> curve2, double tol)
{
  double tolerance  = tol * tol;
  //If the box intersects and the area is above the tolerance
  //run intersectioncheck on subdivided curves.
  if (boxIntersection(curve1, curve2) == true && (area(curve1) > tolerance) && (area(curve2) > tolerance))
  {
    IntersectionCheck(modSubDiv(curve1)[0], modSubDiv(curve2)[0], tol);
    IntersectionCheck(modSubDiv(curve1)[0], modSubDiv(curve2)[1], tol);
    IntersectionCheck(modSubDiv(curve1)[1], modSubDiv(curve2)[0], tol);
    IntersectionCheck(modSubDiv(curve1)[1], modSubDiv(curve2)[1], tol);
  }
  else if (boxIntersection(curve1, curve2) == false)
  {
  }
  else if (boxIntersection(curve1, curve2) == true && ((area(curve1) < tolerance) || (area(curve2) < tolerance)))
  {
    glColor3f(1,1,0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(curve1[0].x, curve1[0].y);
    glEnd();
  }
}
