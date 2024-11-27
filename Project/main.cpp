#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>

int main (int, char**) {
    vector <Point> test;
    for (int i = 0; i < 100; i++) {
        test.push_back(Point(3).setAllCoord({randNumGen(-20, 20), randNumGen(-20, 20), randNumGen(-20, 20)}));
    }

}