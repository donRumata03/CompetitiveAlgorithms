#include <iostream>
#include <tests/segment_tree_test.hpp>

#include <data_structures/DSU.h>
#include <tests/dsu_tests.h>
#include <tests/factorization_tests.h>
#include <tests/geometry/polar_angle_sorting_test.h>
#include <tests/geometry/convex_hull_test.h>

int main ()
{
	/// Segment Tree:

	// stree_building_test();

	// stree_sum_test8();
	// stree_sum_test3();

	// stree_getting_test3();
	// stree_getting_test8();

	// stree_setting_test3();
	// test_min_and_max_stree();

	/// DSU:

	// test_dsu_working_ability();
	// test_dsu_computational_complexity();

	/// Graphs:


	/// Numeric:
	// test_eratosphene_factorization();

	/// Geometry:
	// test_sorting_by_polar_angle();
	test_convex_hull();

	return 0;
}
