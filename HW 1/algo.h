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
  //de Castlejau

public:
  void deCastlejau(vector<dim> coordinates, double t, int res);
  void Bernstein(vector<dim> coordinates, int res);

private:
  vector<vector<int>> Pascals (int level);
};

#endif // ALGO_H
