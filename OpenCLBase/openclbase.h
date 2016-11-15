#ifndef OPENCLBASE_H
#define OPENCLBASE_H

//Header for this file
//
//C System-Headers
//
//C++ System headers
//
//OpenCL Headers
#include <CL/cl.h>
#include <CL/cl.hpp>
//Boost Headers
//
//OpenMP Headers
//
//Project specific headers
//

namespace jaspl {

namespace ocl {

class OpenCLBase {

  public:

    OpenCLBase( uint device_number = 0 );
    virtual ~OpenCLBase() = 0;

  protected:

    void SetUp(uint device_number);

    static bool initalized;
    static std::vector<cl::Platform> all_platforms;
    static cl::Platform default_platform;
    static std::vector<cl::Device> all_devices;
    static cl::Device current_device;
    static cl::Context context;
    static cl::CommandQueue command_queue;
};

}

}


#endif // OPENCLBASE_H
