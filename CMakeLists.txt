cmake_minimum_required(VERSION 3.10)
project(diffgeomeng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(diffgeomeng
        src/classes/diff/Manifold.cpp
        src/classes/diff/Metric.cpp
        src/classes/compute/rk4_realize.cpp
        src/classes/compute/partical_differentiation.cpp
        src/classes/diff/ChristoffelSymbols.cpp
        src/classes/compute/invert_matrix.cpp
        src/classes/diff/Geodesic.cpp
        src/classes/visual/MetricGrid.cpp
        src/utility/functions.cpp
)

find_package(glm REQUIRED)

target_link_libraries(diffgeomeng PRIVATE glm::glm)

target_include_directories(diffgeomeng PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(diffgeomeng
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core
)