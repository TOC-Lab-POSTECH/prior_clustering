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

// 두 point 사이의 euclidean distance를 반환
double distance(Point p1, Point p2) {
    double sum = 0.0;
    for (int i = 0; i < p1.getCoord().size(); i++) {
        sum += pow(p1.getCoord()[i] - p2.getCoord()[i], 2);
    }
    return sqrt(sum);
}

/*
 * Point 생성시 coordinates의 무작위 생성을 위한 util fn.
 * start와 end 사이의 무작위 난수를 반환
 * */
double randNumGen(double start, double end){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(start, end);
    return dist(gen);
}

/*
 * Point 생성 시 Coordinates의 Normal Distribution을 통항 생성을 위한 util fn
 *
 *
 * */
double NormDistGen(double mean, double std_){
    random_device rd;
    mt19937 gen(rd());
    std::normal_distribution<> dist(mean, std_);
    return dist(gen);
}

// Combination fn을 위한 divide&conquer.
void Comb(vector<Point>& points, vector<vector<Point>>& ans, vector<Point> comb, int r, int idx, int depth){
    if(r == 0){
        ans.push_back(comb);
//        for(int i = 0; i < comb.size(); i++){
//            for(int j = 0; j < comb[i].getCoord().size(); j++){
//                cout << comb[i].getCoord()[j] << " ";
//            }
//        }
//        cout << endl;
//        cout << ans.size()<<endl;
        return;
    }

    if(depth == points.size()){
        return;
    }

    Comb(points, ans, comb, r, idx, depth + 1);

    comb[idx] = points[depth];
    Comb(points, ans, comb, r - 1, idx + 1, depth + 1);
}

// Point vevtor를 받아 그 중 r개의 조합 vector를 element로 하는 vector를 반환.
// superset lemma 를 위해 사용됨.
vector<vector<Point>> Combination(vector<Point>& points, int r){
    vector<vector<Point>> ans;
    vector<Point> comb;
    comb.reserve(r);

    for(int i = 0; i < r; i++){
        comb.emplace_back(points[0].getCoord().size());
    }

    Comb(points, ans, comb, r, 0, 0);
    return ans;
}

// Point vector를 받아 해당 Point들의 center를 반환하는 함수.
Point calculateCenter(vector<Point> points){
    int totalNum = points.size();
    vector<double> newCoord(points[0].getCoord().size());
    for(int i = 0; i < totalNum; i++){
        for(int j = 0; j < points[i].getCoord().size(); j++){
            newCoord[j] += points[i].getCoord()[j];
        }
    }
    for(int i = 0; i < newCoord.size(); i++){
        newCoord[i] = newCoord[i] / totalNum;
    }
    Point newPoint(points[0].getCoord().size());
    newPoint.setAllCoord(newCoord);
    return newPoint;
}
// Point vector를 받아 그 중 n개를 random sampling 하는 함수.
vector<Point> randSample(vector<Point> points, int n){
    if (n > points.size()) {
        throw invalid_argument("n is larger than the size of points");
    }

    vector<int> indices(points.size());
    for (int i = 0; i < points.size(); ++i) {
        indices[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(indices.begin(), indices.end(), gen);

    vector<Point> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(points[indices[i]]);
    }

    return result;
}
// Point들을 어떤 한 점 ret에 대해 먼 순서대로 sort하는 함수.
vector<Point> sortbyDistance(vector<Point> points, Point ref){
    vector<pair<double, Point>> dist;
    for(auto& point : points){
        double pointDist = distance(ref, point);
        dist.push_back(make_pair(pointDist, point));
    }

    sort(dist.begin(), dist.end(), [](pair<double, Point>& a, pair<double, Point>& b) {
        return a.first > b.first;
    });

    vector<Point> ret;
    for(auto& item : dist){
        ret.push_back(item.second);
    }
    return ret;
}
// 구해진 clustering center들에 대해 전제 points들의 clustering cost를 계산하는 함수.
double clusteringCost(vector<Point> points, vector<Point> centers){
    double totalCost = 0;
    for(auto& point: points){
        double minDist = numeric_limits<double>::infinity();
        for(auto& center : centers){
            minDist = min(minDist, distance(point, center));
        }
        totalCost += pow(minDist, 2);
    }
    return totalCost;
}
// Points vector를 start idx부터 end idx까지 slicing 하는 함수.
vector<Point> slice(const std::vector<Point>& v, size_t start, size_t end) {
    if (start > end || end > v.size()) {
        throw std::out_of_range("Invalid slice range");
    }
    return vector<Point>(v.begin() + start, v.begin() + end);
}
// 한 점을 integer grid위로 옮기는 함수.
Point roundPoint(Point point){
    Point ret(point.getCoord().size());
    for(int i = 0; i < point.getCoord().size(); i++){
        ret.setCoord(i, round(point.getCoord()[i]));
    }
    return ret;
}