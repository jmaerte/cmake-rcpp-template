#include "CL_context.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>


namespace backend {

	CL_context::CL_context() {
		// Step 1: Get all platforms
		std::vector<cl::Platform> platforms;
        	try {
		    cl::Platform::get(&platforms);
		    if (platforms.empty()) {
		        throw std::runtime_error("No OpenCL platforms found.");
		    }
		} catch (cl::Error &e) {
			std::cerr << "*** IMPORTANT: No OpenCL platforms where found! Make sure you have a graphics driver installed for your hardware! ***" << std::endl;
			std::cerr << "*** HINT: NVIDIA Drivers might not be loaded even though they were installed due to 'Secure Boot' being enabled ***" << std::endl;
		    throw std::runtime_error("OpenCL error: " + std::string(e.what()) + " (" + std::to_string(e.err()) + ")");
		}

		bool found = false;

		for (const auto& platform : platforms) {
		    std::vector<cl::Device> devices;
		    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

		    for (const auto& dev : devices) {
		        cl_device_type type = dev.getInfo<CL_DEVICE_TYPE>();
		        cl_uint compute_units = dev.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
		        std::string name = dev.getInfo<CL_DEVICE_NAME>();
		        std::string vendor = dev.getInfo<CL_DEVICE_VENDOR>();

		        std::cout << "Found device: " << name << " (" << vendor << ")"
		                  << " | Type: " << (type == CL_DEVICE_TYPE_GPU ? "GPU" :
		                                     type == CL_DEVICE_TYPE_CPU ? "CPU" :
		                                     type == CL_DEVICE_TYPE_ACCELERATOR ? "Accelerator" : "Other")
		                  << " | Compute Units: " << compute_units << "\n";

		        // Prioritize GPU over others
		        if (!found || (type == CL_DEVICE_TYPE_GPU && best_device.getInfo<CL_DEVICE_TYPE>() != CL_DEVICE_TYPE_GPU) ||
		            (type == best_device.getInfo<CL_DEVICE_TYPE>() && compute_units > best_device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>())) {
		            best_device = dev;
		            best_platform = platform;
		            found = true;
		        }
		    }
		}

		if (!found) {
		    throw std::runtime_error("No suitable OpenCL devices found.");
		}

		std::cout << "Selected device: " << best_device.getInfo<CL_DEVICE_NAME>()
		          << " on platform: " << best_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

		// Use best_device and best_platform to create context and queue:
		context = cl::Context(best_device);
		queue = cl::CommandQueue(context, best_device);
	}

	CL_context::~CL_context() {}

	CL_context& CL_context::instance() {
	    static CL_context instance;
	    return instance;
	}

	void CL_context::set_kernels_path(const std::string& path) {
	    std::lock_guard<std::mutex> lock(mutex);
	    kernels_path = path;
	}

	std::string CL_context::get_kernels_path() const {
	    std::lock_guard<std::mutex> lock(mutex);
	    return kernels_path;
	}

    const cl::Context& CL_context::get_context() const {
    	return context;
    }

	const cl::CommandQueue& CL_context::get_queue() const {
		return queue;
	}

	const cl::Device& CL_context::get_device() const {
		return best_device;
	}


	cl::Program CL_context::get_program(const std::string& filename) const {
		std::ifstream file(kernels_path + "/" + filename);
	    if (!file.is_open()) {
	        throw std::runtime_error("Failed to open kernel file: " + filename);
	    }
	    std::stringstream ss;
	    ss << file.rdbuf();
	    std::string kernel_str = ss.str();

	    std::cout << kernel_str << std::endl;

		cl::Program::Sources sources;
		sources.push_back({kernel_str.c_str(), kernel_str.length()});
        cl::Program program(context, sources);

        cl_int err = program.build("-cl-fast-relaxed-math");
        if (err != CL_SUCCESS) {
            std::string buildlog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(best_device);
            throw std::runtime_error("Error building: " + buildlog + "\n");
        }

        return program;
	}

}
