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

vector<vector<Point>> Combination(vector<Point>& points, int r){
    vector<vector<Point>> ans;
    vector<Point> comb;
    comb.reserve(r);

//    for(int i = 0; i < points.size(); i++){
//        for(int k = 0; k < points[i].getCoord().size(); k++){
//            cout << points[i].getCoord()[k] << " ";
//        }
//        cout << endl;
//    }

    for(int i = 0; i < r; i++){
        comb.emplace_back(points[0].getCoord().size());
    }

    Comb(points, ans, comb, r, 0, 0);
    return ans;
}

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

vector<Point> slice(const std::vector<Point>& v, size_t start, size_t end) {
    if (start > end || end > v.size()) {
        throw std::out_of_range("Invalid slice range");
    }
    return vector<Point>(v.begin() + start, v.begin() + end);
}