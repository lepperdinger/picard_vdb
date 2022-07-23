#include "read.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string usage =
      "usage: hdf5_to_openvdb <source *.h5> <HDF5 dataset name> <destination *.vdb>";
  if (argc != 4) {
    std::cerr << usage << std::endl;
    std::exit(1);
  }
  std::string source_path = argv[1];
  std::string dataset_name = argv[2];
  std::string destination = argv[3];
  
  auto data = read::read_3d_dataset(source_path, dataset_name);

  return 0;
}
