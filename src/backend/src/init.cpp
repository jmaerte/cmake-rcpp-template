#include "backend/init.hpp"

#include "CL_context.hpp"

namespace backend {

	extern "C" void set_kernels_path(const std::string& path) {
	    CL_context::instance().set_kernels_path(path);
	}

}