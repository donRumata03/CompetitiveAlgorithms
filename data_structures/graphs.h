//
// Created by Vova on 14.01.2021.
//

#pragma once

#include <olymp_funcions.hpp>


template<class Weight>
struct base_edge {
	li first = -1;
	li second = -1;

	Weight weight = 1;
};

using int_edge = base_edge<li>;
using float_edge = base_edge<double>;


