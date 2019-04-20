#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include "algo.h"

using namespace std;

void algo::deCastlejau (vector<dim> coordinates, double t, int res)
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
  //Do Castlejau's
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
    cout << endl;
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
