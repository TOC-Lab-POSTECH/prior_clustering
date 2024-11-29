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

// gets points, approximation parameter epsilon. and create class that contains data of points, epsilon, clustering center, clustering cost.
TwoMeans::TwoMeans(vector<Point> points_, double epsilon_) :epsilon(epsilon_), points(points_){
    // Approximation parameters.
    double alpha = epsilon; // epsilon / 64

    // sampling size, superset size.
    int sampleSize = 10 / epsilon;
    int subsetSize = 2 / epsilon;

    // random sampling
    vector<Point> sampleSet = randSample(points, sampleSize);
    // superset
    vector<vector<Point>> superSet = Combination(sampleSet, subsetSize);
    // calculate centers.
    vector<Point> centerCandidates;
    for(auto& set : superSet){
        centerCandidates.push_back(calculateCenter(set));
    }

    vector<Point> Q;

    vector<pair<double, vector<Point>>> answerCandidates;

    for(auto& c1 : centerCandidates){
        // sort points according to distance from center candidate.
        Q = sortbyDistance(points, c1);
        // first half of the points
        int idx = Q.size() / 2;
        int prev = 0;
        double totalCost = 0;
        for(int i = 2; idx < Q.size(); i++){
            // again use superset sampling lemma.
            vector<Point> Q_i = slice(Q, 0, idx);
            vector<Point> Q_i_sample = randSample(Q_i, int(1 / pow(alpha, 2)));
            vector<vector<Point>> P2_candidates = Combination(Q_i_sample, int(1 / alpha));
            vector<Point> C2_candidates;
            for(auto& P2_candidate : P2_candidates){
                C2_candidates.push_back(calculateCenter(P2_candidate));
            }
            for(auto& C2_candidate : C2_candidates){
                // pair <c1, c2> could be the answer. we will check it at the end of this algorithm.
                vector<Point> insertCenters = {c1, C2_candidate};
                answerCandidates.push_back(make_pair(clusteringCost(points, insertCenters), insertCenters));
            }
            prev = idx;
            idx = idx + (Q.size() / pow(2, i)) + 1;
        }
    }

    double minAnswerCost = numeric_limits<double>::infinity();
    pair<double, vector<Point>> answer;
    // find center pair which has the minimum clustering cost.
    for(auto& candidatePair: answerCandidates) {
        if (candidatePair.first < minAnswerCost) {
            minAnswerCost = candidatePair.first;
            answer = candidatePair;
        }
    }
    // set the clustering cost and clustering centers.
    cost = answer.first;
    centers = answer.second;
};