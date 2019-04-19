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
  void deCastlejau(vector<dim> coordinates);

};

#endif // ALGO_H
