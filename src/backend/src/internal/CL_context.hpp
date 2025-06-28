#pragma once

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_TARGET_OPENCL_VERSION 210
#define CL_HPP_TARGET_OPENCL_VERSION 210
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <CL/opencl.hpp>

#include <string>
#include <mutex>

namespace backend {


	/**
	 * 	A singleton class managing the external library state (in this case OpenCL).
	 * 	
	 * 	Other patterns can obviously be used but in this rare occation singletons are
	 * 	actually a good choice.
	 * 	
	 * 	The instance gets initialized once "instance()" is called; in our case this is in the
	 * 	.onLoad call of R (i.e. whenever the package is loaded using library(...) or the namespace decorator CMakeRcppTemplate:: is used)
	 * 	If .onLoad would not call SetKernelsPath the initialization would happen on first C-function call using the CL_context.
	 * 
	 */
	class CL_context {
	public:
		// gets the static linkage CL state
	    static CL_context& instance();

		// attaches the resources path
	    void set_kernels_path(const std::string& str);
		// retrieves the resources path
	    std::string get_kernels_path() const;

		// get the current CL context
	    const cl::Context& get_context() const;
		// get the current command queue
	    const cl::CommandQueue& get_queue() const;
		// get the used device
	    const cl::Device& get_device() const;

		// Build a program from a kernel file
	    cl::Program get_program(const std::string& filepath) const;

	private:
		// Initializer runs the typical init code for your external library
	    CL_context();
		// Destructor cleans up the external library state
	    ~CL_context();

		// thread safe singleton
	    CL_context(const CL_context&) = delete;
	    CL_context& operator=(const CL_context&) = delete;


	    // CL constants:
        cl::Device best_device;
		cl::Platform best_platform;
	    cl::Context context;
	    cl::CommandQueue queue;

		// attached resource path
	    std::string kernels_path;

		// thread safety
	    mutable std::mutex mutex;
	};

}