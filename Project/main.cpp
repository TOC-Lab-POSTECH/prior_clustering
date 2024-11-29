#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>
#include <iostream>
#include <chrono>

int main (int, char**) {
    vector <Point> test;
    for (int i = 0; i < 1000; i++) {
        test.push_back(Point(3).setAllCoord({randNumGen(-20, 20), randNumGen(-20, 20), randNumGen(-20, 20)}));
    }

    double eps = 0.5;

    auto start = chrono::high_resolution_clock::now();

    TwoMeans twomeans(test, eps, "raw");

    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(end - start);

    cout << "# of points: " << test.size() << endl;
    cout << "raw" << endl;
    cout << "cost: " << twomeans.getCost() << endl;
    cout << "centers: " << endl;
    for(auto& center : twomeans.getCenter()){
        for(int i = 0; i < center.getCoord().size(); i++){
            cout << center.getCoord()[i] << " ";
        }
        cout << endl;
    }
    cout << "time spent: " << duration.count() << "seconds" << endl;

    auto start2 = chrono::high_resolution_clock::now();

    TwoMeans twomeansgrid(test, eps, "grid");

    auto end2 = chrono::high_resolution_clock::now();

    auto duration2 = chrono::duration_cast<chrono::seconds>(end2 - start2);
    cout << "\ngrid" << endl;
    cout << "cost: " << twomeansgrid.getCost() << endl;
    cout << "centers: " << endl;
    for(auto& center : twomeansgrid.getCenter()){
        for(int i = 0; i < center.getCoord().size(); i++){
            cout << center.getCoord()[i] << " ";
        }
        cout << endl;
    }
    cout << "time spent: " << duration2.count() << "seconds" << endl;
}