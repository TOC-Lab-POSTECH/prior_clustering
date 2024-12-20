//
// Created by 신동훈 on 11/27/24.
//

#ifndef PROJECT1_TWOMEANS_H
#define PROJECT1_TWOMEANS_H

#include "point.h"
#include "util.h"
#include <vector>
#include <string>

class TwoMeans{
private:
    double epsilon;
    vector<Point> points;
    vector<Point> centers;
    double cost;
public:
    TwoMeans(vector<Point> points_, double epsilon_, string type_);
    vector<Point> getCenter();
    double getCost();
};

#endif //PROJECT1_TWOMEANS_H
