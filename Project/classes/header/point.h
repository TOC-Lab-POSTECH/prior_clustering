//
// Created by 신동훈 on 11/23/24.
//

#ifndef K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_POINT_H
#define K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_POINT_H

#include <vector>
#include "math.h"
#include <map>
using namespace std;

class Point{
public:
    Point(int d);
    double distance(const Point &other);
    vector<double> getCoord();
    vector<double> getCoordConst() const;
    Point& setAllCoord(vector<double> newCoord);
    void setCoord(int idx, double newVal);
    bool operator<(const Point& other) const;
private:
    vector<double> coord;
};

#endif //K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_POINT_H
