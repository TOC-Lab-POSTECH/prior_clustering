#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "testdata.h"

int main (int, char**) {
    vector <Point> randDist;

    int min = -10000;
    int max = 10000;
    for (int i = 0; i < 100; i++) {
        randDist.push_back(Point(3).setAllCoord({randNumGen(min, max), randNumGen(min, max), randNumGen(min, max)}));
    }

    vector<Point> NormDist;
    int mean1 = 50;
    int mean2 = -50;
    int sd = 25;
    for(int i = 0; i < 100; i++){
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean1, sd), NormDistGen(mean1, sd), NormDistGen(mean1, sd)}));
    }
    for(int i = 0; i < 100; i++){
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean2, sd), NormDistGen(mean2, sd), NormDistGen(mean2, sd)}));
    }

    double eps = 1;
    int runtimes = 20;

    ManageData randDistData;

    for(int i = 0; i < runtimes; i++){
        auto start = chrono::high_resolution_clock::now();

        TwoMeans twomeans(NormDist, eps, "raw");

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::seconds>(end - start);

        TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
        randDistData.insert(newRandData);
    }

    randDistData.printAll();

    randDistData.clear();

    for(int i = 0; i < runtimes; i++){
        auto start = chrono::high_resolution_clock::now();

        TwoMeans twomeans(NormDist, eps, "grid");

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::seconds>(end - start);

        TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
        randDistData.insert(newRandData);
    }

    randDistData.printAll();
}