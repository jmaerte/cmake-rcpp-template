#pragma once

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_TARGET_OPENCL_VERSION 210
#define CL_HPP_TARGET_OPENCL_VERSION 210
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <CL/opencl.hpp>

#include <string>
#include <mutex>

namespace backend {

	class CL_context {
	public:
	    static CL_context& instance();

	    void set_kernels_path(const std::string& str);
	    std::string get_kernels_path() const;
	    const cl::Context& get_context() const;
	    const cl::CommandQueue& get_queue() const;
	    const cl::Device& get_device() const;

	    cl::Program get_program(const std::string& filepath) const;

	private:
	    CL_context();                      // Private constructor
	    ~CL_context();                     // Destructor

	    CL_context(const CL_context&) = delete;
	    CL_context& operator=(const CL_context&) = delete;

	    // CL constants:
        cl::Device best_device;
		cl::Platform best_platform;
	    cl::Context context;
	    cl::CommandQueue queue;

	    std::string kernels_path;
	    mutable std::mutex mutex;
	};

}