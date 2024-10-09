cmake_minimum_required(VERSION 3.10)
project(Project1)

find_package(CGAL REQUIRED COMPONENTS Core)
find_package(Eigen3 3.1.0 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/classes/header)
include_directories(${CMAKE_SOURCE_DIR}/classes/source)

file(GLOB_RECURSE SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/classes/source/*.cpp"
        "${CMAKE_SOURCE_DIR}/libs/*.cpp"
)

add_executable(Project1 main.cpp ${SOURCE_FILES})

#add_subdirectory(${CMAKE_SOURCE_DIR}/libs)

target_include_directories(Project1 PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(Project1 PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Project1 CGAL::CGAL CGAL::CGAL_Core)
set(CMAKE_BUILD_TYPE "Release")