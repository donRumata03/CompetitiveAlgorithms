cmake_minimum_required(VERSION 3.17)
project(CompetitiveAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(./)

add_executable(CompetitiveAlgorithms
        main.cpp

        data_structures/segment_tree.hpp
        tests/segment_tree_test.hpp

        olymp_funcions.hpp

        data_structures/DSU.h)


project(the_task)
add_executable(the_task

        # task_solutions/segment_tree_A.cpp
        task_solutions/segment_tree_B.cpp

        )
