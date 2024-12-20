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
TwoMeans::TwoMeans(vector<Point> points_, double epsilon_, string type_) :epsilon(epsilon_), points(points_){
    if(type_ == "raw"){ // algorithm for
        // Approximation parameters.
        double alpha = epsilon; // in paper, use alpha as epsilon / 64.

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
    }
    else if(type_ == "grid"){   // algorithm for approx. using grid.
        // algorithms except processing raw data to grid data are similar to the raw algorithm.
        // Approximation parameter.
        double alpha = epsilon;

        // sampling size, superset
        int sampleSize = 10 / epsilon;
        int subsetSize = 2 / epsilon;

        // random sampling.
        vector<Point> sampleSet = randSample(points, sampleSize);
        // superset.
        vector<vector<Point>> superSet = Combination(sampleSet, subsetSize);

        map<Point, vector<Point>> c1_gridmap;   // mapping for raw coord -> grid coord
        for(auto& set : superSet){
            Point cal_c1 = calculateCenter(set);
            Point approxPoint = roundPoint(cal_c1);
            auto it = c1_gridmap.find(approxPoint);
            if(it == c1_gridmap.end()){
                vector<Point> newVector;
                newVector.push_back(cal_c1);
                c1_gridmap.insert({approxPoint, newVector});
            }
            else{
                it->second.push_back(cal_c1);
            }
        }

        vector<Point> Q;

        vector<pair<double, vector<Point>>> answerCandidates;

        for(auto& [c1_gridpoint, c1_rawList] : c1_gridmap){
            Q = sortbyDistance(points, c1_gridpoint);
            int idx = Q.size() / 2;
            int prev = 0;
            double totalCost = 0;
            for(int i = 2; idx < Q.size(); i++){
                vector<Point> Q_i = slice(Q, 0, idx);
                vector<Point> Q_i_sample = randSample(Q_i, int(1 / pow(alpha, 2)));
                vector<vector<Point>> P2_candidates = Combination(Q_i_sample, int(1 / alpha));
                map<Point, vector<Point>> c2_gridmap;
                for(auto& P2_candidate : P2_candidates){
                    Point cal_c2 = calculateCenter(P2_candidate);
                    Point approxPoint2 = roundPoint(cal_c2);
                    auto it = c2_gridmap.find(approxPoint2);
                    if(it == c2_gridmap.end()){
                        vector<Point> newVector2;
                        newVector2.push_back(cal_c2);
                        c2_gridmap.insert({approxPoint2, newVector2});
                    }
                    else{
                        it->second.push_back(cal_c2);
                    }
                }
                for(auto& [c2_gridpoint, c2_rawList] : c2_gridmap){
                    vector<Point> insertCenters = {c1_gridpoint, c2_gridpoint};
                    answerCandidates.push_back(make_pair(clusteringCost(points, insertCenters), insertCenters));

                }
                prev = idx;
                idx = idx + (Q.size() / pow(2, i)) + 1;
            }
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
    }
};

