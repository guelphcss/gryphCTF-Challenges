# whatev
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)
project(BabyVM)

add_executable(BabyVM)
target_sources(BabyVM
    PRIVATE
        main.cpp
)
