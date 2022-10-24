cmake_minimum_required(VERSION 3.22)
project(TensorMath)

set(CMAKE_CXX_STANDARD 17)


add_executable(TensorMath main.cpp TensorMath/Matrix.hpp TensorMath/Vector.hpp TensorMath/FixedVector.hpp TensorMath/BoundingVolume.hpp TensorMath/Camera.hpp TensorMath/Tensor.hpp TensorMath/VoxelVolume.hpp)
add_library(TensorMath_lib main.cpp TensorMath/Matrix.hpp TensorMath/Vector.hpp TensorMath/FixedVector.hpp TensorMath/BoundingVolume.hpp TensorMath/Camera.hpp TensorMath/Tensor.hpp TensorMath/VoxelVolume.hpp)
add_subdirectory(Tests)