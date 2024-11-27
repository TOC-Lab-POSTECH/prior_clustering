//
// Created by 신동훈 on 11/27/24.
//
#include "twoMeans.h"
#include <iostream>

vector<Point> TwoMeans::getCenter() {
    return centers;
}

double TwoMeans::getCost() {
    return cost;
}


TwoMeans::TwoMeans(vector<Point> points_, double epsilon_) :epsilon(epsilon_), points(points_){
    double alpha = epsilon;
    int sampleSize = 10 / epsilon;
    int subsetSize = 2 / epsilon;

//    int qr = 0;

    vector<Point> sampleSet = randSample(points, sampleSize);
    vector<vector<Point>> superSet = Combination(sampleSet, subsetSize);

    vector<Point> centerCandidates;
    for(auto& set : superSet){
        centerCandidates.push_back(calculateCenter(set));
    }
//    cout << centerCandidates.size() << endl;

    vector<Point> Q;

    vector<pair<double, vector<Point>>> answerCandidates;

    for(auto& c1 : centerCandidates){
        Q = sortbyDistance(points, c1);
        int idx = Q.size() / 2;
        int prev = 0;
        double totalCost = 0;
//        cout << idx << " " << centerCandidates.size()<<endl;
        for(int i = 2; idx < Q.size(); i++){
            vector<Point> Q_i = slice(Q, 0, idx);
            vector<Point> Q_i_sample = randSample(Q_i, int(1 / pow(alpha, 2)));
            vector<vector<Point>> P2_candidates = Combination(Q_i_sample, int(1 / alpha));
            vector<Point> C2_candidates;
            for(auto& P2_candidate : P2_candidates){
                C2_candidates.push_back(calculateCenter(P2_candidate));
            }
            for(auto& C2_candidate : C2_candidates){
                vector<Point> insertCenters = {c1, C2_candidate};
                answerCandidates.push_back(make_pair(clusteringCost(points, insertCenters), insertCenters));
            }
            prev = idx;
            idx = idx + (Q.size() / pow(2, i)) + 1;
//            cout << idx << " " << Q.size() << endl;
        }
//        cout << qr++ << endl;
    }
    double minAnswerCost = numeric_limits<double>::infinity();
    pair<double, vector<Point>> answer;
    for(auto& candidatePair: answerCandidates) {
        if (candidatePair.first < minAnswerCost) {
            minAnswerCost = candidatePair.first;
            answer = candidatePair;
        }
    }
    cost = answer.first;
    centers = answer.second;
};