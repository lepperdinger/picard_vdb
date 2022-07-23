// Author: Stefan Lepperdinger
#include "hdf5_file.h"
#include "processing.h"
#include "vdb_file.h"
#include <iostream>
#include <regex>

int main(int argc, char *argv[]) {
  // parse arguments
  std::string usage = "usage: hdf5_to_openvdb [--reverse] <source *.h5> <HDF5 "
                      "dataset name> <destination *.vdb>";
  std::vector<std::string> positional_arguments;
  bool reverse_order{false};
  for (int i{1}; i != argc; ++i) {
    if (std::regex_match(argv[i], std::regex("^--.*$"))) {
      if ("--reverse" == std::string(argv[i])) {
        reverse_order = true;
        continue;
      } else {
        std::cerr << "error: unknown option " << argv[i] << '\n';
        std::cerr << usage << '\n';
        std::exit(1);
      }
    }
    positional_arguments.emplace_back(argv[i]);
  }
  if (positional_arguments.size() != 3) {
    std::cerr << "error: invalid number of arguments\n";
    std::cerr << usage << std::endl;
    std::exit(1);
  }
  std::string source_path = positional_arguments[0];
  std::string dataset_name = positional_arguments[1];
  std::string destination_path = positional_arguments[2];

  // read data
  auto data =
      hdf5_file::read_3d_dataset(source_path, dataset_name, reverse_order);

  // process data
  processing::normalize_data(data);

  // write data
  auto grid = vdb_file::create_grid();
  vdb_file::fill_grid(grid, data);
  vdb_file::save_file(destination_path, grid);

  return 0;
}
