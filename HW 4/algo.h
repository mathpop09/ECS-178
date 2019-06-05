#ifndef ALGO_H
#define ALGO_H

#include <vector>

using namespace std;

struct cpDim{
  int row;
  int col;
};
//data struct for two orders
struct orders{
  int uKnotO_k;
  int vKnotO_l;
};

//data struct for coordinates
struct threeDim{
  double x;
  double y;
  double z;
};

struct fourDim{
  double x;
  double y;
  double z;
  double w;
};

/*
struct NURBs{
  vector<dim> control_points;
  vector<double> knots;
};
*/



class algo{
  //NURBS

public:
  //project to 3D space
  vector<threeDim> proj3Space (vector<fourDim> sStar);


private:
  //Move to 4D space
  vector<fourDim> move4Space (vector<threeDim> d, vector<double> weights);
  //evaluate in 4D space
  vector<fourDim> eval4Space (vector<fourDim> dStar, orders orderPair);


  vector<vector<int>> Pascals (int level);
  vector<double> tridiagonal_solver(vector<double> a, vector<double> b, vector<double> c, vector<double> f);
};

#endif // ALGO_H
