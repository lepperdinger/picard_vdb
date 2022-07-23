// Author: Stefan Lepperdinger
#include "hdf5_file.h"
#include "processing.h"
#include "vdb_file.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string usage = "usage: hdf5_to_openvdb <source *.h5> <HDF5 dataset "
                      "name> <destination *.vdb>";
  if (argc != 4) {
    std::cerr << usage << std::endl;
    std::exit(1);
  }
  std::string source_path = argv[1];
  std::string dataset_name = argv[2];
  std::string destination_path = argv[3];

  // read data
  auto data = hdf5_file::read_3d_dataset(source_path, dataset_name);

  // process data
  processing::normalize_data(data);

  // write data
  auto grid = vdb_file::create_grid();
  vdb_file::fill_grid(grid, data);
  vdb_file::save_file(destination_path, grid);

  return 0;
}
