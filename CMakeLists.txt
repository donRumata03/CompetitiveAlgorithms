cmake_minimum_required(VERSION 3.17)
project(CompetitiveAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(./)

add_executable(CompetitiveAlgorithms
        main.cpp

        data_structures/segment_tree.hpp
        tests/segment_tree_test.hpp

        olymp_functions.hpp

        data_structures/DSU.h
        tests/dsu_tests.h

        data_structures/graphs.h
        graphs/cruscal.h
        graphs/graph_is_connected.h

        numeric/factorization.h
        numeric/eratosphene_sieve.h
        tests/factorization_tests.h


        geometry/geom_base.h
        geometry/point_in_polygon.h
        geometry/polar_angle_sort.h
        tests/geometry/polar_angle_sorting_test.h

        geometry/convex_hull.h tests/geometry/convex_hull_test.h)


project(the_task)
add_executable(the_task

        # task_solutions/segment_tree_A.cpp
        # task_solutions/segment_tree_B.cpp

        # task_solutions/cruscal.cpp
        task_solutions/geometry/testing_point_in_polygon.cpp
        )
