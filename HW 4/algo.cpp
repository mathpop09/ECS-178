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


//Draw NURBS

vector<fourDim> algo::move4Space (vector<threeDim> d, vector<double> weights)
{
  vector<fourDim> newVector;
  for (int i = 0; i < d.size(); i++)
  {
    fourDim newVectorElem = {d[i].x * weights[i], d[i].y * weights[i], d[i].z * weights[i], weights[i]};
    newVector.push_back(newVectorElem);
  }
  return newVector;
}
