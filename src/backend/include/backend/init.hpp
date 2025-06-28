#pragma once

#include <string>

#include "backend/export.hpp"

namespace backend {

	extern "C" EXPORT void set_kernels_path(const std::string& path);

}