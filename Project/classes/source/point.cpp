//
// Created by 신동훈 on 11/23/24.
//

//
// Created by 신동훈 on 11/13/24.
//

#include "point.h"

Point::Point(int d) : coord(d,0) {};

double Point::distance(const Point &other) {
    double dist = 0;
    for(size_t i = 0; i < coord.size(); i++){
        dist += std::pow(coord[i] - other.coord[i], 2);
    }
    return sqrt(dist);
};

vector<double> Point::getCoord() {
    return coord;
};

vector<double> Point::getCoordConst() const{
    return coord;
};

Point& Point::setAllCoord(vector<double> newCoord) {
    coord = newCoord;
    return *this;
}

void Point::setCoord(int idx, double newVal) {
    coord[idx] = newVal;
}

bool Point::operator<(const Point& other) const{
    return coord < other.getCoordConst();
}