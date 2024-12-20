#include "TwoApproxTwoCenter.h"

int* TwoCenter::twoApprox_twoCenter(vector<Point> points_) {
    // output centers as an array
    int* centers = new int[2]{-1, -1};
    int num_points = points_.size();
    
    // Set the random seed for choosing the first center uniformly at random
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(0, num_points - 1);
    boost::variate_generator<boost::random::mt19937&, boost::random::uniform_int_distribution<> > choose(gen, dist);

    // Choose the first center uniformly at random
    centers[0] = choose();

    // Check the distance of each point to the first center
    double max_dist = 0;
    for(size_t i = 0; i < num_points; i++){
        double dist = distance(points_[i], points_[centers[0]]);
        if(dist > max_dist){
            max_dist = dist;
            centers[1] = i;
        }
    }

    // vaildity check
    if(centers[0] == -1 || centers[1] == -1){
        throw invalid_argument("Invalid centers");
    }

    return centers;
}