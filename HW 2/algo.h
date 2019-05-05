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
  void Bernstein(vector<dim> coordinates, int res);
  void BernsteinYellow (vector<dim> coordinates, int res);
  void BernsteinMagneta (vector<dim> coordinates, int res);
  dim singleT (vector<dim> points, double tVal);
  void degreeRaised (vector<dim> points, int res);
  void degreeLowerAvg (vector<dim> points, int res);


private:
  vector<vector<int>> Pascals (int level);
  vector<dim> degreeLowerL (vector<dim> points);
  vector<dim> degreeLowerR (vector<dim> points);
};

#endif // ALGO_H
