/* ************************************************************************
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ************************************************************************ */

#ifndef CUBLAS_BENCHMARK_xCsr2Coo_HXX__
#define CUBLAS_BENCHMARK_xCsr2Coo_HXX__

#include "cufunc_common.hpp"
#include "include/io-exception.hpp"

template <typename T>
class xCsr2Coo : public cusparseFunc
{
public:
    xCsr2Coo(StatisticalTimer& timer): cusparseFunc(timer)
    {
        n_rows = 0;
        n_cols = 0;
        n_vals = 0; // nnz
    }// end

    ~xCsr2Coo()
    {

    }// end

    void call_func()
    {
        timer.Start(timer_id);

        xCsr2Coo_Function(true);

        timer.Stop(timer_id);
    }//end

    double gflops()
    {
        return 0.0;
    }//

    std::string gflops_formula()
    {
        return "N/A";
    }// end

    double bandwidth()
    {
#if 0
        //  Assuming that accesses to the vector always hit in the cache after the first access
        //  There are NNZ integers in the cols[ ] array
        //  You access each integer value in row_delimiters[ ] once.
        //  There are NNZ float_types in the vals[ ] array
        //  You read num_cols floats from the vector, afterwards they cache perfectly.
        //  Finally, you write num_rows floats out to DRAM at the end of the kernel.
        return (sizeof(int)*(n_vals + n_rows) + sizeof(T) * (n_vals + n_cols + n_rows)) / time_in_ns();
#endif
		// Number of Elements converted in unit time
		return (n_vals / time_in_ns());
    }//end

    std::string bandwidth_formula()
    {
        //return "GiB/s";
		return "GiElements/s";
    }// end

    void setup_buffer(double alpha, double beta, const std::string& path)
    {
        int fileError = sparseHeaderfromFile(&n_vals, &n_rows, &n_cols, path.c_str());
        if (fileError != 0)
        {
            throw clsparse::io_exception("Could not read matrix market header from disk");
        }

        if (csrMatrixfromFile(row_offsets, col_indices, values, path.c_str()))
        {
            throw clsparse::io_exception("Could not read matrix market header from disk");
        }
        /*
        n_rows = row_offsets.size();
        n_cols = col_indices.size();
        n_vals = values.size();
        */
        // Input: CSR
        cudaError_t err = cudaMalloc((void**)&deviceCSRRowOffsets, (n_rows+1) * sizeof(int));
        CUDA_V_THROW(err, "cudaMalloc deviceCSRRowOffsets");

        // Output: COO Row Indices
        err = cudaMalloc((void**)&deviceCooRowInd, n_vals * sizeof(int));
        CUDA_V_THROW(err, "cudaMalloc deviceCooRowInd");
    }// End of function

    void initialize_cpu_buffer()
    {
    }// end

    void initialize_gpu_buffer()
    {
        cudaError_t err = cudaMemcpy(deviceCSRRowOffsets, &row_offsets[0], row_offsets.size() * sizeof(int), cudaMemcpyHostToDevice);
        CUDA_V_THROW(err, "cudaMalloc deviceCSRRowOffsets");

        err = cudaMemset(deviceCooRowInd, 0x0, n_vals * sizeof(int));
        CUDA_V_THROW(err, "cudaMemset deviceCooRowInd");

    }// end of function

    void reset_gpu_write_buffer()
    {
        err = cudaMemset(deviceCooRowInd, 0x0, n_vals * sizeof(int));
        CUDA_V_THROW(err, "cudaMemset deviceCooRowInd");
    }// end of function

    void read_gpu_buffer()
    {
    }// end

    void releaseGPUBuffer_deleteCPUBuffer()
    {
        CUDA_V_THROW(cudaFree(deviceCSRRowOffsets), "cudafree deviceCSRRowOffsets");
        CUDA_V_THROW(cudaFree(deviceCooRowInd), "cudafree deviceCooRowInd");

        row_offsets.clear();
        col_indices.clear();
        values.clear();
    }// end

protected:
    void initialize_scalars(double pAlpha, double pBeta)
    {
    }//end

private:
    void xCsr2Coo_Function(bool flush);

  //  std::string sparseFile;

    //host matrix definition corresponding to CSR Format
    std::vector< int > row_offsets;
    std::vector< int > col_indices;
    std::vector< T > values; // matrix values

    int  n_rows; // number of rows
    int  n_cols; // number of cols
    int  n_vals; // number of Non-Zero Values (nnz)
    int* colIndices;

    // device CUDA pointers
    int* deviceCSRRowOffsets; // Input: CSR Row Offsets
    int* deviceCooRowInd; // Output: Coordinate format row indices
}; // class xCsr2Coo

template<>
void
xCsr2Coo<float>::
xCsr2Coo_Function(bool flush)
{
    cuSparseStatus = cusparseXcsr2coo(handle,
                                      deviceCSRRowOffsets,
                                      n_vals,
                                      n_rows,
                                      deviceCooRowInd,
                                      CUSPARSE_INDEX_BASE_ZERO );

    CUDA_V_THROW(cuSparseStatus, "cusparseXcsr2coo");

    cudaDeviceSynchronize();

}


template<>
void
xCsr2Coo<double>::
xCsr2Coo_Function(bool flush)
{
    cuSparseStatus = cusparseXcsr2coo(handle,
        deviceCSRRowOffsets,
        n_vals,
        n_rows,
        deviceCooRowInd,
        CUSPARSE_INDEX_BASE_ZERO );

    CUDA_V_THROW(cuSparseStatus, "cusparseXcsr2coo");

    cudaDeviceSynchronize();

}

#endif //CUBLAS_BENCHMARK_xCsr2Coo_HXX__
