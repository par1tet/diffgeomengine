cmake_minimum_required(VERSION 3.10)
project(diffgemeng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/classes/diff/Manifold.cpp
)

find_package(glm REQUIRED)

target_link_libraries(diffgemeng PRIVATE glm::glm)

target_include_directories(diffgemeng PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})