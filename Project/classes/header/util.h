//
// Created by 신동훈 on 11/23/24.
//

#ifndef K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_UTIL_H
#define K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_UTIL_H

#include "point.h"
#include <vector>
#include <limits>
#include <cmath>

double distance(const Point p1, const Point p2);

double randNumGen(double start, double end);

void Comb(vector<Point>& points, vector<vector<Point>>& ans, vector<Point> comb, int r, int idx, int depth);

vector<vector<Point>> Combination(vector<Point>& points, int r);

Point calculateCenter(vector<Point> points);

vector<Point> randSample(vector<Point> Points, int n);

vector<Point> sortbyDistance(vector<Point> points, Point ref);

double clusteringCost(vector<Point> points, vector<Point> centers);

vector<Point> slice(const std::vector<Point>& v, size_t start, size_t end);

Point roundPoint(Point point);

#endif //K_MEANS_CLUSTERING_OF_AXIS_PARALLEL_AFFINE_SUBSPACES_UTIL_H
