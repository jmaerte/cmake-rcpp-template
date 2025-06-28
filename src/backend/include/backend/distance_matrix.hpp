#pragma once

#include "backend/export.hpp"

#include <string>

namespace backend {

	/**
	 * 	FUNCTION TO CALCULATE THE DISTANCE MATRIX OF data AND WRITE IT INTO res.
	 * 
	 * 	data is a 1d array of length rows * cols.
	 * 	res is a 1d array of length rows * rows.
	 */
	extern "C" EXPORT void distance_matrix(double* data, int rows, int cols, double* res);

}