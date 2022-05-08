enable_language(CUDA)
find_package(CUDA REQUIRED)
add_library(CUDA
fitness.cu
)
set(CMAKE_CUDA_COMPILE_SEPARABLE_COMPILATION 
"${CMAKE_CUDA_COMPILE_SEPARABLE_COMPILATION} && touch <OBJECT>")

set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_61,code=sm_61")

if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
  set(CMAKE_CUDA_ARCHITECTURES 61)
endif(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)

target_compile_features(CUDA PUBLIC)
set_target_properties(CUDA
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON
                       CMAKE_CUDA_COMPILE_SEPARABLE_COMPILATION on)
target_link_libraries(CUDA)