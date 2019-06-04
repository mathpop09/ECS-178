#ifndef ALGO_H
#define ALGO_H

#include <vector>

using namespace std;

//data struct for coordinates
struct dim{
  double x;
  double y;
};

struct bSpline{
  vector<dim> control_points;
  vector<double> knots;
};

struct curve{
  vector<dim> coordinates;
};

class algo{
  //de Casteljau + Bernstein

public:
  void Bernstein (vector<dim> coordinates, int res);
  void BSpline (vector<dim> points, vector<double> knots);
  double EucDistance (dim point1, dim point2);
  //enter control points and get the knot vector
  vector<double> EucKnot(vector<dim> points, int order);
  void c2Algo (vector<dim> coordinates, int parametrization, int res);
  void deBoors(vector<dim> coordinates, int order, int res);
  void c1Algo (vector<dim> coordinates, dim vector1, dim vector2, int res);


private:
  vector<vector<int>> Pascals (int level);
  vector<double> tridiagonal_solver(vector<double> a, vector<double> b, vector<double> c, vector<double> f);
  double twoPointDistance (dim point1, dim point2);
  bool isOdd(int num);
};

#endif // ALGO_H
