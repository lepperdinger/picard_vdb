cmake_minimum_required(VERSION 3.16)
project(hdf5_to_openvdb)

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


# libraries ####################################################################


# Half library
find_library(HALF_LIBRARY Half)


# HDF5 library for reading and writing to HDF5 files
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# TBB library for parallelization
find_package(TBB REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(OpenVDB REQUIRED)


# executable ###################################################################

file(GLOB SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(
  hdf5_to_openvdb
  apps/hdf5_to_openvdb
  ${SRC}
)

target_link_libraries(
  hdf5_to_openvdb
  TBB::tbb
  ${HDF5_LIBRARIES}
  ${HALF_LIBRARY}
  OpenVDB::openvdb
)
target_compile_options(hdf5_to_openvdb PRIVATE -Wall -Wextra -Wpedantic -Werror)
