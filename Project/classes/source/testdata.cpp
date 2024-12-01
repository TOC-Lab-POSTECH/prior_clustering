//
// Created by 신동훈 on 12/2/24.
//
#include "testdata.h"
#include <iostream>

using namespace std;

TestData::TestData(int t, double c, vector<Point> ce) :time(t), cost(c), centers(ce){};

int TestData::getTime() {
    return time;
}

double TestData::getCost() {
    return cost;
}

vector<Point> TestData::getCenters() {
    return centers;
}

//===================================================

ManageData::ManageData() {};

void ManageData::insert(TestData newData) {
    datas.push_back(newData);
}

void ManageData::printAll() {
     for(int i = 0; i < datas.size(); i++){
         cout << "test case " << i + 1 << "\n"
         << "run time: " << datas[i].getTime() << "\n"
         << "cost: " << datas[i].getCost() << "\n"
         << "centers: " << endl;
         for(int j = 0; j < datas[i].getCenters().size(); j++){
             for(int k = 0; k < datas[i].getCenters()[j].getCoord().size(); k++){
                 cout << datas[i].getCenters()[j].getCoord()[k] << " ";
             }
             cout << endl;
         }
         cout << endl;
     }
     printSummary();
}

void ManageData::printSummary() {
    float totalTime = 0;
    float totalCost = 0;
    for(int i = 0; i < datas.size(); i++){
        totalTime += datas[i].getTime();
        totalCost += datas[i].getCost();
    }
    cout << "Avg Time Spent: " << totalTime/datas.size() << " Seconds" << endl;
    cout << "Avg Cost: " << totalCost/datas.size() << endl;
}

void ManageData::clear() {
    datas.clear();
}