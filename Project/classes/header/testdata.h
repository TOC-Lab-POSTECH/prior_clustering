//
// Created by 신동훈 on 12/2/24.
//

#ifndef PROJECT1_TESTDATA_H
#define PROJECT1_TESTDATA_H

#include <vector>
#include "point.h"

using namespace std;
class TestData{
private:
    int time;
    double cost;
    vector<Point> centers;
public:
    TestData(int t, double c, vector<Point> ce);
    int getTime();
    double getCost();
    vector<Point> getCenters();
};


class ManageData{
private:
    vector<TestData> datas;
public:
    ManageData();
    void insert(TestData newData);
    void printAll();
    void printSummary();
};

#endif //PROJECT1_TESTDATA_H
