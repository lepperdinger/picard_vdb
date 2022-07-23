// Author: Stefan Lepperdinger
#include "hdf5_file.h"
#include <iostream>
#include <memory>

namespace hdf5_file {

tensors::tensor_3d read_3d_dataset(const std::string &file_name,
                                   const std::string &dataset_name,
                                   bool reverse_order) {
  hid_t file = H5Fopen(file_name.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  if (file < 0) {
    std::cerr << "error: Couldn't open the file '" << file_name << "'\n";
    std::exit(1);
  }
  hid_t dataset = H5Dopen2(file, dataset_name.c_str(), H5P_DEFAULT);
  if (dataset < 0) {
    std::cerr << "error: Couldn't open the dataset '" << dataset_name << "'\n";
    std::exit(1);
  }
  hid_t file_space = H5Dget_space(dataset);
  int number_of_dimensions = H5Sget_simple_extent_ndims(file_space);
  if (number_of_dimensions != 3) {
    std::cerr << "error: wrong number of dimensions of the dataset '"
              << dataset_name << "'.\n";
    std::exit(1);
  }
  auto dimensions = std::make_unique<hsize_t[]>(number_of_dimensions);
  H5Sget_simple_extent_dims(file_space, dimensions.get(), nullptr);

  size_t number_of_values = dimensions[0] * dimensions[1] * dimensions[2];
  auto buffer = std::make_unique<float[]>(number_of_values);

  hid_t memory_space =
      H5Screate_simple(number_of_dimensions, dimensions.get(), nullptr);

  H5Dread(dataset, H5T_NATIVE_FLOAT, memory_space, file_space, H5P_DEFAULT,
          buffer.get());

  size_t x_dimension;
  size_t y_dimension;
  size_t z_dimension;
  if (reverse_order) {
    x_dimension = dimensions[2];
    y_dimension = dimensions[1];
    z_dimension = dimensions[0];
  } else {
    x_dimension = dimensions[0];
    y_dimension = dimensions[1];
    z_dimension = dimensions[2];
  }
  auto data = tensors::make_3d_tensor({x_dimension, y_dimension, z_dimension});
  for (size_t x{}; x != x_dimension; ++x) {
    for (size_t y{}; y != y_dimension; ++y) {
      for (size_t z{}; z != z_dimension; ++z) {
        size_t data_index;
        if (reverse_order) {
          data_index = z * y_dimension * x_dimension;
          data_index += y * x_dimension;
          data_index += x;
        } else {
          data_index = x * y_dimension * z_dimension;
          data_index += y * z_dimension;
          data_index += z;
        }
        data[x][y][z] = buffer[data_index];
      }
    }
  }

  H5Sclose(memory_space);
  H5Sclose(file_space);
  H5Dclose(dataset);
  H5Fclose(file);
  return data;
}

} // namespace hdf5_file