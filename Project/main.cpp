#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "testdata.h"

int main (int, char**) {
    vector <Point> randDist;
    for (int i = 0; i < 100; i++) {
        randDist.push_back(Point(3).setAllCoord({randNumGen(-20, 20), randNumGen(-20, 20), randNumGen(-20, 20)}));
    }

    vector<Point> NormDist;
    for(int i = 0; i < 100; i++){
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(10, 5), NormDistGen(10, 5), NormDistGen(10, 5)}));
    }
    for(int i = 0; i < 50; i++){
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(-10, 5), NormDistGen(-10, 5), NormDistGen(-10, 5)}));
    }

    double eps = 0.5;
    int runtimes = 10;

    ManageData randDistData;

    for(int i = 0; i < runtimes; i++){
        auto start = chrono::high_resolution_clock::now();

        TwoMeans twomeans(NormDist, eps, "raw");

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::seconds>(end - start);

        TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
        randDistData.insert(newRandData);
    }

    randDistData.printSummary();

    randDistData.clear();

    for(int i = 0; i < runtimes; i++){
        auto start = chrono::high_resolution_clock::now();

        TwoMeans twomeans(NormDist, eps, "grid");

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::seconds>(end - start);

        TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
        randDistData.insert(newRandData);
    }

    randDistData.printSummary();
}