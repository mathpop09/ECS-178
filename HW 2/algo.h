#ifndef ALGO_H
#define ALGO_H

#include <vector>

using namespace std;

//data struct for coordinates
struct dim{
  double x;
  double y;
};

struct curve{
  vector<dim> coordinates;
};

class algo{
  //de Casteljau + Bernstein

public:
  void deCasteljau(vector<dim> coordinates, double t, int res);
  void Bernstein(vector<dim> coordinates, int res);
  dim singleT (vector<dim> points, double tVal);
  vector<vector<dim>> modSubDiv (vector<dim> curve);
  void IntersectionCheck(vector<dim> curve1, vector<dim> curve2, double tolerance);



private:
  vector<vector<int>> Pascals (int level);
  bool boxIntersection (vector<dim> points1, vector<dim> points2);
  double area (vector<dim> curve);
};

#endif // ALGO_H
