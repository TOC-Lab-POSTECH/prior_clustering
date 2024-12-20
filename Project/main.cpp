#include "util.h"
#include "point.h"
#include "twoMeans.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "testdata.h"

#include "TwoApproxTwoCenter.h"

int main(int, char**)
{
    vector <Point> randDist;

    // random distribution point set의 minimum, maximum 지정. (min ~ max 사이에서 무작위 실수 생성)
    int min = -10000;
    int max = 10000;
    for (int i = 0; i < 100; i++) { // i의 최대 반복 횟수를 변경하여 point의 개수 조절
        randDist.push_back(Point(3).setAllCoord({randNumGen(min, max), randNumGen(min, max), randNumGen(min, max)}));
    }

    // normal distribution point set의 mean, standard deviation 지정.
    vector<Point> NormDist;
    int mean1 = 50;
    int mean2 = -50;
    int sd = 25;
    for(int i = 0; i < 100; i++){ // i의 최대 반복 횟수를 변경하여 point의 개수 조절
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean1, sd), NormDistGen(mean1, sd), NormDistGen(mean1, sd)}));
    }
    for(int i = 0; i < 100; i++){ // i의 최대 반복 횟수를 변경하여 point의 개수 조절
        NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean2, sd), NormDistGen(mean2, sd), NormDistGen(mean2, sd)}));
    }

    int runtimes = 1;
    int* centers = TwoCenter::twoApprox_twoCenter(NormDist);
    std::cout << "Center 1: " << centers[0] << std::endl;
    std::cout << "Center 2: " << centers[1] << std::endl;
}

// int main (int, char**) {
//     vector <Point> randDist;

//     // random distribution point set의 minimum, maximum 지정. (min ~ max 사이에서 무작위 실수 생성)
//     int min = -10000;
//     int max = 10000;
//     for (int i = 0; i < 100; i++) { // i의 최대 반복 횟수를 변경하여 point의 개수 조절
//         randDist.push_back(Point(3).setAllCoord({randNumGen(min, max), randNumGen(min, max), randNumGen(min, max)}));
//     }

//     // normal distribution point set의 mean, standard deviation 지정.
//     vector<Point> NormDist;
//     int mean1 = 50;
//     int mean2 = -50;
//     int sd = 25;
//     for(int i = 0; i < 100; i++){ // i의 최대 반복 횟수를 변경하여 point의 개수 조절
//         NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean1, sd), NormDistGen(mean1, sd), NormDistGen(mean1, sd)}));
//     }
//     for(int i = 0; i < 100; i++){ // i의 최대 반복 횟수를 변경하여 point의 개수 조절
//         NormDist.push_back(Point(3).setAllCoord({NormDistGen(mean2, sd), NormDistGen(mean2, sd), NormDistGen(mean2, sd)}));
//     }

//     double eps = 1; // approximation factor epsilon.
//     int runtimes = 20;  // 테스트 실행 횟수

//     ManageData randDistData;    // 실험 정보 저장 data structure

//     // 일반 알고리즘에 대한 실험 결과
//     for(int i = 0; i < runtimes; i++){
//         auto start = chrono::high_resolution_clock::now();

//         TwoMeans twomeans(NormDist, eps, "raw");

//         auto end = chrono::high_resolution_clock::now();

//         auto duration = chrono::duration_cast<chrono::seconds>(end - start);

//         TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
//         randDistData.insert(newRandData);
//     }

//     randDistData.printAll();

//     randDistData.clear();

//     // grid rounding 에 대한 실험 결과
//     for(int i = 0; i < runtimes; i++){
//         auto start = chrono::high_resolution_clock::now();

//         TwoMeans twomeans(NormDist, eps, "grid");

//         auto end = chrono::high_resolution_clock::now();

//         auto duration = chrono::duration_cast<chrono::seconds>(end - start);

//         TestData newRandData(duration.count(), twomeans.getCost(), twomeans.getCenter());
//         randDistData.insert(newRandData);
//     }

//     randDistData.printAll();
// }