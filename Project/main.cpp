#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>
#include <iostream>

int main (int, char**) {
    vector <Point> test;
    for (int i = 0; i < 100; i++) {
        test.push_back(Point(3).setAllCoord({randNumGen(-20, 20), randNumGen(-20, 20), randNumGen(-20, 20)}));
    }

    double eps = 0.5;

    TwoMeans twomeans(test, eps, "grid");

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

}