#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "algo.h"

using namespace std;

void algo::deCastlejau (vector<dim> coordinates, double t)
{

  dim tPoint;
  //number of dots to be connected
  int resolution = 100;
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
          cout << drawT << endl;
          cout << tVals[h] << endl;
          if (abs(tVals[h] - drawT) < 0.005) {
            cout << "welcome" << endl;
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

/*
void algo::Bernstein (vector<dim> coordinates) {

}
*/
