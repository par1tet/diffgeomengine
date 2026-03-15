cmake_minimum_required(VERSION 3.10)
project(diffgeomeng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(diffgeomeng INTERFACE)

find_package(glm REQUIRED)

target_link_libraries(diffgeomeng
    INTERFACE glm::glm
)

target_include_directories(diffgeomeng
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/core
)