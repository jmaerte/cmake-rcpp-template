#pragma once

#include <string>

#include "backend/export.hpp"

namespace backend {

	/**
	 * 	Attaches a kernel path to the static linkage OpenCL state singleton.
	 */
	extern "C" EXPORT void set_kernels_path(const std::string& path);

}