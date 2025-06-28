#include "backend/distance_matrix.hpp"

#include "CL_context.hpp"
#include <iostream>

namespace backend {

    extern "C" void distance_matrix(double* data, int rows, int cols, double* res) {
        try {
            const cl::Context& context = CL_context::instance().get_context();
            const cl::CommandQueue& queue = CL_context::instance().get_queue();


            cl::Program program = CL_context::instance().get_program("distance.cl");
            
            cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double) * rows * cols, data);
            cl::Buffer outputBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double) * rows * rows);

            cl::Kernel kernel(program, "distance_matrix");
            kernel.setArg(0, outputBuffer);
            kernel.setArg(1, inputBuffer);
            kernel.setArg(2, rows);
            kernel.setArg(3, cols);

            cl::NDRange global(rows, rows);
            queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, cl::NullRange);
            queue.finish();

            queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, sizeof(double) * rows * rows, res);
        }
        catch (cl::Error &err) {
            throw std::runtime_error(std::string("OpenCL Error: ") + err.what() + " (" + std::to_string(err.err()) + ")\n");
        }
    }

}