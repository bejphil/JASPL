#ifndef JFFT_UNIT_TEST_H
#define JFFT_UNIT_TEST_H

//Header for this file
//
//C System-Headers
#include <math.h>
//C++ System headers
#include <iostream>
#include <chrono>
//OpenCL Headers
//
//Boost Headers
//
//Project specific headers
#include "jVector/jvector.h"
#include "jFFT/ocl_jfft.h"
#include "jFFT/jfft.h"
#include "jPlot/jplot.h"

namespace jaspl {

template <typename T>
class JFFTUnitTest {

  public:

    void TestCPUFFT( uint num_points ) {

        JVector<T> vec = SineSignal( num_points );

        auto fft_er = jaspl::JFFT();

        fft_er.Setup( vec.size() );

        auto start_cpu = std::chrono::high_resolution_clock::now();

        fft_er.PowerSpectrum( vec );

        auto end_cpu = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> cpu_ms = end_cpu - start_cpu;
        auto time_taken_cpu = cpu_ms.count();

        std::cout<<"CPU took "<<time_taken_cpu<<" ms."<<std::endl;

        fft_er.TearDown();

        plot( vec, "FFT (CPU)", 500 );

    }

    void TestGPUFFT( uint num_points ) {

        JVector<T> vec = SineSignal( num_points );

        auto ocl_fft_er = jaspl::ocl::JFFT();

        ocl_fft_er.Setup();

        auto start_gpu = std::chrono::high_resolution_clock::now();

        ocl_fft_er.PowerSpectrum( vec );

        auto end_gpu = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> gpu_ms = end_gpu - start_gpu;
        auto time_taken_gpu = gpu_ms.count();

        ocl_fft_er.Teardown();

        std::cout<<"GPU took "<<time_taken_gpu<<" ms."<<std::endl;

        plot( vec, "FFT (GPU)", 500 );

    }

  private:
    JVector<T> SineSignal( uint N ) {

        JVector<T> sin_vect ( N );

        for ( uint i = 0; i < N ; i++ ) {

            sin_vect.push_back( sinf( 2*i *2*M_PI/N) + sinf( 25*i*2*M_PI/N) + sinf( 100*i*2*M_PI/N ) );
        }

        return sin_vect;
    }
};

}

#endif // JFFT_UNIT_TEST_H