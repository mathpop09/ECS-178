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
  void NURBS (orders order, vector<vector<threeDim>> controlPoints, vector<vector<double>> weights,  vector<double> uKnots, vector<double> vKnots, int resolution);


private:
  //Move to 4D space
  vector<vector<fourDim>> move4Space (vector<vector<threeDim>> d, vector<vector<double>> weights);
  //evaluate in 4D space
  vector<vector<fourDim>> eval4Space (vector<vector<fourDim>> dStar, vector<double> uKnots, vector<double> vKnots, orders orderPair, int res);
  //Basic function computer
  double basisFunc (int upperVal, int lowerVal, double mainVal, vector<double> knotVector, int order);
  //project to 3D space
  vector<vector<threeDim>> proj3Space (vector<vector<fourDim>> sStar);
};

#endif // ALGO_H
