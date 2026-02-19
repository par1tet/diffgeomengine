cmake_minimum_required(VERSION 3.10)
project(diffgemeng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/classes/diff/Manifold.cpp
        src/classes/diff/Metric.cpp
        src/classes/compute/rk4_realize.cpp
        src/classes/compute/partical_differentiation.cpp
        src/classes/diff/ChristoffelSymbols.cpp
        src/classes/compute/invert_matrix.cpp
        src/classes/diff/Geodesic.cpp
        src/classes/visual/MetricGrid.cpp
        src/utility/createShaderProgram.cpp
        src/utility/functions.cpp
)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(diffgemeng PRIVATE glad glfw OpenGL::GL glm::glm)

target_include_directories(diffgemeng PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})