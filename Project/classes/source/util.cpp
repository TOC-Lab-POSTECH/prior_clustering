//
// Created by 신동훈 on 11/23/24.
//

//
// Created by 신동훈 on 11/13/24.
//
#include "util.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

double distance(Point p1, Point p2) {
    double sum = 0.0;
    for (int i = 0; i < p1.getCoord().size(); i++) {
        sum += pow(p1.getCoord()[i] - p2.getCoord()[i], 2);
    }
    return sqrt(sum);
}

double randNumGen(double start, double end){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(start, end);
    return dis(gen);
}