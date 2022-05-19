#pragma once
#include "stdxx/grid2.hxx"
#include "utils.hxx"

std::vector<stx::vector2i> a_star(
	const stx::grid2<int> & graph,
	const stx::vector2i & start,
	const stx::vector2i & end);