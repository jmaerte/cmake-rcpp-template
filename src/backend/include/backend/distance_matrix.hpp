#pragma once

#include "backend/export.hpp"

#include <string>

namespace backend {

	extern "C" EXPORT void distance_matrix(double* data, int rows, int cols, double* res);

}