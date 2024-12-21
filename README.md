This repository contains two clustering algorithms - 2-approximation 2-center algorithm and (1+$\varepsilon$)-approximation 2-means clustering. Given the set of points, these algorithms return two _centers_ satisfying each objective function. We implement theses algorithms on C++.

Note that we implemented these algorithms to use them in the experiments for the main research and development of our project.

# Requirements
- [boost](https://www.boost.org/)
- [CGAL](https://www.cgal.org/)

Note that CGAL has the dependency on the boost library since it uses the boost graph library. Thus, we recommend to download both libraries together following the package manager of CGAL.

# Algorithms
## 2-Center Approximation Algorithm
The problem $k$-_Center_ is defined as follows: Given the set $S$ of points on the Euclidean space, find the $k$ balls $\mathcal B$ such that the union of the balls covers all points of $S$ while minimizing $\text{max}_{v\in S}d(v, B_v)$, where $B_v$ is the ball covering $v$ and $d(\cdot, \cdot)$ is the (Euclidean) distance function. In other words, we want to find the balls minimizing the maximum radii.
__The 2-approximation 2-Center algorithm__ is an algorithm that provides a solution to the 2-Center problem with an approximation factor of 2, i.e., the algorithm guarantees that the objective value of its solution is at most twice the optimal value.
Our implementation outputs the centers of the solution (i.e., the centers of the balls). It is a basic 2-approximation 2-Center algorithm based on a greedy technique. Specifically, the algorithm works as follows:
1.  Pick an arbitrary point in $S$ as the first center.
2.  Select the farthest point from the first center as the second center.

## 2-Means Approximation Algorithm
The problem $k$-_Means_ is defined as follows: Given the set $S$ of points on the Euclidean space, find the $k$ points $\mathcal C$ minimizing the sum of the square of the distance between each point and its corresponding center, i.e., $min_{v\in S} d(v, argmin_{c\in C} d(v,c))$, where $d(\cdot, \cdot)$ is the (Euclidean) distance function.
__The $(1+\varepsilon)$-approximation 2-Means algorithm__ is an algorithm that provides a solution to the 2-Means problem with an approximation factor of $(1+\varepsilon)$, i.e., the algorithm guarantees that the objective value of its solution is at most twice the optimal value. Note that $\varepsilon$ is also given with the problem instance.
Our implementation outputs the centers of the solution. It is based on the work of [[Kumar, Sabharwal, and Sen 04]](https://ieeexplore.ieee.org/abstract/document/1366265).



# How to run(On Mac)
We use [brew](https://brew.sh/) to install the requirements.
1. install(terminal)
    ```
   brew install cmake
   brew install cgal
   ```
   
2. (If you did not clone this repository, then this step may be required.) Configure CMakeLists.txt(Refer to CMakeLists.txt at the root folder)

4. create and move to the build folder(on the Project folder)
   ```
   mkdir build
   cd build
   ```
5. run cmake
   ```
   cmake ..
   ```
6. run make to create the execution
   ```
   make
   ```
   
7. run execution.(named Project1)
   ```
   ./Project1
   ```
   
